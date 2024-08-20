#include <repository.h>
#include <sat.h>
#include <stdio.h>
#include <string.h>

void repository_save (operation_t *operation)
{
    char buffer [512] = {0};

    sat_file_t file;

    sat_file_open (&file, REPOSITORY_CSV_FILENAME, sat_file_mode_append);

    snprintf (buffer, sizeof (buffer) - 1, REPOSITORY_CSV_FORMAT, operation->type,
                                                                  operation->values._1,
                                                                  operation->values._2,
                                                                  operation->result,
                                                                  sat_time_get_epoch_now());

    sat_file_write (&file, buffer, strlen (buffer));

    sat_file_close (&file);
}