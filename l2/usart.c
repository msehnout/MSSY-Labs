
#include <avr/io.h>
#define F_CPU 8000000UL
#define BAUD 9600
#include <util/setbaud.h>
#include <avr/sfr_defs.h>

#include "usart.h"

void USART_init(void)
{
	/* Setup USART1 */
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

void USART_Transmit(const uint8_t data)
{
	/* Wait for empty transmit buffer */
	//while ( !( UCSR1A & (1<<UDRE1)) )
	//;
	loop_until_bit_is_set(UCSR1A, UDRE1);
	/* Put data into buffer, sends the data */
	UDR1 = data;
}

void usart_transmit_string(const struct StringBuffer s)
{
	uint8_t i = 0;
	while (i < s.length && s.string[i] != '\0') {
		USART_Transmit(s.string[i]);
		++i;
	}
}

void usart_println(const struct StringBuffer s)
{
	struct StringBuffer line_ending = 
	{
		.string = "\n\r",
		.length = 2,
	};
	usart_transmit_string(s);
	usart_transmit_string(line_ending);
}

uint8_t USART_Receive( void )
{
	/* Wait for data to be received */
	//while ( !(UCSR1A & (1<<RXC1)) )
	//;
	loop_until_bit_is_set(UCSR1A, RXC1);
	/* Get and return received data from buffer */
	return UDR1;
}