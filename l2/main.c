/*
 * lab1.c
 *
 * Created: 9.2.2017 13:18:57
 * Author : Student
 */

#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#define BAUD 9600
#include <util/setbaud.h>
#include <avr/sfr_defs.h>
#include <avr/interrupt.h>

//#define MYUBRR (F_CPU/16/BAUD-1)

#define set_bit(VAR,BIT) ((VAR |= (1 << BIT)))
#define CLEARBIT(VAR,BIT) ((VAR &= ~(1 << BIT)))
#define ISSET(VAR,BIT) ((VAR & (1 << BIT)))

#include "usart.h"

int main(void) {
    /* Setup internal clock */
    CLKPR = 0x80; // Enable CLKPR change
    CLKPR = 0x01; // Change division factor to 2

    usart_init();
    set_bit(UCSR1B, RXCIE1);

    sei();

    const struct StringBuffer hello = {
        .string = "Hello",
        .length = 5,
    };

    const struct StringBuffer konec = {
        .string = "Konec",
        .length = 5,
    };
    const struct StringBuffer menu0 = {
        .string = "MENU:",
        .length = 5,
    };
    const struct StringBuffer menu1 = {
        .string = "0-konec",
        .length = 7,
    };
    const struct StringBuffer menu2 = {
        .string = "1-LED+",
        .length = 6,
    };
    const struct StringBuffer menu3 = {
        .string = "2-LED-",
        .length = 6,
    };
    const struct StringBuffer menu4 = {
        .string = "4-Abeceda",
        .length = 9,
    };


    set_bit(DDRB, 5);
    set_bit(PORTB, 5);
    CLEARBIT(PORTB, 5);

    usart_println(hello);
    while(1);

    // Puvodni ukol
    usart_println(menu0);
    usart_println(menu1);
    usart_println(menu2);
    usart_println(menu3);
    usart_println(menu4);


    while (1) {
        uint8_t recv;
        /* receive character */
        recv = usart_receive();
        /* Send back the character */
        switch (recv) {
        case '0':
            usart_println(konec);
            while(1);
            break;
        case '1':
            CLEARBIT(PORTB, 5);
            break;
        case '2':
            set_bit(PORTB, 5);
            break;
        case '3':
            usart_println(hello);
            break;
        default:
            break;
        }
        //usart_transmit(recv);
    }
}

ISR(USART1_RX_vect) {
    uint8_t recv;
    /* Recv character */
    recv = usart_receive();
    /* Send back the character */
    usart_transmit(recv);
    usart_transmit(recv);
}
