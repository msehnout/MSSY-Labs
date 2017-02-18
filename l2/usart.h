#ifndef usart_H_
#define usart_H_

#include "string_buffer.h"

void usart_init(void);
void usart_transmit(const uint8_t data);
void usart_transmit_string(const struct StringBuffer s);
void usart_println(const struct StringBuffer s);
uint8_t usart_receive( void );

#endif // usart_H_