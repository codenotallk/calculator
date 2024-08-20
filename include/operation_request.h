#ifndef OPERATION_REQUEST_H_
#define OPERATION_REQUEST_H_

#define OPERATION_REQUEST_SIZE      30

typedef struct
{
    struct
    {
        char _1 [OPERATION_REQUEST_SIZE + 1];
        char _2 [OPERATION_REQUEST_SIZE + 1];
    } values;
} operation_request_t;

#endif/* OPERATION_REQUEST_H_ */
