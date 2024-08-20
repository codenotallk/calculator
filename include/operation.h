#ifndef OPERATION_H_
#define OPERATION_H_

#define OPERATION_TYPE_SIZE     30

typedef struct 
{
    struct 
    {
        int _1;
        int _2;
    } values;

    int result;

    char type [OPERATION_TYPE_SIZE + 1];

} operation_t;

void operation_calculate (operation_t *object);

#endif/* OPERATION_H_ */
