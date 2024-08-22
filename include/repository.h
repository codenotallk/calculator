#ifndef REPOSITORY_H_
#define REPOSITORY_H_

#include <operation.h>
#include <sat.h>
#include <stdint.h>

#define REPOSITORY_CSV_FORMAT       "%s,%d,%d,%d,%ld\n"
#define REPOSITORY_CSV_FILENAME     "report.txt"

void repository_save (operation_t *operation);
sat_array_t *repository_get (uint32_t offset);

#endif/* REPOSITORY_H_ */
