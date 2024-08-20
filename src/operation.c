#include <operation.h>
#include <string.h>

void operation_calculate (operation_t *object)
{
    if (strcmp (object->type, "sum") == 0)
    {
        object->result = object->values._1 + object->values._2;
    }

    else if (strcmp (object->type, "subb") == 0)
    {
        object->result = object->values._1 - object->values._2;
    }

    else if (strcmp (object->type, "multiply") == 0)
    {
        object->result = object->values._1 * object->values._2;
    }

    else if (strcmp (object->type, "divide") == 0)
    {
        object->result = 0;

        if (object->values._2 != 0)
            object->result = object->values._1 / object->values._2;
    }
}