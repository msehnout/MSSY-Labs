#ifndef usart_H_
#define usart_H_

#include "string_buffer.h"

enum UsartSpeed {
   USART_SPEED_9600,
   USART_SPEED_14400,
};

enum UsartDataBits {
   USART_DATA_BITS_7 ,
   USART_DATA_BITS_8 ,
   USART_DATA_BITS_9 ,
};

enum UsartParity {
   USART_PARITY_NONE ,
   USART_PARITY_EVEN ,
   USART_PARITY_ODD ,
};

enum UsartStopBits {
   USART_STOP_BITS_1,
   USART_STOP_BITS_2,
};

struct UsartBuilder {
   enum UsartSpeed speed;
   enum UsartDataBits data_bits;
   enum UsartParity parity;
   enum UsartSpeed stop_bits;
};

#ifndef __TESTING__

/// Initialize USART1
void usart_init(void);

/// Initialize USART1
void usart_builder_finalize(struct UsartBuilder builder);

/// Transmit one byte of data
void usart_transmit(const uint8_t data);

/// Recieve one byte of data
uint8_t usart_receive(void);

/// Transmit one byte of data
void usart_transmit_buffer(const void *data, size_t length);

/// Transmit string from StringBuffer
void usart_transmit_string(const struct StringBuffer s);

/// Transmit string followed by \n\r
void usart_println(const struct StringBuffer s);

#endif // __TESTING__
#endif // usart_H_
