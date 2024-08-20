#include <handlers.h>
#include <common.h>
#include <operation_request.h>
#include <stdlib.h>
#include <string.h>
#include <operation_response.h>

int calculator_calculate_handler (struct mg_connection *connection, void *data)
{
    // char *json = "{\"value_1\":%s,\"value_2\":%s,\"result\":%d}";

    const struct mg_request_info *ri = mg_get_request_info (connection);

    int status = sat_webserver_http_status_bad_request;

    char buffer_send [512] = {0};

    operation_request_t request;
    operation_t operation;
    operation_response_t response;


    if (ri->query_string != NULL)
    {
        operation_request_from_query (&request, ri->query_string);

        operation_request_to (&request, &operation);

        operation_calculate (&operation);

        operation_response_from (&response, &operation);

        operation_response_to_json (&response, buffer_send, sizeof (buffer_send));

        return calculator_response (connection,
                                buffer_send,
                                strlen (buffer_send),
                                sat_webserver_http_status_ok);
    }

    return status;
}