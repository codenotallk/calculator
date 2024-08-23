#ifndef INTERVAL_H_
#define INTERVAL_H_

#include <sat.h>

typedef struct 
{
    struct
    {
        uint32_t from;
        uint32_t to;
    } date;

    uint32_t offset;

} interval_t;

sat_status_t interval_init (interval_t *object);

#endif/* INTERVAL_H_ */
