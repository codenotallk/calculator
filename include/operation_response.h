#ifndef OPERATION_RESPONSE_H_
#define OPERATION_RESPONSE_H_

#include <operation.h>
#include <stdint.h>

#define OPERATION_RESPONSE_FIELD_SIZE       30

typedef struct
{
    struct 
    {
        int _1;
        int _2;
    } values;

    int result;

    char type [OPERATION_RESPONSE_FIELD_SIZE + 1];
} operation_response_t;

void operation_response_from (operation_response_t *object, const operation_t *operation);
void operation_response_to_json (operation_response_t *object, char *buffer, uint32_t size);

#endif/* OPERATION_RESPONSE_H_ */
