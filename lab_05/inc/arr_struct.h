#ifndef _ARR_STRUCT_H_

#define _ARR_STRUCT_H_

#include "structures.h"

typedef struct
{
    float *array;
    float *head;
    float *bottom;
    int size;
    int count;
    inter_t to_arrive, to_process;
} arr_t;


#endif