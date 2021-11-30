#include "structures.h"
#include "io.h"
#include "arr_io.h"
#include "arr_oper.h"
#include "errors.h"
#include "colors.h"
#include "arr_io.h"
#include "list_oper.h"
#include "list_io.h"
#include <time.h>

int main(void)
{
    float *array = NULL, *stack_b_array, *stack_a_array;
    int size;
    int input_size;
    int command = -1;
    clock_t begin, end, t = 0;
    node_t *stack = NULL;
    frmem_t *mem = NULL;
    int error_code = initial_setup(&array, &size); //stack allocation
    if (error_code)
    {
        printf(RED"Initial setup failed! E./a   xiting the program\n"CLR);
        return INVALID_INPUT;
    }

    stack_a_array = array - 1;
    stack_b_array = array + size;
    do
    {
        print_menu();
        error_code = NO_ERROR;
        int rc = scanf("%d", &command);
        if (rc)
        {
            switch (command)
            {
            case 1:
                printf(PURPLE"Input numbers count: "CLR);
                rc = scanf("%d", &input_size);
                printf("\n");
                if (rc && input_size > 0)
                {
                    if (stack_a_array + input_size < stack_b_array)
                        error_code = array_input(&stack_a_array, input_size);
                    else
                    {
                        printf(RED"Free space remaining: %ld element(s)\n"CLR, stack_b_array - stack_a_array - 1);
                        error_code = STACK_OVERFLOW;
                    }
                }
                else
                    error_code = INVALID_INPUT;
                break;
            
            case 2:
                printf(PURPLE"Input numbers count: "CLR);
                rc = scanf("%d", &input_size);
                printf("\n");
                if(rc && input_size > 0)
                {
                    if (stack_b_array - input_size > stack_a_array)
                        error_code = array_input_rev(&stack_b_array, input_size);
                    else
                    {
                        printf(RED"Free space remaining: %ld element(s)\n"CLR, stack_b_array - stack_a_array - 1);
                        error_code = STACK_OVERFLOW;
                    }
                }
                else
                    error_code = INVALID_INPUT;
                break;

            case 3:
                if (array - 1 < stack_a_array)
                    printf(GREEN"Deleted element: %f\n"CLR, popa_down(&stack_a_array));
                else
                    error_code = POP_EMPTY_STACK;
                break;

            case 4:
                if (array + size > stack_b_array)
                    printf(GREEN"Deleted element: %f\n"CLR, popa_up(&stack_b_array));
                else
                    error_code = POP_EMPTY_STACK;
                break;

            case 5:
                printf(YELLOW"First stack:\n"CLR);
                if (array - 1 < stack_a_array)
                {
                    begin = clock();
                    print_arr(stack_a_array, array - 1);
                    end = clock();
                    t = end - begin;
                    printf("Time spent (clocks): %ld\n", t);
                }
                else
                    printf("Stack Empty\n");
                
                printf(YELLOW"Second stack:\n"CLR);
                if (array + size > stack_b_array)
                {
                    begin = clock();
                    print_arr(stack_b_array, array + size);
                    end = clock();
                    t = end - begin;
                    printf("Time spent (clocks): %ld\n", t);
                }
                else
                    printf("Stack Empty\n");
                break;

            case 6:
                printf(PURPLE"Input numbers count: "CLR);
                rc = scanf("%d", &input_size);
                printf("\n");
                
                if (rc && input_size > 0)
                {
                    list_push(&stack, input_size);
                    delete_addresses(&mem, stack, input_size);
                }
                else
                    error_code = INVALID_INPUT;
                break;

            case 7:
                if (stack)
                {
                    push_address(&mem, stack);
                    begin = clock();
                    pop_node(&stack);
                    end = clock();
                    t = end - begin;
                    printf("Time spent (clocks): %ld\n", t);
                }
                else
                    error_code = POP_EMPTY_STACK;
                break;

            case 8:
                begin = clock();
                if (stack)
                {
                    begin = clock();
                    print_stack(stack);
                    end = clock();
                    t = end - begin;
                    printf("Time spent (clocks): %ld\n", t);
                }
                else
                    printf("Stack is Empty\n");
                break;
                
            case 9:
                if (mem)
                    print_mem(mem);
                else
                    printf("There is none free'd addresses\n");
                break;
                
            case 10:
                test_it();
                break;

            case 0:
                break;

            default:
                error_code = UNKNOWN_COMMAND;
                break;
            }
        }
        else
            error_code = INVALID_INPUT;
        print_error(error_code);
        clean_input();
    } while (command);
//    printf("Time spent (clocks): %ld\n", t);
//    printf("Memory spent: %ld\n", sizeof(node_t) * size);                
    free(array);
    clear_addresses(mem);
    clear_stack(stack);

    return 0;
}
