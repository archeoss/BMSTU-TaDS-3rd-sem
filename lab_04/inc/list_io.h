#ifndef _LIST_IO_H_

#define _LIST_IO_H_

#include <stdio.h>
#include <stdlib.h>
#include "errors.h"
#include "colors.h"
#include "structures.h"
#include "list_oper.h"
#include <time.h>

int list_push(node_t **stack, int n);

void print_stack(node_t *stack);
void print_mem(frmem_t *mem);
#endif