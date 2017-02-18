#include <stdio.h>
#include "string_buffer.h"

int main() {
    StringLiteral test = string_builder("test");
    printf("%s - %d", test.string, test.length);
    return 0;
}
