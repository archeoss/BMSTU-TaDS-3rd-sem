#ifndef _IO_H_

#define _IO_H_

#include "errors.h"
#include "colors.h"
#include "structures.h"
#include "arr_struct.h"
#include "list_struct.h"
#include "constants.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

int initial_setup(float **, float **, int *size);

void print_menu();
void print_error(int);
int read_inter(inter_t *to_arrive, inter_t *to_proccess);

void clean_input();
void print_res_per_hundred(int processed, size_t avg_size_a, size_t avg_size_b, size_t cur_size_a, size_t cur_size_b);
void print_result(meta_t meta_a, meta_t meta_b, int a_count, int b_count, float freetime);

#endif