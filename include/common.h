#ifndef COMMON_H_
#define COMMON_H_

#include <sat.h>

sat_webserver_http_status_t calculator_response (struct mg_connection *connection, char *content, uint32_t size, sat_webserver_http_status_t status);

#endif/* COMMON_H_ */
