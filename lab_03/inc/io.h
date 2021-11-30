#ifndef _IO_H_

#define _IO_H_

#include "mem_alloc.h"
#include "errors.h"
#include "constants.h"
#include "structures.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void print_as_std(parse *pars, int n, int m);
int input_matrix(int *matrix, int n, int m);
void generate_matrix(int *matrix, int n, int m, int perc);
int load_matrix(int *matrix, char *filename, int n, int m);
void print_matrix(int **matrix, int n, int m);
int get_size(int *n, int *m);
int sparse_input(int **matrix, int n, int m, int un_zero);
void print_parsed(parse *pars);

#endif