#include <handlers.h>
#include <common.h>
#include <string.h>

int calculator_health_handler (struct mg_connection *connection, void *data)
{
    (void) data;

    char *json = "{\"status\":\"up\",\"message\":\"Calculator Application\"}";

    return calculator_response (connection,
                                json,
                                strlen (json),
                                sat_webserver_http_status_ok);
}