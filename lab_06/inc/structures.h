#ifndef _STRUCTURES_H_

#define _STRUCTURES_H_

#include <stdlib.h>

#define A 1
#define B 2

typedef struct tree_node
{
    int data;
    struct tree_node *left;
    struct tree_node *right;
} node_t;

typedef struct
{
    node_t *arr;
    int size;
} tree_arr;

typedef struct 
{
    int *hash_table;
    int *is_occupied;
    int size;
    int hash_num;
} hash_t;


#endif