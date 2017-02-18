/*
 * lab1.c
 *
 * Created: 9.2.2017 13:18:57
 * Author : Student
 */ 

#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

#define SETBIT(VAR,BIT) ((VAR |= (1 << BIT)))
#define CLEARBIT(VAR,BIT) ((VAR &= ~(1 << BIT)))
#define ISSET(VAR,BIT) ((VAR & (1 << BIT)))

//#define F_CPU 8000000UL

int main(void)
{
    /* Replace with your application code */
	
	SETBIT(DDRB, 5);
	SETBIT(DDRB, 6);
	SETBIT(DDRE, 3);
	SETBIT(PORTB, 6);
	SETBIT(PORTB, 5);
	SETBIT(PORTE, 3);
	
	CLEARBIT(DDRE, 5); // input
	SETBIT(PORTE, 5);  // internal pull-up
	
	CLEARBIT(DDRF, 0); // input
	SETBIT(PORTF, 0);  // internal pull-up
	
	CLEARBIT(DDRF, 1); // input
	SETBIT(PORTF, 1);  // internal pull-up
	
// 	DDRB = 0xFF;
// 	DDRE = 0xFF;
// 	PORTB = 0xFF;
// 	PORTE = 0xFF;
// 	
    while (1) 
    {
		// Ukol 3
// 		_delay_loop_2(0xFFFF);
// 		SETBIT(PORTB, 6);
// 		_delay_loop_2(0xFFFF);
// 		CLEARBIT(PORTB, 6);

		// Ukol 4
// 		SETBIT(PORTE, 3);
// 		CLEARBIT(PORTB, 5);
// 		_delay_loop_2(0xFFFF);
// 		SETBIT(PORTB, 5);
// 		CLEARBIT(PORTB, 6);
// 		_delay_loop_2(0xFFFF);
// 		SETBIT(PORTB, 6);
// 		CLEARBIT(PORTE, 3);
// 		_delay_loop_2(0xFFFF);

		// Ukol 5
		if ISSET(PINE, 5)	{
			SETBIT(PORTB, 5);
		} else {
			CLEARBIT(PORTB, 5);
		}
		
		if ISSET(PINF, 0)	{
			SETBIT(PORTB, 6);
			} else {
			CLEARBIT(PORTB, 6);
		}
		
		if ISSET(PINF, 1)	{
			SETBIT(PORTE, 3);
			} else {
			CLEARBIT(PORTE, 3);
		}
		_delay_loop_2(0x00FF);
    }
}

