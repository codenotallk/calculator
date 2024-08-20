#include <operation_request.h>
#include <string.h>
#include <sat.h>

void operation_request_from_query (operation_request_t *object, const char *query)
{
    memset (object, 0, sizeof (operation_request_t));

    mg_get_var (query,
                strlen (query),
                "value_1",
                object->values._1,
                OPERATION_REQUEST_FIELD_SIZE);

    mg_get_var (query,
                strlen (query),
                "value_2",
                object->values._2,
                OPERATION_REQUEST_FIELD_SIZE);

    mg_get_var (query,
                strlen (query),
                "type",
                object->type,
                OPERATION_REQUEST_FIELD_SIZE);
}

void operation_request_to (operation_request_t *object, operation_t *operation)
{
    memset (operation, 0, sizeof (operation_t));

    strncpy (operation->type, object->type, OPERATION_TYPE_SIZE);
    operation->values._1 = atoi (object->values._1);
    operation->values._2 = atoi (object->values._2);
}