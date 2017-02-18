/*
 * string_buffer.h
 *
 * Created: 16.2.2017 15:53:01
 *  Author: Martin Sehnoutka
 */


#ifndef STRING_BUFFER_H_
#define STRING_BUFFER_H_

struct StringBuffer {
    char *string;
    size_t length;
};

typedef const struct StringBuffer StringLiteral;

#define string_builder(STR)      \
    {                            \
        .string = (STR),         \
        .length = sizeof((STR)), \
    }

#endif /* STRING_BUFFER_H_ */
