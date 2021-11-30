#ifndef _OPERATIONS_H_

#define _OPERATIONS_H_

#include "errors.h"
#include <stdlib.h>
#include <stdio.h>
#include "structures.h"
#include "mem_alloc.h"
#include <time.h>
int parse_matr(matrix *, parse *);
void parse_sum(parse *pars, parse *parse_res, clock_t *);

void fill_en(parse *pars);
int std_sum(matrix *matr, matrix *res, clock_t *);

int found_total_len(parse *pars, int *total_len);
void fill_cols_en(parse *parse_res, matrix *matrix_res);

#endif