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

    strncpy (object->date, operation->date, OPERATION_RESPONSE_DATE_SIZE);
}

void operation_response_to_json (operation_response_t *object, char *buffer, uint32_t size)
{
    char *json = "{\"type\":\"%s\",\"value_1\":%d,\"value_2\":%d,\"result\":%d,\"date\":\"%s\"}";

    memset (buffer, 0, size);

    snprintf (buffer,
              size - 1,
              json,
              object->type,
              object->values._1,
              object->values._2,
              object->result,
              object->date);
}

void operation_response_from_list_to_json (sat_array_t *array, char *buffer, uint32_t size)
{
    uint32_t items;

    sat_array_get_size (array, &items);

    strncat (buffer, "[", 2);

    for (uint32_t i = 0; i < items && strlen (buffer) < size; i ++)
    {
        operation_t operation;
        operation_response_t response;
        char json [512] = {0};

        if (i > 0)
            strncat (buffer, ",", 2);

        sat_array_get_object_by (array, i, &operation);
        operation_response_from (&response, &operation);
        operation_response_to_json (&response, json, 512);

        strncat (buffer, json, strlen (json));
    }

    strncat (buffer, "]", 2);
}