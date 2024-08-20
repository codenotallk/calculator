#include <operation_response.h>
#include <string.h>
#include <stdio.h>

void operation_response_from (operation_response_t *object, const operation_t *operation)
{
    memset (object, 0, sizeof (operation_response_t));

    strncpy (object->type, operation->type, OPERATION_RESPONSE_FIELD_SIZE);

    object->result = operation->result;
    object->values._1 = operation->values._1;
    object->values._2 = operation->values._2;
}

void operation_response_to_json (operation_response_t *object, char *buffer, uint32_t size)
{
    char *json = "{\"type\":\"%s\",\"value_1\":%d,\"value_2\":%d,\"result\":%d}";

    snprintf (buffer,
              size - 1,
              json,
              object->type,
              object->values._1,
              object->values._2,
              object->result);
}