#include "list_io.h"

int list_push(node_t **stack, int n)
{
    int error_code = NO_ERROR;
    int i = 0;
    clock_t ttt = 0;
    while (i++ < n && error_code == NO_ERROR)
    {
        float tmp;
        int rc = scanf("%f", &tmp);
        if (!rc)
            error_code = INVALID_INPUT;
        else
        {
            clock_t begin = clock();
            error_code = node_create(stack, tmp);
            clock_t end = clock();
            ttt += end - begin;
        }
    }
    printf(GREEN"Number of stack'd elements: %d\n"CLR, i - 1);
    printf(GREEN"Time spent: %ld\n"CLR, ttt);
    
    return error_code; 
}

void print_stack(node_t *stack)
{
    node_t *cur_node = stack;
    printf(YELLOW"Stack content:\n"CLR);
    while (cur_node != NULL)
    {
        printf("%f at %zx\n", cur_node->data, (long)cur_node);
        cur_node = cur_node->next;
    }
}

void print_mem(frmem_t *mem)
{
    frmem_t *cur_node = mem;
    printf(YELLOW"Free'd addresses:\n"CLR);
    while (cur_node != NULL)
    {
        printf("%zx \n", cur_node->address);
        cur_node = cur_node->next;
    }
    printf("\n");
}