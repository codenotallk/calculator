#include <operation_request.h>
#include <string.h>
#include <ctype.h>

typedef struct 
{
    sat_validation_t validation;
    bool initialized;
} operation_request_validation_t;

static void operation_request_validation_initialize (operation_request_validation_t *object);

static sat_status_t operation_request_criteria_value_1_is_not_empty (void *object);
static sat_status_t operation_request_criteria_value_1_is_a_number (void *object);
static sat_status_t operation_request_criteria_value_2_is_not_empty (void *object);
static sat_status_t operation_request_criteria_value_2_is_a_number (void *object);
static sat_status_t operation_request_criteria_type_is_not_empty (void *object);
static sat_status_t operation_request_criteria_type_exists (void *object);

static operation_request_validation_t operation_request_validation = {.initialized = false};


sat_status_t operation_request_from_query (operation_request_t *object, const char *query)
{
    memset (object, 0, sizeof (operation_request_t));

    mg_get_var (query,
                strlen (query),
                "value_1",
                object->values._1,
                OPERATION_REQUEST_FIELD_SIZE);

    mg_get_var (query,
                strlen (query),
                "value_2",
                object->values._2,
                OPERATION_REQUEST_FIELD_SIZE);

    mg_get_var (query,
                strlen (query),
                "type",
                object->type,
                OPERATION_REQUEST_FIELD_SIZE);

    if (operation_request_validation.initialized == false)
    {
        operation_request_validation_initialize (&operation_request_validation);
        operation_request_validation.initialized = true;
    }

    return sat_validation_verify (&operation_request_validation.validation, object);
}

void operation_request_to (operation_request_t *object, operation_t *operation)
{
    memset (operation, 0, sizeof (operation_t));

    strncpy (operation->type, object->type, OPERATION_TYPE_SIZE);
    operation->values._1 = atoi (object->values._1);
    operation->values._2 = atoi (object->values._2);
}

static void operation_request_validation_initialize (operation_request_validation_t *object)
{
    sat_validation_init (&object->validation);

    sat_validation_add (&object->validation, operation_request_criteria_value_1_is_not_empty);
    sat_validation_add (&object->validation, operation_request_criteria_value_1_is_a_number);
    sat_validation_add (&object->validation, operation_request_criteria_value_2_is_not_empty);
    sat_validation_add (&object->validation, operation_request_criteria_value_2_is_a_number);
    sat_validation_add (&object->validation, operation_request_criteria_type_is_not_empty);
    sat_validation_add (&object->validation, operation_request_criteria_type_exists);
}

static sat_status_t operation_request_criteria_value_1_is_not_empty (void *object)
{
    sat_status_t status = sat_status_set (&status, false, "value 1 is empty");

    operation_request_t *request = (operation_request_t *) object;

    if (strlen (request->values._1) > 0)
    {
        sat_status_set (&status, true, "");
    }

    return status;
}

static sat_status_t operation_request_criteria_value_1_is_a_number (void *object)
{
    sat_status_t status = sat_status_set (&status, true, "");

    operation_request_t *request = (operation_request_t *) object;

    for (size_t i = 0; i < strlen (request->values._1); i ++)
    {
        if  (isdigit (request->values._1 [i]) == 0)
        {
            sat_status_set (&status, false, "value 1 is not a number");
            break;
        }
    }

    return status;
}

static sat_status_t operation_request_criteria_value_2_is_not_empty (void *object)
{
    sat_status_t status = sat_status_set (&status, false, "value 2 is empty");

    operation_request_t *request = (operation_request_t *)object;

    if (strlen (request->values._2) > 0)
    {
        sat_status_set (&status, true, "");
    }

    return status;
}

static sat_status_t operation_request_criteria_value_2_is_a_number (void *object)
{
    sat_status_t status = sat_status_set (&status, true, "");

    operation_request_t *request = (operation_request_t *) object;

    for (size_t i = 0; i < strlen (request->values._2); i ++)
    {
        if  (isdigit (request->values._2 [i]) == 0)
        {
            sat_status_set (&status, false, "value 2 is not a number");
            break;
        }
    }

    return status;
}

static sat_status_t operation_request_criteria_type_is_not_empty (void *object)
{
    sat_status_t status = sat_status_set (&status, false, "type is empty");

    operation_request_t *request = (operation_request_t *)object;

    if (strlen (request->type) > 0)
    {
        sat_status_set (&status, true, "");
    }

    return status;
}

static sat_status_t operation_request_criteria_type_exists (void *object)
{
    sat_status_t status = sat_status_set (&status, false, "type is empty");

    operation_request_t *request = (operation_request_t *)object;

    if (strcmp (request->type, "sum") == 0      ||
        strcmp (request->type, "subb") == 0     ||
        strcmp (request->type, "multiply") == 0 ||
        strcmp (request->type, "divide") == 0)
    {
        sat_status_set (&status, true, "");
    }

    return status;
}