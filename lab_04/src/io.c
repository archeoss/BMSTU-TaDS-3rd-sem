#include "io.h"

int initial_setup(float **stack_ptr, int *size)
{
    int error_code = NO_ERROR;
    printf(CYAN"Initial setup\n"CLR);
    printf(CYAN"Input size of array (for array realisation of stack, size > 1): "CLR);
    int rc = scanf("%d", size);
    if (!rc || *size < 1)
        error_code = INVALID_INPUT;
    else
    {
        *stack_ptr = malloc(*size * sizeof(float));
        if (!(*stack_ptr))
            error_code  = ALLOC_ERROR;
    }

    return error_code;
}

void print_menu()
{
    printf(BLUE"--------------------------------------\n"CLR);
    printf(BBLUE"| List of Commands  \n|\n"CLR);
    printf(BLUE"| 1. ARRAY: Input float numbers into first(start-of-array) stack\n"CLR);
    printf(BLUE"| 2. ARRAY: Input float numbers into second(end-of-array) stack \n"CLR);
    printf(BLUE"| 3. ARRAY: Delete number from first stack \n"CLR);
    printf(BLUE"| 4. ARRAY: Delete number from second stack \n"CLR);
    printf(BLUE"| 5. ARRAY: Show both stacks \n"CLR);
    printf(BLUE"| 6. LIST: Input float numbers in stack \n"CLR);
    printf(BLUE"| 7. LIST: Delete number from stack \n"CLR);
    printf(BLUE"| 8. LIST: Show current stack \n"CLR);
    printf(BLUE"| 9. LIST: Show list of free'd addresses \n"CLR);
    printf(BLUE"| 10. LIST: Time Test \n"CLR);
    printf(BLUE"| 0: Exit \n");
    printf(BLUE"--------------------------------------\n"CLR);
    printf(PURPLE"| Input command: "CLR);
}

void print_error(int error_code)
{
    if (error_code == INVALID_INPUT)
        printf(RED"Invalid input\n"CLR);
    else if (error_code == STACK_OVERFLOW)
        printf(RED"STACK OVERFLOW!\n"CLR);
    else if (error_code == ALLOC_ERROR)
        printf(RED"Allocation error\n"CLR);
    else if (error_code == POP_EMPTY_STACK)
        printf(RED"Stack already empty\n"CLR);
    else if (error_code == NOT_ALLOCATED)
        printf(RED"Matrix not allocated\n"CLR);
    else if (error_code == UNKNOWN_COMMAND)
        printf(RED"Unknown command\n"CLR);
}

void clean_input()
{
    while(getchar()!='\n')
    {}
}

int test_it()
{
    printf(PURPLE"Input numbers count: "CLR);
    int size;
    int error_code = NO_ERROR;
    int rc = scanf("%d", &size);
    printf("\n");
    float *stack_arr;
    clock_t begin, end, t;
    srand(time(NULL));
    if (rc && size > 0)
    {
        stack_arr = malloc(size * sizeof(float));
        if (!stack_arr)
            error_code  = ALLOC_ERROR;
        printf("ARRAY: Time of addition of %d\n", size);
        begin = clock();
        for (int i = 0; i < size; i++)
            push(&stack_arr, rand() % 100);
        end = clock();
        t = end - begin;
        printf("%ld clocks\n", t);
        printf("ARRAY: Time of delete of %d\n", size);
        begin = clock();
        for (int i = 0; i < size; i++)
            popa_down(&stack_arr);
        end = clock();
        t = end - begin;
        printf("%ld clocks\n", t);

        node_t *stack_list = NULL;
        printf("LIST: Time of addition of %d\n", size);
        begin = clock();
        for (int i = 0; i < size; i++)
            node_create(&stack_list, rand() % 100);
        end = clock();
        t = end - begin;
        printf("%ld clocks\n", t);
        printf("LIST: Time of delete of %d\n", size);
        begin = clock();
        for (int i = 0; i < size; i++)
            pop_node(&stack_list);
        end = clock();
        t = end - begin;
        printf("%ld clocks\n", t);
        
        clear_stack(stack_list);
        free(stack_arr);
    }
    
    return error_code;
}