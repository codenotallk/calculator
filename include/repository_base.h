#ifndef REPOSITORY_H_
#define REPOSITORY_H_

#include <operation.h>
#include <sat.h>
#include <stdint.h>

typedef struct
{
    void *object;
    void (*save) (void *object, operation_t *operation);
    sat_array_t *(*get) (void *object, uint32_t offset);
} repository_base_t;


#endif/* REPOSITORY_H_ */
