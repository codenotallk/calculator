#include <application.h>
#include <string.h>
#include <handlers.h>
#include <file_repository.h>
#include <mysql_repository.h>

sat_status_t calculator_init (calculator_t *object)
{
    sat_status_t status = sat_status_set (&status, false, "calculator init error");

    if (object != NULL)
    {
        memset (object, 0, sizeof (calculator_t));

        sat_status_set (&status, true, "");
    }

    return status;
}

sat_status_t calculator_open (calculator_t *object, calculator_args_t *args)
{
    sat_status_t status = sat_status_set (&status, false, "calculator open error");

    if (object != NULL && args != NULL)
    {
        do
        {
            // static file_repository_t file;

            // if (file_repository_init (&file) == false)
            //     break;

            // object->repository = file.base;

            static mysql_repository_t mysql;

            if (mysql_repository_open (&mysql, &(mysql_repository_args_t)
                                                     {
                                                        .database = "report_db",
                                                        // .hostname = "mysql_db",
                                                        .hostname = "127.0.0.1",
                                                        .user = "root",
                                                        .password = "root",
                                                        .port = 3306
                                                     }));

            object->repository = mysql.base;

            status = sat_webserver_open (&object->webserver, &(sat_webserver_args_t)
                                                             {
                                                                .endpoint_amount = 1,
                                                                .mode = sat_webserver_mode_dynamic,
                                                                .folder = ".",
                                                                .port = "1234",
                                                                .threads_amount = "1"
                                                             });

            if (sat_status_get_result (&status) == false)
                break;

            status = sat_webserver_add_endpoint (&object->webserver,
                                                 "/v1/health",
                                                 "GET",
                                                 calculator_health_handler,
                                                 NULL);
            
            if (sat_status_get_result (&status) == false)
                break;

            status = sat_webserver_add_endpoint (&object->webserver,
                                                 "/v1/calculate",
                                                 "GET",
                                                 calculator_calculate_handler,
                                                 &object->repository);

            if (sat_status_get_result (&status) == false)
                break;

            status = sat_webserver_add_endpoint (&object->webserver,
                                                 "/v1/report",
                                                 "GET",
                                                 calculator_report_handler,
                                                 &object->repository);


        } while (false);
    }

    return status;
}

sat_status_t calculator_run (calculator_t *object)
{
    sat_status_t status = sat_status_set (&status, false, "calculator run error");

    if (object != NULL)
    {
        printf ("Server is running at port %s\n", object->webserver.port);

        status = sat_webserver_run (&object->webserver);
    }

    return status;
}

sat_status_t calculator_close (calculator_t *object)
{
    sat_status_t status = sat_status_set (&status, false, "calculator close error");

    if (object != NULL)
    {
        status = sat_webserver_close (&object->webserver);
    }

    return status;
}