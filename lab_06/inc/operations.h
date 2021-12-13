#ifndef _OPERATIONS_H_

#define _OPERATIONS_H_

#include "errors.h"
#include "colors.h"
#include "structures.h"
#include "avl_oper.h"
#include <stdlib.h>
#include <stdio.h>
#include "timer.h"
#include "io.h"
#include "hash.h"

#define INT_MAX 2147483647

node_avl_t *balance_tree(tree_arr *tree_src);
node_t *create_node(int n);
node_t *insert(node_t *cur_node, int n);
node_avl_t *build_tree(int *values, int start, int end);
node_t *find_bin(node_t **node, int num_to_find, int *cmp_count);
int pop_from_bin(node_t **node, int num_to_del);
int check_avl(node_t *node);
int make_prime(int n);
size_t tree_size(node_t *node);
int pop_from_file(char *filename, int num_to_del);
size_t file_size(char *filename);
void free_tree(node_t *node);
void free_avl_tree(node_avl_t *node);
void get_avg_time(char *filename, uint64_t *bin_time, uint64_t *bal_time, uint64_t *hash_time, uint64_t *file_time);
void read_nodes(node_t *src, int *values, int *size);
size_t tree_avl_size(node_avl_t *node);
int bfactor(node_avl_t* p);
#endif