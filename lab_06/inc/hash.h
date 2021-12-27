#ifndef _HASH_H_

#define _HASH_H_

#include "errors.h"
#include "colors.h"
#include "structures.h"
#include "operations.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define HASH_RATE 1.2
#define MAX_TIMES 100

int gen_hashtable(char *filename, hash_t *hash_table, int mode);
int hash_find(hash_t *hash_table, int num_to_find, int *comprasions, int (*hash_func)(hash_t *, int));
int pop_from_hash(hash_t *hash_table, int num_to_del, int mode);
int hash_func_a(hash_t *hash_table, int a);
int hash_func_b(hash_t *hash_table, int a);
int hash_find_a(hash_t *hash_table, int num_to_find, int *comprasions);
int hash_find_b(hash_t *hash_table, int num_to_find, int *comprasions);


#endif