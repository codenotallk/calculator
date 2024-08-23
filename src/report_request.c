#include <report_request.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct 
{
    sat_validation_t validation;
    bool initialized;
} report_request_validation_t;

static void report_request_validation_init (report_request_validation_t *object);

static sat_status_t report_request_criteria_offset_is_not_empty (void *object);
static sat_status_t report_request_criteria_offset_is_a_number (void *object);
static sat_status_t report_request_criteria_from_is_not_empty (void *object);
static sat_status_t report_request_criteria_from_is_a_date (void *object);
static sat_status_t report_request_criteria_to_is_not_empty (void *object);
static sat_status_t report_request_criteria_to_is_a_date (void *object);

static report_request_validation_t report_request_validation = {.initialized = false};

sat_status_t report_request_from_query (report_request_t *object, const char *query)
{

    memset (object, 0, sizeof (report_request_t));

    mg_get_var (query, strlen (query), "offset", object->offset.value,    REPORT_REQUEST_VALUE_SIZE);
    mg_get_var (query, strlen (query), "from",   object->date.from.value, REPORT_REQUEST_VALUE_SIZE);
    mg_get_var (query, strlen (query), "to",     object->date.to.value,   REPORT_REQUEST_VALUE_SIZE);

    if (report_request_validation.initialized == false)
    {
        report_request_validation_init (&report_request_validation);
    }

    return sat_validation_verify (&report_request_validation.validation, object);
}

void report_request_to (report_request_t *object, interval_t *interval)
{
    if (object->offset.present == true)
        interval->offset = atoi (object->offset.value);

    if (object->date.from.present == true)
        interval->date.from = sat_time_get_epoch_by_string (object->date.from.value,
                                                            REPORT_REQUEST_DATE_FORMAT);

    if (object->date.to.present == true)
        interval->date.to = sat_time_get_epoch_by_string (object->date.to.value,
                                                            REPORT_REQUEST_DATE_FORMAT);
}

static void report_request_validation_init (report_request_validation_t *object)
{
    sat_validation_init (&object->validation);

    sat_validation_add (&object->validation, report_request_criteria_offset_is_not_empty);
    sat_validation_add (&object->validation, report_request_criteria_offset_is_a_number);
    sat_validation_add (&object->validation, report_request_criteria_from_is_not_empty);
    sat_validation_add (&object->validation, report_request_criteria_from_is_a_date);
    sat_validation_add (&object->validation, report_request_criteria_to_is_not_empty);
    sat_validation_add (&object->validation, report_request_criteria_to_is_a_date);

    object->initialized = true;
}

static sat_status_t report_request_criteria_offset_is_not_empty (void *object)
{
    sat_status_t status = sat_status_set (&status, true, "");

    report_request_t *request = (report_request_t *) object;

    if (strlen (request->offset.value) > 0)
    {
        request->offset.present = true;
    }

    return status;
}

static sat_status_t report_request_criteria_offset_is_a_number (void *object)
{
    sat_status_t status = sat_status_set (&status, true, "");

    report_request_t *request = (report_request_t *) object;

    for (size_t i = 0; i < strlen (request->offset.value) && request->offset.present == true; i ++)
    {
        if (isdigit (request->offset.value [i]) == 0)
        {
            sat_status_set (&status, false, "offset is not a number");

            break;
        }
    }

    return status;
}

static sat_status_t report_request_criteria_from_is_not_empty (void *object)
{
    sat_status_t status = sat_status_set (&status, true, "");

    report_request_t *request = (report_request_t *) object;

    if (strlen (request->date.from.value) > 0)
    {
        request->date.from.present = true;
    }

    return status;
}

static sat_status_t report_request_criteria_from_is_a_date (void *object)
{
    sat_status_t status = sat_status_set (&status, true, "");

    report_request_t *request = (report_request_t *) object;

    if (request->date.from.present == true && 
        sat_time_get_epoch_by_string (request->date.from.value, REPORT_REQUEST_DATE_FORMAT) == 0)
    {
        sat_status_set (&status, false, "[from] field wrong format");
    }

    return status;
}

static sat_status_t report_request_criteria_to_is_not_empty (void *object)
{
    sat_status_t status = sat_status_set (&status, true, "");

    report_request_t *request = (report_request_t *) object;

    if (strlen (request->date.to.value) > 0)
    {
        request->date.to.present = true;
    }

    return status;
}

static sat_status_t report_request_criteria_to_is_a_date (void *object)
{
    sat_status_t status = sat_status_set (&status, true, "");

    report_request_t *request = (report_request_t *) object;

    if (request->date.to.present == true && 
        sat_time_get_epoch_by_string (request->date.to.value, REPORT_REQUEST_DATE_FORMAT) == 0)
    {
        sat_status_set (&status, false, "[to] field wrong format");
    }

    return status;
}