#include <common.h>
#include <string.h>

sat_webserver_http_status_t calculator_response (struct mg_connection *connection, char *content, uint32_t size, sat_webserver_http_status_t status)
{
    sat_webserver_response_t response;

    memset (&response, 0, sizeof (sat_webserver_response_t));

    sat_webserver_response_set_payload (&response, content, size);
    sat_webserver_response_set_status (&response, status);

    sat_webserver_response_header_add (&response, 
                                       "Content-Type",
                                       "application/json; charset=utf-8");

    sat_webserver_response_send (connection, response);

    return status;
}