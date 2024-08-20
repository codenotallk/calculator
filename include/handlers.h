#ifndef HANDLERS_H_
#define HANDLERS_H_

#include <sat.h>

int calculator_health_handler (struct mg_connection *connection, void *data);
int calculator_calculate_handler (struct mg_connection *connection, void *data);

#endif/* HANDLERS_H_ */
