#ifndef usart_H_
#define usart_H_

#include "string_buffer.h"

/// Initialize USART1
void usart_init(void);

/// Transmit one byte of data
void usart_transmit(const uint8_t data);

/// Recieve one byte of data
uint8_t usart_receive( void );

/// Transmit string from StringBuffer
void usart_transmit_string(const struct StringBuffer s);

/// Transmit string followed by \n\r
void usart_println(const struct StringBuffer s);

#endif // usart_H_
