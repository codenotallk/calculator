#ifndef REPORT_REQUEST_H_
#define REPORT_REQUEST_H_

#include <interval.h>

#define REPORT_REQUEST_VALUE_SIZE       30
#define REPORT_REQUEST_DATE_FORMAT      "%d/%m/%Y %H:%M:%S"

typedef struct 
{
    char value [REPORT_REQUEST_VALUE_SIZE + 1];
    bool present;
} report_value_t;

typedef struct 
{
    struct 
    {
        report_value_t from;
        report_value_t to;
    } date;

    report_value_t offset;
} report_request_t;

sat_status_t report_request_from_query (report_request_t *object, const char *query);
void report_request_to (report_request_t *object, interval_t *interval);

#endif/* REPORT_REQUEST_H_ */
