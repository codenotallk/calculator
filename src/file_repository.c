#include <file_repository.h>
#include <sat.h>
#include <stdio.h>
#include <string.h>

#define FILE_REPOSITORY_MAX_OBJECTS      20

static void repository_set_offset (sat_file_t *file, uint32_t offset, char *buffer, uint32_t size);
static void repository_get_object_from (operation_t *object, char *buffer);
static void file_repository_save (void *object, operation_t *operation);
static sat_array_t *file_repository_get (void *object, interval_t *interval);

bool file_repository_init (file_repository_t *object)
{
    bool status = false;

    if (object != NULL)
    {
        object->base.object = object;
        object->base.save = file_repository_save,
        object->base.get = file_repository_get;

        status = true;
    }

    return status;
}

static void file_repository_save (void *object, operation_t *operation)
{
    (void) object;

    char buffer [512] = {0};

    sat_file_t file;

    time_t now = sat_time_get_epoch_now ();

    sat_file_open (&file, REPOSITORY_CSV_FILENAME, sat_file_mode_append);

    snprintf (buffer, sizeof (buffer) - 1, REPOSITORY_CSV_FORMAT, operation->type,
                                                                  operation->values._1,
                                                                  operation->values._2,
                                                                  operation->result,
                                                                  now);

    sat_file_write (&file, buffer, strlen (buffer));

    sat_file_close (&file);

    sat_time_get_date_by_epoch (operation->date, OPERATION_DATE_SIZE, OPERATION_DATE_FORMAT, now);
}

static sat_array_t *file_repository_get (void *object, interval_t *interval)
{
    (void) object;

    sat_array_t *array = NULL;
    sat_file_t file;

    char line [1024];

    sat_file_open (&file, REPOSITORY_CSV_FILENAME, sat_file_mode_read);

    repository_set_offset (&file, interval->offset, line, sizeof (line));

    sat_status_t status = sat_array_create (&array, &(sat_array_args_t)
                                                    {
                                                        .size = FILE_REPOSITORY_MAX_OBJECTS,
                                                        .object_size = sizeof (operation_t),
                                                        .mode = sat_array_mode_static
                                                    });

    if (sat_status_get_result (&status) == true)
    {
        for (uint8_t i = 0; i < FILE_REPOSITORY_MAX_OBJECTS && sat_file_readline (&file, line, sizeof (line)) != false; i ++)
        {
            operation_t operation;

            repository_get_object_from (&operation, line);
            sat_array_add (array, (void *)&operation);
        }
    }

    return array;
}

static void repository_set_offset (sat_file_t *file, uint32_t offset, char *buffer, uint32_t size)
{
    for (uint32_t i = 0; i < offset; i++)
    {
        if (sat_file_readline (file, buffer, size) == false)
            break;
    }
}

static void repository_get_object_from (operation_t *object, char *buffer)
{
    memset (object, 0, sizeof (operation_t));

    char *token;

    token = strtok (buffer, ",");
    strncpy (object->type, token, OPERATION_TYPE_SIZE);

    token = strtok (NULL, ",");
    object->values._1 = atoi (token);

    token = strtok (NULL, ",");
    object->values._2 = atoi (token);

    token = strtok (NULL, ",");
    object->result = atoi (token);

    token = strtok (NULL, ",");
    sat_time_get_date_by_epoch (object->date,
                                OPERATION_DATE_SIZE,
                                OPERATION_DATE_FORMAT,
                                atoi (token));
}