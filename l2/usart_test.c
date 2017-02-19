
#include <stdio.h>
#include <stdlib.h>
#define __TESTING__
#define index_t size_t
#define uint8_t unsigned char
#define RX_BUFFFER_SIZE 50
#define TX_BUFFFER_SIZE 50
#include "usart.c"

uint8_t *rx_buffer = NULL;
uint8_t *tx_buffer = NULL;

void print_buffer(uint8_t *buffer, index_t length) {
    printf("[");
    for (index_t i=0; i<length; ++i) {
        printf("%0X, ", buffer[i]);
    }
    printf("]\n");
}

void print_rx_buffer() {
    printf("RX BUFFER: ");
    print_buffer(rx_buffer, RX_BUFFFER_SIZE);
}

int main() {
    usart_get_buffers(&tx_buffer, &rx_buffer);
    print_rx_buffer();
    usart_rx_buffer_push(5);
    usart_rx_buffer_push(6);
    usart_rx_buffer_push(7);
    print_rx_buffer();
    return 0;
}
