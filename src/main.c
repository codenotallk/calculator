#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <application.h>

int main(int argc, char *argv[])
{
    sat_status_t status;

    calculator_t calculator;
    calculator_args_t args =
    {
        .dummy = 1
    };

    do
    {
        status = calculator_init (&calculator);
        if (sat_status_get_result (&status) == false)
        {
            break;
        }

        status = calculator_open (&calculator, &args);
        if (sat_status_get_result (&status) == false)
        {
            break;
        }

        status = calculator_run (&calculator);
        if (sat_status_get_result (&status) == false)
        {
            break;
        }

        else
            status = calculator_close (&calculator);

    } while (false);

    printf ("%s\n", sat_status_get_motive (&status));

    return sat_status_get_result (&status) == true ? EXIT_SUCCESS : EXIT_FAILURE;
}