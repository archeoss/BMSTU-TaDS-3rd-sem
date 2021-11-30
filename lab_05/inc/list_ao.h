#ifndef _LIST_AO_H_

#define _LIST_AO_H_

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "io.h"
#include "structures.h"
#include "arr_struct.h"
#include "errors.h"
#include "colors.h"
#include "operations.h"
#include "constants.h"

void simulation_list(list_t *, list_t *);
float popa_list(list_t *ql);
void push_list(list_t *ql, float);
void push_list_back(list_t *ql);

void add_address(list_t *ql, mem_t *free_memory);
void check_address(size_t address, mem_t *free_memory, meta_t *meta);

#endif