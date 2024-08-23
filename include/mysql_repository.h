#ifndef MYSQL_REPOSITORY_H_
#define MYSQL_REPOSITORY_H_

#include <repository_base.h>

typedef struct 
{
    repository_base_t base;
    sat_mysql_t mysql;
    const char *database;
    const char *hostname;
    const char *password;
    const char *user;
    uint16_t port;
} mysql_repository_t;

typedef struct
{
    const char *database;
    const char *hostname;
    const char *password;
    const char *user;
    uint16_t port;
} mysql_repository_args_t;

bool mysql_repository_open (mysql_repository_t *object, mysql_repository_args_t *args);

#endif/* MYSQL_REPOSITORY_H_ */
