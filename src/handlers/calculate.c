#include <handlers.h>
#include <common.h>
#include <operation_request.h>
#include <stdlib.h>
#include <string.h>
#include <operation_response.h>
#include <repository.h>

int calculator_calculate_handler (struct mg_connection *connection, void *data)
{
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

        repository_save (&operation);

        operation_response_from (&response, &operation);

        operation_response_to_json (&response, buffer_send, sizeof (buffer_send));

        return calculator_response (connection,
                                buffer_send,
                                strlen (buffer_send),
                                sat_webserver_http_status_ok);
    }

    return status;
}