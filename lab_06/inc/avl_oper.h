#ifndef _AVL_OPERATIONS_H_

#define _AVL_OPERATIONS_H_

#include "errors.h"
#include "colors.h"
#include "structures.h"
#include "operations.h"
#include <stdlib.h>
#include <stdio.h>
#include "timer.h"
#include "io.h"
#include "hash.h"

#define INT_MAX 2147483647

node_avl_t *create_avl_node(int n);
int height(node_avl_t* p);
node_avl_t *find_avl(node_avl_t **node, int num_to_find, int *cmp_count);
int pop_from_avl(node_avl_t **node, int num_to_del);
void replace_avl_node(node_avl_t **node, int *cmp_count);
node_avl_t* balance(node_avl_t* p);
int remove_me(node_avl_t **node, int num_to_del, int *cmp_count);

#endif