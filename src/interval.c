#include <interval.h>
#include <string.h>

sat_status_t interval_init (interval_t *object)
{
    sat_status_t status = sat_status_set (&status, false, "Interval create error");

    if (object != NULL)
    {
        memset (object, 0, sizeof (interval_t));

        sat_status_set (&status, true, "");
    }

    return status;
}