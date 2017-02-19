
#ifndef __TESTING__
#include <avr/io.h>
#define F_CPU 8000000UL
#define BAUD 9600
#include <util/setbaud.h>
#include <avr/sfr_defs.h>
#endif // __TESTING__

#include "usart.h"
#include "return_t.h"

#ifndef RX_BUFFER_SIZE
#define RX_BUFFER_SIZE 256
#endif

#ifndef TX_BUFFER_SIZE
#define TX_BUFFER_SIZE 256
#endif

#ifndef index_t
#define index_t uint16_t
#endif

/// Recieve buffer
static uint8_t RX_BUFFFER[RX_BUFFFER_SIZE] = {0};
/// Points to the end of data portion in buffer
static index_t RX_IDX = 0;
/// Transmit buffer
static uint8_t TX_BUFFFER[TX_BUFFFER_SIZE] = {0};
/// Points to the end of data portion in buffer
/// XXX: Maybe I should have two of these, so I don't have to move the whole
// buffer with every byte sent
static index_t TX_IDX = 0;

#ifdef __TESTING__
void usart_get_buffers(uint8_t **tx_buffer, uint8_t **rx_buffer) {
    *tx_buffer = TX_BUFFFER;
    *rx_buffer = RX_BUFFFER;
}
#endif // __TESTING__

#ifndef __TESTING__
void usart_init(void) {
    /* Setup usart1 */
    //uint16_t baud_rate = MYUBRR;
    UBRR1H = UBRRH_VALUE;// (uint8_t)(baud_rate>>8);
    UBRR1L = UBRRL_VALUE;//(uint8_t)baud_rate;
    /* Enable receiver and transmitter */
    UCSR1B = (1<<RXEN1)|(1<<TXEN1)|(1<<UCSZ12);
    /*UCSR1C = (1<<UPM11)|	// Odd parity
      (1<<UPM10)|	//
      (1<<USBS1)|	// 2 stop bits
      (1<<UCSZ11)|	// 8-bits message
      (1<<UCSZ10);	//*/
    UCSR1C = (1<<UCSZ11)|(1<<UCSZ10);
}

void usart_transmit(const uint8_t data) {
    /* Wait for empty transmit buffer */
    //while ( !( UCSR1A & (1<<UDRE1)) )
    //;
    loop_until_bit_is_set(UCSR1A, UDRE1);
    /* Put data into buffer, sends the data */
    UDR1 = data;
}

void usart_transmit_buffer(const void *data, size_t length) {
    size_t i = 0;
    uint8_t array = (uint8_t *)data;
    for (i=0; i < length; ++i) {
        usart_transmit(array[i]);
    }
}

void usart_transmit_string(const struct StringBuffer s) {
    size_t i = 0;
    while (i < s.length && s.string[i] != '\0') {
        usart_transmit((uint8_t)s.string[i]);
        ++i;
    }
}

void usart_println(const struct StringBuffer s) {
    struct StringBuffer line_ending = {
        .string = "\n\r",
        .length = 2,
    };
    usart_transmit_string(s);
    usart_transmit_string(line_ending);
}

uint8_t usart_receive( void ) {
    /* Wait for data to be received */
    //while ( !(UCSR1A & (1<<RXC1)) )
    //;
    loop_until_bit_is_set(UCSR1A, RXC1);
    /* Get and return received data from buffer */
    return UDR1;
}

#endif // __TESTING__

// This functions should be used from the main loop
return_t usart_tx_buffer_push(const uint8_t byte) {
    if (TX_IDX < TX_BUFFFER_SIZE) {
        TX_BUFFFER[TX_IDX] = byte;
        ++TX_IDX;
        return RET_SUCCESS;
    } else {
        // Let's panic!
        return RET_BUFFER_OVERFLOW;
    }
}

// This function is supposed to be called from interrupt
return_t usart_rx_buffer_push(const uint8_t byte) {
    if (RX_IDX < RX_BUFFFER_SIZE) {
        RX_BUFFFER[RX_IDX] = byte;
        ++RX_IDX;
        return RET_SUCCESS;
    } else {
        // Let's panic!
        return RET_BUFFER_OVERFLOW;
    }
}

return_t usart_rx_view_slice(uint8_t **view, const index_t length) {
    if (length <= RX_IDX) {
        *view = RX_BUFFFER;
        return RET_SUCCESS;
    } else {
        *view = NULL;
        return RET_NOT_ENOUGH_DATA;
    }
}
