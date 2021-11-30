#include "arr_struct.h"
#include "list_struct.h"
#include "io.h"
#include "errors.h"
#include "colors.h"
#include <time.h>
#include "structures.h"
#include "arr_ao.h"
#include "list_ao.h"
#include "operations.h"
#include "test_ao.h"
int main(void)
{
    int size = 0, n;
    int command = -1;
    arr_t qa_a, qa_b;
    list_t ql_a, ql_b;
    int error_code = initial_setup(&qa_a.array, &qa_b.array, &size); //queues allocation

    if (error_code)
    {
        printf(RED"Initial setup failed! Exiting the program\n"CLR);
        return INVALID_INPUT;
    }
    
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
                arr_setup(&qa_a, &qa_b, size);
                printf(YELLOW"Первая очередь\n"CLR);
                error_code = read_inter(&qa_a.to_arrive, &qa_a.to_process);
                if (!error_code)
                {
                    printf(YELLOW"Вторая очередь\n"CLR);
                    error_code = read_inter(&qa_b.to_arrive ,&qa_b.to_process);
                }
                if (!error_code)
                    simulation_arr(&qa_a, &qa_b);
                break;
            case 2:
                printf(YELLOW"Введите количество повторений: "CLR);
                rc = scanf("%d", &n);
                printf("\n");
                if (rc && n > 0)
                    test_arr(n);
                else
                    error_code = INVALID_INPUT;
                break;

            case 3:
                list_setup(&ql_a, &ql_b);
                printf(YELLOW"Первая очередь\n"CLR);
                error_code = read_inter(&ql_a.to_arrive, &ql_a.to_process);
                if (!error_code)
                {
                    printf(YELLOW"Вторая очередь\n"CLR);
                    error_code = read_inter(&ql_b.to_arrive ,&ql_b.to_process);
                }
                if (!error_code)
                {
                    simulation_list(&ql_a, &ql_b);
                
                    clear_queue(&ql_a);
                    clear_queue(&ql_b);
                }
                break;

            case 4:
                printf(YELLOW"Введите количество повторений: "CLR);
                rc = scanf("%d", &n);
                printf("\n");
                if (rc && n > 0)
                    test_list(n);
                else
                    error_code = INVALID_INPUT;
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
    
    free(qa_a.array);
    free(qa_b.array);

    return 0;
}
