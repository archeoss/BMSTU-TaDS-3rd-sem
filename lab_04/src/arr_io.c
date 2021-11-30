#include "arr_io.h"

int array_input(float **stack, int size)
{
    int error_code = NO_ERROR;
    int i = 0;
    clock_t ttt = 0;
    while (i++ < size && error_code == NO_ERROR)
    {
        float tmp;
        int rc = scanf("%f", &tmp);
        if (!rc)
            error_code = INVALID_INPUT;
        else
        {
            clock_t begin = clock();
            push(stack, tmp);
            clock_t end = clock();
            ttt += end - begin;
        }
    }
    printf(GREEN"Number of stack'd elements: %d\n"CLR, i - 1);
    printf(GREEN"Time spent: %ld\n"CLR, ttt);
    
    return error_code;
}

void push(float **stack, float tmp)
{
    *(++(*stack)) = tmp;
}

void push_rev(float **stack, float tmp)
{
    *(--(*stack)) = tmp;
}

int array_input_rev(float **stack, int size)
{
    int error_code = NO_ERROR;
    int i = 0;
    clock_t ttt = 0;
    while (i++ < size && error_code == NO_ERROR)
    {
        float tmp;
        int rc = scanf("%f", &tmp);
        if (!rc)
            error_code = INVALID_INPUT;
        else
        {
            clock_t begin = clock();
            push_rev(stack, tmp);
            clock_t end = clock();
            ttt += end - begin;
        }
    }
    printf(GREEN"Number of stack'd elements: %d\n"CLR, i - 1);
    printf(GREEN"Time spent: %ld\n"CLR, ttt);

    return error_code;
}

void print_arr(float *stack_b, float *stack_e)
{
    while (stack_b > stack_e)
        printf("%f\n", *(stack_b--));

    while (stack_b < stack_e)
        printf("%f\n", *(stack_b++));
}
