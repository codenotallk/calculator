#include <handlers.h>
#include <repository_base.h>
#include <common.h>
#include <string.h>
#include <operation_response.h>
#include <report_request.h>

int calculator_report_handler (struct mg_connection *connection, void *data)
{
    int http_status = sat_webserver_http_status_not_found;

    repository_base_t *repository = (repository_base_t *) data;

    report_request_t request;
    interval_t interval;

    const struct mg_request_info *ri = mg_get_request_info (connection);

    char buffer [2048] = {0};

    sat_status_t status = sat_status_set (&status, true, "");

    interval_init (&interval);

    if (ri->query_string != NULL)
    {
        status = report_request_from_query (&request, ri->query_string);
        if (sat_status_get_result (&status) == true)
        {
            report_request_to (&request, &interval);
        }

        else 
        {
            snprintf (buffer, sizeof (buffer) - 1, "{\"error\":\"%s\"}",
                                                   sat_status_get_motive (&status));
        }
    }

    if (sat_status_get_result (&status) == true)
    {
        sat_array_t *array = repository->get (repository->object, &interval);  

        operation_response_from_list_to_json (array, buffer, sizeof (buffer));

        sat_array_destroy (array);

        http_status = sat_webserver_http_status_ok;
    }

    return calculator_response (connection,
                                  buffer,
                                  strlen (buffer),
                                  http_status);

}