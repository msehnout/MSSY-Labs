#ifndef RETURN_T_H_
#define RETURN_T_H_

/// Return type from functions which might fail
enum e_return_t {
    RET_SUCCESS, ///< Everything went fine
    RET_BUFFER_OVERFLOW, ///< Data wouldn't fit into the buffer. Used with non-blocking USART.
    RET_NOT_ENOUGH_DATA, ///< The buffer does not contain enough data. Used with non-blocking USART.
};

/// I don't want to write enum everywhere
typedef enum e_return_t return_t;

#endif
