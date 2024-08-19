#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <sat.h>

typedef struct
{
    sat_webserver_t webserver;
} calculator_t;

typedef struct 
{
    int dummy;
} calculator_args_t;

sat_status_t calculator_init (calculator_t *object);
sat_status_t calculator_open (calculator_t *object, calculator_args_t *args);
sat_status_t calculator_run (calculator_t *object);
sat_status_t calculator_close (calculator_t *object);

#endif/* APPLICATION_H_ */