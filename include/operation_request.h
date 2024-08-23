#ifndef OPERATION_REQUEST_H_
#define OPERATION_REQUEST_H_

#include <operation.h>
#include <sat.h>

#define OPERATION_REQUEST_FIELD_SIZE      30

typedef struct
{
    struct
    {
        char _1 [OPERATION_REQUEST_FIELD_SIZE + 1];
        char _2 [OPERATION_REQUEST_FIELD_SIZE + 1];
    } values;

    char type [OPERATION_REQUEST_FIELD_SIZE + 1];

} operation_request_t;

sat_status_t operation_request_from_query (operation_request_t *object, const char *query);
void operation_request_to (operation_request_t *object, operation_t *operation);

#endif/* OPERATION_REQUEST_H_ */
