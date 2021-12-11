#ifndef _OPERATIONS_H_

#define _OPERATIONS_H_

#include "errors.h"
#include "colors.h"
#include "structures.h"
#include "operations.h"
#include <stdlib.h>
#include <stdio.h>

node_t *balance_tree(tree_arr *);
node_t *create_node(int n);
node_t *insert(node_t *cur_node, int n);
node_t *build_tree(int *values, int start, int end);
node_t *find_bin(node_t **node, int num_to_find, int *cmp_count);
int pop_from_bin(node_t **node, int num_to_del);
size_t tree_size(node_t *node);
int pop_from_file(char *filename, int num_to_del);
size_t file_size(char *filename);
void free_tree(node_t *node);
void read_nodes(node_t *src, int *values, int *size);

#endif