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

typedef struct node_avl
{
    int data;
    int height;
    struct node_avl *left;
    struct node_avl *right;
} node_avl_t;

typedef struct
{
    node_t *arr;
    int size;
} tree_arr;

typedef struct
{
    node_avl_t *arr;
    int size;
} tree_avl;

typedef struct 
{
    int *hash_table;
    int *is_occupied;
    int size;
    int hash_num;
} hash_t;


#endif