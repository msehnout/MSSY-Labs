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

#define set_bit(VAR,BIT) ((VAR |= (1 << BIT)))
#define clear_bit(VAR,BIT) ((VAR &= ~(1 << BIT)))
#define is_set_bit(VAR,BIT) ((VAR & (1 << BIT)))

#include "usart.h"

int main(void) {
    /* Setup internal clock */
    CLKPR = 0x80; // Enable CLKPR change
    CLKPR = 0x01; // Change division factor to 2

    usart_init();
    set_bit(UCSR1B, RXCIE1);

    sei();

    StringLiteral hello = string_builder("hello");
    StringLiteral konec = string_builder("Konec");
    StringLiteral menu0 = string_builder("MENU:");
    StringLiteral menu1 = string_builder("0 - Konec");
    StringLiteral menu2 = string_builder("1 - Zapnout LED");
    StringLiteral menu3 = string_builder("2 - Vypnout LED");
    StringLiteral menu4 = string_builder("4 - Abeceda");

    set_bit(DDRB, 5);
    set_bit(PORTB, 5);
    clear_bit(PORTB, 5);

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
            clear_bit(PORTB, 5);
            break;
        case '2':
            set_bit(PORTB, 5);
            break;
        case '4':
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
