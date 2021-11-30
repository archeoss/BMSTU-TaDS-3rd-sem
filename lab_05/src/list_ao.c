#include "list_ao.h"

float popa_list(list_t *ql)
{
    float res = ql->bottom->work_time;
    node_t *tmp = ql->bottom;
    ql->bottom = ql->bottom->next;
    free(tmp);
    (ql->count)--;
    
    return res;
}


void push_list(list_t *ql, float i)
{
    node_t *tmp = malloc(sizeof(node_t));
    if (tmp)
    {
        ql->count++;
        if (ql->count == 1)
            ql->bottom = tmp;
        else
            ql->head->next = tmp;
        ql->head = tmp;
        tmp->work_time = i;
        tmp->next = NULL;
    }
    else
        printf(RED"Невозможно добавить элемент, очередь переполнена\n"CLR);
}

void push_list_back(list_t *ql)
{
    ql->head->next = ql->bottom;
    ql->head = ql->bottom;
    ql->bottom = ql->bottom->next;
}

void add_address(list_t *ql, mem_t *free_memory)
{
    mem_t *new = malloc(sizeof(mem_t));
    new->address = (size_t)ql->bottom;
    new->next = free_memory;
    free_memory = new;
}

void check_address(size_t address, mem_t *free_memory, meta_t *meta)
{
    mem_t *prev = NULL;
    mem_t *cur = free_memory;
    int flag = 1;
    while (cur && flag)
    {
        if (cur->address == address)
        {
            flag = 0;
            meta->reused_addresses++;
            if (prev)
                prev->next = cur->next;
            free(cur);
        }
        prev = cur;
        cur = cur->next;
    }
    if (flag)
        meta->new_addresses++;
}

static void process(list_t *ql_a, list_t *ql_b, meta_t *meta_a, meta_t *meta_b, float *tta, float *remained_time, float *freetime, int *prev, mem_t *free_memory)
{
    int tmp = meta_a->processed;
    while (*tta > 0 && meta_a->processed < PROCESSED_AMOUNT)
    {
        if (!ql_a->count && !ql_b->count)
        {
            *freetime += *tta;
            *tta = 0;
            *remained_time = 0;
        }
        else if (ql_a->count)
        {
            if (*prev == SECOND && *remained_time > 0)
            {
                if (ql_b->count)
                {
                    meta_a->worktime += *remained_time;
                    push_list_back(ql_b);
                    meta_b->returned++;
                }
                *remained_time = 0;
            }
            *prev = FIRST;

            if (ql_a->bottom->work_time - *remained_time <= *tta)
            {
                *tta -= ql_a->bottom->work_time - *remained_time;
                add_address(ql_a, free_memory);
                float ttt = popa_list(ql_a);
                meta_a->worktime += ttt - *remained_time;
                meta_a->processed++;
                *remained_time = 0;
                meta_a->avg_size += ql_a->count;
            }
            else
            {
                meta_a->worktime += *tta;
                *remained_time += *tta;
                *tta = 0;
            }
        }
        else
        {
            *prev = SECOND;
            if (ql_b->bottom->work_time - *remained_time <= *tta)
            {
                *tta -= ql_b->bottom->work_time - *remained_time;
                add_address(ql_b, free_memory);
                float ttt = popa_list(ql_b);
                meta_b->worktime += ttt;
                *remained_time = 0;
                meta_b->processed++;
                meta_b->avg_size += ql_b->count;
            }
            else
            {
                *remained_time += *tta;
                *tta = 0;
            }
        }
        if (meta_a->processed % 100 == 0 && meta_a->processed != tmp)
        {
            tmp = meta_a->processed;
            print_res_per_hundred(meta_a->processed, meta_a->avg_size/meta_a->processed, meta_b->avg_size/meta_a->processed, ql_a->count, ql_b->count);
        }


    }

}

void simulation_list(list_t *ql_a, list_t *ql_b)
{
    mem_t *free_memory = NULL;

    meta_t meta_a, meta_b;
    meta_a.avg_size = meta_b.avg_size = 0;
    meta_a.processed = meta_b.processed = 0;
    meta_a.returned = meta_b.returned = 0;
    meta_a.worktime = meta_b.worktime = 0;
    meta_a.new_addresses = meta_b.new_addresses = 0;
    meta_a.reused_addresses = meta_b.reused_addresses = 0;

    meta_a.expected = get_expected(ql_a->to_arrive, ql_a->to_process);
    float freetime = 0;
    srand(time(NULL));
    float tta_a = 0, tta_b = 0;
    float remained_time = 0;
    int prev = FIRST;
    
    while (meta_a.processed < PROCESSED_AMOUNT)
    {
        if (tta_a == 0)
            tta_a = generate_time(ql_a->to_arrive);
        if (tta_b == 0)
            tta_b = generate_time(ql_b->to_arrive);
    
        if (tta_a < tta_b)
        {
            tta_b -= tta_a;
            process(ql_a, ql_b, &meta_a, &meta_b, &tta_a, &remained_time, &freetime, &prev, free_memory);
            push_list(ql_a, generate_time(ql_a->to_process));
            check_address((size_t)ql_a->bottom, free_memory, &meta_a);
        }
        else if (tta_a > tta_b)
        {
            tta_a -= tta_b;
            process(ql_a, ql_b, &meta_a, &meta_b, &tta_b, &remained_time, &freetime, &prev, free_memory);
            push_list(ql_b, generate_time(ql_b->to_process));
            check_address((size_t)ql_b->bottom, free_memory, &meta_b);
        }
        else  // might be useless
        {
            process(ql_a, ql_b, &meta_a, &meta_b, &tta_a, &remained_time, &freetime, &prev, free_memory);
            tta_a = tta_b = 0;
            push_list(ql_b, generate_time(ql_b->to_process));
            push_list(ql_a, generate_time(ql_a->to_process));
            check_address((size_t)ql_a->bottom, free_memory, &meta_a);
            check_address((size_t)ql_b->bottom, free_memory, &meta_b);
        } 
    }

    print_result(meta_a, meta_b, ql_a->count, ql_b->count, freetime);
    printf(GREEN"Переиспользованных адрессов: %d\n"CLR, meta_a.reused_addresses + meta_b.reused_addresses);
    printf(GREEN"Новых адрессов: %d\n"CLR, meta_a.new_addresses + meta_b.new_addresses);
}

