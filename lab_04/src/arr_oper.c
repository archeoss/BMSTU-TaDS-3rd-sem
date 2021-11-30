#include "arr_oper.h"

float popa_down(float **stack)
{
    return *((*stack)--);
}

float popa_up(float **stack)
{
    return *((*stack)++);
}