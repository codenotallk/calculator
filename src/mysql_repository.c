#include <mysql_repository.h>
#include <string.h>

static void mysql_repository_save (void *object, operation_t *operation);
static sat_array_t *mysql_repository_get (void *object, uint32_t offset);
static bool mysql_repository_is_args_valid (mysql_repository_args_t *args);
static void mysql_repository_set_context (mysql_repository_t *object, mysql_repository_args_t *args);
static bool mysql_repository_arg_field_is_valid (const char *field);

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
        sat_status_t status = sat_mysql_init (&mysql->mysql);
        if (sat_status_get_result (&status) == false)
        {
            printf ("%s\n", sat_status_get_motive (&status));
            break;
        }

        status = sat_mysql_open (&mysql->mysql, &(sat_mysql_args_t)
                                                {
                                                    .database = mysql->database,
                                                    .hostname = mysql->hostname,
                                                    .password = mysql->password,
                                                    .user = mysql->user,
                                                    .port = mysql->port
                                                });

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

static sat_array_t *mysql_repository_get (void *object, uint32_t offset)
{
    mysql_repository_t *mysql = (mysql_repository_t *) object;
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