#ifndef _IO_H_

#define _IO_H_

#include "errors.h"
#include "colors.h"
#include "structures.h"
#include "operations.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

void print_tree(node_t *tree, int spaces);
int get_count(FILE *f);
void print_hash(hash_t *hash_table);
int read_tree(FILE *f, tree_arr *tree);


#endif