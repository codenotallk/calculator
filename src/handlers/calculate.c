#include <handlers.h>
#include <common.h>
#include <operation_request.h>
#include <stdlib.h>
#include <string.h>
#include <operation_response.h>
#include <repository_base.h>

#define CALCULATOR_NO_QUERY_ERROR   "{\"error\":\"<ip>:<port>/v1/calculate?value_1=10&value_2=10&type=sum\"}"

int calculator_calculate_handler (struct mg_connection *connection, void *data)
{
    repository_base_t *repository = (repository_base_t *) data;

    const struct mg_request_info *ri = mg_get_request_info (connection);

    int http_status = sat_webserver_http_status_bad_request;

    char buffer_send [512] = CALCULATOR_NO_QUERY_ERROR;

    operation_request_t request;
    operation_t operation;
    operation_response_t response;


    if (ri->query_string != NULL)
    {
        sat_status_t status = operation_request_from_query (&request, ri->query_string);

        if (sat_status_get_result (&status) == true)
        {
            operation_request_to (&request, &operation);

            operation_calculate (&operation);

            repository->save (repository->object, &operation);

            operation_response_from (&response, &operation);

            operation_response_to_json (&response, buffer_send, sizeof (buffer_send));

            http_status = sat_webserver_http_status_ok;
        }

        else
        {
            char *error = "{\"error\":\"%s\"}";
            memset (buffer_send, 0, sizeof (buffer_send));
            snprintf (buffer_send, sizeof (buffer_send) - 1, error, sat_status_get_motive (&status));
        }
    }

    return calculator_response (connection,
                                buffer_send,
                                strlen (buffer_send),
                                http_status);
}