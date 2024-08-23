#ifndef FILE_REPOSITORY_H_
#define FILE_REPOSITORY_H_

#include <repository_base.h>

#define REPOSITORY_CSV_FORMAT       "%s,%d,%d,%d,%ld\n"
#define REPOSITORY_CSV_FILENAME     "report.txt"

typedef struct 
{
    repository_base_t base;
} file_repository_t;

bool file_repository_init (file_repository_t *object);

#endif/* FILE_REPOSITORY_H_ */
