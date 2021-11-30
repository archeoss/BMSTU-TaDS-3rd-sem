#include "list_oper.h"

int node_create(node_t **stack, float item)
{
    int error_code = NO_ERROR;
    node_t *tmp = malloc(sizeof(node_t));
    if (!tmp)
        error_code = ALLOC_ERROR;
    else
    {
        tmp->next = *stack;
        *stack = tmp;
        (*stack)->data = item;
    }

    return error_code;
}

float pop_node(node_t **stack)
{
    node_t *tmp = *stack;
    float popped = (*stack)->data;
    *stack = (*stack)->next;
    free(tmp);

    return popped;
}

int push_address(frmem_t **mem, node_t *stack)
{
    int error_code = NO_ERROR;
    frmem_t *tmp = malloc(sizeof(frmem_t));
    if (!tmp)
        error_code = ALLOC_ERROR;
    else
    {
        tmp->next = *mem;
        *mem = tmp;
        (*mem)->address = (size_t)stack;
    }

    return error_code;
}

void pop_address(frmem_t **mem, node_t *stack)
{
    frmem_t *cur_node = *mem;
    short flag = 1;
    while (cur_node->next && flag)
    {
        if (cur_node->next->address == (long)stack)
        {
            frmem_t *tmp = cur_node->next;
            cur_node->next = cur_node->next->next;
            flag = 0;
            free(tmp);
        }
        else
            cur_node = cur_node->next;
    }
}

void delete_addresses(frmem_t **mem, node_t *stack, int n)
{
    int i = 0;
    while (i++ < n && *mem != NULL)
    {
        pop_address(mem, stack);
        stack = stack->next;
    }
}

void clear_stack(node_t *stack)
{
    while (stack)
    {
        node_t *tmp = stack;
        stack = stack->next;
        free(tmp);
    }
}

void clear_addresses(frmem_t *mem)
{
    while (mem)
    {
        frmem_t *tmp = mem;
        mem = mem->next;
        free(tmp);
    }
}