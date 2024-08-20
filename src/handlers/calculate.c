#include <handlers.h>
#include <common.h>
#include <operation_request.h>
#include <stdlib.h>
#include <string.h>

int calculator_calculate_handler (struct mg_connection *connection, void *data)
{
    char *json = "{\"value_1\":%s,\"value_2\":%s,\"result\":%d}";

    const struct mg_request_info *ri = mg_get_request_info (connection);

    int status = sat_webserver_http_status_bad_request;

    char buffer_send [512] = {0};

    operation_request_t request;

    if (ri->query_string != NULL)
    {
        memset (&request, 0, sizeof (operation_request_t));

        mg_get_var (ri->query_string,
                    strlen (ri->query_string),
                    "value_1",
                    request.values._1,
                    strlen (ri->query_string));

        mg_get_var (ri->query_string,
                    strlen (ri->query_string),
                    "value_2",
                    request.values._2,
                    strlen (ri->query_string));

        snprintf (buffer_send,
                  512 - 1,
                  json,
                  request.values._1,
                  request.values._2,
                  atoi (request.values._1) + atoi (request.values._2));

        return calculator_response (connection,
                                buffer_send,
                                strlen (buffer_send),
                                sat_webserver_http_status_ok);
    }

    return status;
}