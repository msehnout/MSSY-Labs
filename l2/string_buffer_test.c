#include <stdio.h>
#define uint8_t int
#include "string_buffer.h"

int main() {
    struct StringBuffer test = string_builder("test");
    printf("%s - %d", test.string, test.length);
    return 0;
}
