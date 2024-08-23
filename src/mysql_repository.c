#include <mysql_repository.h>
#include <string.h>

#define MYSQL_REPOSITORY_MAX_OBJECTS      20

typedef enum 
{
    repository_index_id = 0,
    repository_index_type,
    repository_index_value_1,
    repository_index_value_2,
    repository_index_result,
    repository_index_date,
} repository_index_t;

static void mysql_repository_save (void *object, operation_t *operation);
static sat_array_t *mysql_repository_get (void *object, interval_t *interval);
static bool mysql_repository_is_args_valid (mysql_repository_args_t *args);
static void mysql_repository_set_context (mysql_repository_t *object, mysql_repository_args_t *args);
static bool mysql_repository_arg_field_is_valid (const char *field);
static sat_status_t mysql_repository_get_connection (mysql_repository_t *object);

static void mysql_repository_on_result_set (char **data, int columns, void *__data);

static void mysql_repository_query_builder (char *query, interval_t *interval);

bool mysql_repository_open (mysql_repository_t *object, mysql_repository_args_t *args)
{
    bool status = false;

    if (object != NULL && args != NULL)
    {
        
        if (mysql_repository_is_args_valid (args) == true)
        {
            mysql_repository_set_context (object, args);

            object->base.object = object;
            object->base.save = mysql_repository_save;
            object->base.get = mysql_repository_get;

            status = true;
        }

    }

    return status;
}

static bool mysql_repository_is_args_valid (mysql_repository_args_t *args)
{
    bool status = false;

    if (args != NULL &&
        mysql_repository_arg_field_is_valid (args->database) == true &&
        mysql_repository_arg_field_is_valid (args->hostname) == true &&
        mysql_repository_arg_field_is_valid (args->password) == true &&
        mysql_repository_arg_field_is_valid (args->user) == true)
    {
        status = true;
    }

    return status;
}

static void mysql_repository_set_context (mysql_repository_t *object, mysql_repository_args_t *args)
{
    object->hostname = args->hostname;
    object->database = args->database;
    object->password = args->password;
    object->user = args->user;
    object->port = args->port;
}

static void mysql_repository_save (void *object, operation_t *operation)
{
    mysql_repository_t *mysql = (mysql_repository_t *) object;

    const char *query = "insert into reports_tb (type, value_1, value_2, result, data) values ('%s', %d, %d, %d, %ld);";

    char buffer [256] = {0};

    do
    {
        sat_status_t status = mysql_repository_get_connection (mysql);
        if (sat_status_get_result (&status) == false)
        {
            printf ("%s\n", sat_status_get_motive (&status));
            break;
        }        

        time_t now = sat_time_get_epoch_now ();

        snprintf (buffer, sizeof (buffer) - 1, query, operation->type,
                                                  operation->values._1,
                                                  operation->values._2,
                                                  operation->result,
                                                  now);

        status = sat_mysql_execute (&mysql->mysql, buffer);
        if (sat_status_get_result (&status) == false)
        {
            printf ("%s\n", sat_status_get_motive (&status));
            break;
        }

        sat_mysql_close (&mysql->mysql);

        sat_time_get_date_by_epoch (operation->date, OPERATION_DATE_SIZE, OPERATION_DATE_FORMAT, now);

    } while (false);
}

static sat_array_t *mysql_repository_get (void *object, interval_t *interval)
{
    mysql_repository_t *mysql = (mysql_repository_t *) object;

    sat_array_t *array = NULL;

    char query [216] = {0};

    sat_status_t status = sat_array_create (&array, &(sat_array_args_t)
                                                    {
                                                        .mode = sat_array_mode_static,
                                                        .object_size = sizeof (operation_t),
                                                        .size = MYSQL_REPOSITORY_MAX_OBJECTS
                                                    });
    if (sat_status_get_result (&status) == true)
    {
        status = mysql_repository_get_connection (mysql);

        if (sat_status_get_result (&status) == true)
        {
            mysql_repository_query_builder (query, interval);

            sat_mysql_execute (&mysql->mysql, query);

            sat_mysql_result_set (&mysql->mysql, mysql_repository_on_result_set, array);

            sat_mysql_close (&mysql->mysql);
        }
    }

    return array;
}

static bool mysql_repository_arg_field_is_valid (const char *field)
{
    bool status = false;

    if (field != NULL &&
        strlen (field) > 0)
    {
        status = true;
    }

    return status;
}

static sat_status_t mysql_repository_get_connection (mysql_repository_t *object)
{
    sat_status_t status;

    do 
    {
        status = sat_mysql_init (&object->mysql);

        if (sat_status_get_result (&status) == false)
        {
            printf ("%s\n", sat_status_get_motive (&status));
            break;
        }

        status = sat_mysql_open (&object->mysql, &(sat_mysql_args_t)
                                                 {
                                                    .database = object->database,
                                                    .hostname = object->hostname,
                                                    .password = object->password,
                                                    .user = object->user,
                                                    .port = object->port
                                                 });

        if (sat_status_get_result (&status) == false)
        {
            printf ("%s\n", sat_status_get_motive (&status));
            break;
        }
    } while (false);

    return status;
}

static void mysql_repository_on_result_set (char **data, int columns, void *__data)
{
    sat_array_t *array = (sat_array_t *) __data;

    time_t date;

    operation_t operation;

    memset (&operation, 0, sizeof (operation_t));

    strncpy (operation.type, data [repository_index_type], OPERATION_TYPE_SIZE);
    operation.values._1 = atoi (data [repository_index_value_1]);
    operation.values._2 = atoi (data [repository_index_value_2]);
    operation.result    = atoi (data [repository_index_result]);

    date = atoi (data [repository_index_date]);

    sat_time_get_date_by_epoch (operation.date,
                                OPERATION_DATE_SIZE,
                                OPERATION_DATE_FORMAT,
                                date);

    sat_array_add (array, &operation);
}

static void mysql_repository_query_builder (char *query, interval_t *interval)
{
    const char *sql = "select * from reports_tb ";
    char format [128] = {0};

    strncat (query, sql, strlen (sql));

    if (interval->date.from > 0 && interval->date.to > 0)
    {
        snprintf (format, sizeof (format) - 1, "where data between %d and %d ",
                                                interval->date.from,
                                                interval->date.to);

        strncat (query, format, strlen (format));

        memset (format, 0, sizeof (format));
    }

    else if (interval->date.from > 0)
    {
        snprintf (format, sizeof (format) - 1, "where data >= %d ",
                                                interval->date.from);
                                                

        strncat (query, format, strlen (format));

        memset (format, 0, sizeof (format));
    }

    else if (interval->date.to > 0)
    {
        snprintf (format, sizeof (format) - 1, "where data <= %d ",
                                                interval->date.to);
                                                

        strncat (query, format, strlen (format));

        memset (format, 0, sizeof (format));
    }

    snprintf (format, sizeof (format) - 1, "order by id desc limit 20 offset %d",
                                           interval->offset);
    strncat (query, format, strlen (format));
}