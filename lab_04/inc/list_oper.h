#ifndef _LIST_OPER_H_

#define _LIST_OPER_H_

#include <stdlib.h>
#include "structures.h"
#include "errors.h"


int node_create(node_t **stack, float item);
int push_address(frmem_t **mem, node_t *stack);
float pop_node(node_t **stack);
void pop_address(frmem_t **mem, node_t *node);

void clear_stack(node_t *stack);
void clear_addresses(frmem_t *mem);

void delete_addresses(frmem_t **mem, node_t *, int n);
#endif