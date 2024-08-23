#include <handlers.h>
#include <repository_base.h>
#include <common.h>
#include <string.h>
#include <operation_response.h>

int calculator_report_handler (struct mg_connection *connection, void *data)
{
    int status = sat_webserver_http_status_not_found;

    repository_base_t *repository = (repository_base_t *) data;

    struct 
    {
        char string [20];
        uint32_t number;
    } offset;

    const struct mg_request_info *ri = mg_get_request_info (connection);

    offset.number = 0;

    if (ri->query_string != NULL)
    {
        if (mg_get_var (ri->query_string,
            strlen (ri->query_string),
            "offset",
            offset.string,
            sizeof (offset.string)) > 0)
        {
            offset.number = atoi (offset.string);
        }
    }

    sat_array_t *array = repository->get (repository->object, offset.number);

    char buffer [2048] = {0};

    operation_response_from_list_to_json (array, buffer, sizeof (buffer));

    status = calculator_response (connection,
                                  buffer,
                                  strlen (buffer),
                                  sat_webserver_http_status_ok);


    sat_array_destroy (array);

    return status;
}