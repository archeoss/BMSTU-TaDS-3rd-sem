#ifndef _STRUCTURES_H_

#define _STRUCTURES_H_

#include <stdlib.h>

typedef struct interval
{
    int begin;
    int end;
} inter_t;

typedef struct metadata
{
    int processed, returned;
    float worktime;
    size_t avg_size;
    float expected;
    int reused_addresses, new_addresses;
} meta_t;

#endif