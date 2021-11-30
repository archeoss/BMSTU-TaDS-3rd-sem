#include "io.h"

int initial_setup(float **queue_ptr_a, float **queue_ptr_b, int *size)
{
    int error_code = NO_ERROR;
    printf(CYAN"Initial setup\n"CLR);
    printf(CYAN"Input size of array (for array realisation of queue, size > 1): "CLR);
    int rc = scanf("%d", size);
    if (!rc || *size < 1)
        error_code = INVALID_INPUT;
    else
    {
        *queue_ptr_a = calloc(*size, sizeof(float));
        if (!(*queue_ptr_a))
            error_code  = ALLOC_ERROR;
        else
        {
            *queue_ptr_b = calloc(*size, sizeof(float));
            if (!(*queue_ptr_b))
            {
                error_code  = ALLOC_ERROR;
                free(*queue_ptr_a);
                *queue_ptr_a = NULL;
            }
        }
    }

    return error_code;
}

void print_menu()
{
    printf(BLUE"--------------------------------------\n"CLR);
    printf(BBLUE"| List of Commands  \n|\n"CLR);
    printf(BLUE"| 1. ARRAY: Вывести результаты работы ОА \n"CLR);
    printf(BLUE"| 2. ARRAY: Вывести характеристику работу ОА\n"CLR);
    printf(BLUE"| 3. LIST: Вывести результаты работы ОА \n"CLR);
    printf(BLUE"| 4. LIST: Вывести характеристику работы ОА \n"CLR);
    printf(BLUE"| 0: Exit \n");
    printf(BLUE"--------------------------------------\n"CLR);
    printf(PURPLE"| Input command: "CLR);
}

void print_error(int error_code)
{
    if (error_code == INVALID_INPUT)
        printf(RED"Invalid input\n"CLR);
    else if (error_code == STACK_OVERFLOW)
        printf(RED"QUEUE OVERFLOW!\n"CLR);
    else if (error_code == ALLOC_ERROR)
        printf(RED"Allocation error\n"CLR);
    else if (error_code == UNKNOWN_COMMAND)
        printf(RED"Unknown command\n"CLR);
}

void clean_input()
{
    while(getchar()!='\n')
    {}
}

static int get_inter(inter_t *inter)
{
    int error_code = NO_ERROR;
    int rc = scanf("%d%d", &inter->begin, &inter->end);
    if (rc != 2)
        error_code = INVALID_INPUT;
    else if (inter->begin < 0 || inter->end < 0)
        error_code = NEGATIVE_INTERVAL;

    if (inter->begin > inter->end)
    {
        inter->begin ^= inter->end;
        inter->end ^= inter->begin;
        inter->begin ^= inter->end;
    }

    return error_code;
}

int read_inter(inter_t *to_arrive, inter_t *to_process)
{
    int error_code = NO_ERROR;
    printf(BLUE"Введите интервал прибытия заявки (2 цифры через пробел)\n"CLR);
    error_code = get_inter(to_arrive);

    if (!error_code)
    {    
        printf(BLUE"Введите интервал обработки заявки (2 цифры через пробел)\n"CLR);
        error_code = get_inter(to_process);        
    }

    return error_code;
}

void print_res_per_hundred(int processed, size_t avg_size_a, size_t avg_size_b, size_t cur_size_a, size_t cur_size_b)
{
    printf(PURPLE"Количество обработанных заявок: %d\n\n"CLR, processed);
    printf(YELLOW"Средняя длина первой очереди: %ld\n"CLR, avg_size_a);
    printf(YELLOW"Текущая длина первой очереди: %ld\n\n"CLR, cur_size_a);
    printf(YELLOW"Средняя длина второй очереди: %ld\n"CLR, avg_size_b);
    printf(YELLOW"Текущая длина второй очереди: %ld\n\n"CLR, cur_size_b);
}

void print_result(meta_t meta_a, meta_t meta_b, int a_count, int b_count, float freetime)
{
    printf(BGREEN"Рабочее время автомата: %lf (ожидаемое рабочее время: %lf, погрешность: %lf%%)\n\n"CLR, meta_a.worktime + meta_b.worktime + freetime, meta_a.expected, fabs(1 - (meta_a.worktime + meta_b.worktime + freetime) / meta_a.expected) * 100);

    printf(GREEN"Число вошедших заявок: %d\n"CLR, meta_a.processed + meta_b.processed + a_count + b_count);
    printf(GREEN"Число вошедших заявок первого типа: %d\n"CLR, meta_a.processed + a_count);
    printf(GREEN"Число вошедших заявок второго типа: %d\n\n"CLR, meta_b.processed + b_count);
    
    printf(BGREEN"Число вышедших заявок: %d\n"CLR, meta_a.processed + meta_b.processed);
    printf(GREEN"Число вышедших заявок первого типа: %d\n"CLR, meta_a.processed);
    printf(GREEN"Число вышедших заявок второго типа: %d\n\n"CLR, meta_b.processed);
    
    printf(GREEN"Число возвратившихся заявок: %d\n"CLR, meta_b.returned);
    printf(GREEN"Число срабатываний автомата: %d\n"CLR, meta_b.processed + meta_a.processed + meta_b.returned);
    printf(GREEN"Время простоя автомата: %lf\n" CLR, freetime);
}

