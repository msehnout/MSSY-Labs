/*
 * string_buffer.h
 *
 * Created: 16.2.2017 15:53:01
 *  Author: Student
 */


#ifndef STRING_BUFFER_H_
#define STRING_BUFFER_H_

struct StringBuffer {
    char *string;
    uint8_t length;
};

#define string_builder(STR)      \
    {                            \
        .string = (STR),         \
        .length = sizeof((STR)), \
    }

#endif /* STRING_BUFFER_H_ */
