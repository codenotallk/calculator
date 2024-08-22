#include <handlers.h>
#include <repository.h>
#include <common.h>
#include <string.h>
#include <operation_response.h>

int calculator_report_handler (struct mg_connection *connection, void *data)
{
    int status = sat_webserver_http_status_not_found;

    sat_array_t *array = repository_get (0);

    char buffer [2048] = {0};

    operation_response_from_list_to_json (array, buffer, sizeof (buffer));

    status = calculator_response (connection,
                                  buffer,
                                  strlen (buffer),
                                  sat_webserver_http_status_ok);


    sat_array_destroy (array);

    return status;
}