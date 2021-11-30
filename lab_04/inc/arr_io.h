#ifndef _ARR_IO_H_

#define _ARR_IO_H_

#include <stdio.h>
#include <stdlib.h>
#include "colors.h"
#include "errors.h"
#include <time.h>

void print_arr(float *stack_b, float *stack_e);
void push(float **stack, float tmp);
int array_input_rev(float **stack, int size);
int array_input(float **stack, int size);
void push_rev(float **stack, float tmp);

#endif