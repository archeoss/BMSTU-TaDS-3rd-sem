#ifndef _IO_H_

#define _IO_H_

#include "errors.h"
#include "colors.h"
#include "structures.h"
#include "arr_io.h"
#include "arr_oper.h"
#include "list_io.h"
#include "list_oper.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int initial_setup(float **stack_ptr, int *size);

void print_menu();
void print_error(int);
int test_it();

void clean_input();

#endif