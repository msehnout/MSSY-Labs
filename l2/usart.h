#ifndef USART_H_
#define USART_H_

#include "string_buffer.h"

void USART_init(void);
void USART_Transmit(const uint8_t data);
void usart_transmit_string(const struct StringBuffer s);
void usart_println(const struct StringBuffer s);
uint8_t USART_Receive( void );

#endif // USART_H_