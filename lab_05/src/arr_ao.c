#include "arr_ao.h"

float popa_arr(arr_t *qa)
{
    float res = *(qa->bottom);
    qa->bottom++;
    (qa->count)--;
    if (qa->bottom >= qa->array + qa->size)
        qa->bottom = qa->array;

    return res;
}

void push_arr(arr_t *qa, float i)
{
    if (qa->count < qa->size)
    {
        qa->count++;
        *(qa->head) = i;
        qa->head++;
        if (qa->head >= qa->array + qa->size)
            qa->head = qa->array;
    }
    else
        printf(RED"Невозможно добавить элемент, очередь переполнена\n"CLR);
}

void push_arr_back(arr_t *qa)
{
    *(qa->head) = *(qa->bottom);
    qa->head++;
    qa->bottom++;
    if (qa->head >= qa->array + qa->size)
        qa->head = qa->array;
    if (qa->bottom >= qa->array + qa->size)
        qa->bottom = qa->array;
}

static void process(arr_t *qa_a, arr_t *qa_b, meta_t *meta_a, meta_t *meta_b, float *tta, float *remained_time, float *freetime, int *prev)
{
    int tmp = meta_a->processed;
    while (*tta > 0 && meta_a->processed < PROCESSED_AMOUNT)
    {
        if (!qa_a->count && !qa_b->count)
        {
            *freetime += *tta;
            *tta = 0;
            *remained_time = 0;
        }
        else if (qa_a->count)
        {
            if (*prev == SECOND && *remained_time > 0)
            {
                if (qa_b->count)
                {
                    meta_a->worktime += *remained_time;
                    push_arr_back(qa_b);
                    meta_b->returned++;
                }
                *remained_time = 0;
            }
            *prev = FIRST;

            if (*(qa_a->bottom) - *remained_time <= *tta)
            {
                *tta -= *(qa_a->bottom) - *remained_time;
                float ttt = popa_arr(qa_a);
                meta_a->worktime += ttt - *remained_time;
                meta_a->processed++;
                *remained_time = 0;
                meta_a->avg_size += qa_a->count;
                meta_b->avg_size += qa_b->count;
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
            if (*(qa_b->bottom) - *remained_time <= *tta)
            {
                *tta -= *(qa_b->bottom) - *remained_time;
                float ttt = popa_arr(qa_b);
                meta_b->worktime += ttt;
                *remained_time = 0;
                meta_b->processed++;
                meta_a->avg_size += qa_a->count;
                meta_b->avg_size += qa_b->count;
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
            print_res_per_hundred(meta_a->processed, meta_a->avg_size / (meta_a->processed + meta_b->processed), meta_b->avg_size / (meta_a->processed + meta_b->processed), qa_a->count, qa_b->count);
        }


    }

}

void simulation_arr(arr_t *qa_a, arr_t *qa_b)
{
    meta_t meta_a, meta_b;
    meta_a.avg_size = meta_b.avg_size = 0;
    meta_a.processed = meta_b.processed = 0;
    meta_a.returned = meta_b.returned = 0;
    meta_a.worktime = meta_b.worktime = 0;
    meta_a.expected = get_expected(qa_a->to_arrive, qa_a->to_process);
    float freetime = 0;
    srand(time(NULL));
    float tta_a = 0, tta_b = 0;
    float remained_time = 0;
    int prev = FIRST;
    while (meta_a.processed < PROCESSED_AMOUNT)
    {
        if (tta_a == 0)
            tta_a = generate_time(qa_a->to_arrive);
        if (tta_b == 0)
            tta_b = generate_time(qa_b->to_arrive);
        if (tta_a < tta_b)
        {
            tta_b -= tta_a;
            process(qa_a, qa_b, &meta_a, &meta_b, &tta_a, &remained_time, &freetime, &prev);
            push_arr(qa_a, generate_time(qa_a->to_process));
        }
        else if (tta_a > tta_b)
        {
            tta_a -= tta_b;
            process(qa_a, qa_b, &meta_a, &meta_b, &tta_b, &remained_time, &freetime, &prev);
            push_arr(qa_b, generate_time(qa_b->to_process));
        }
        else  // might be useless
        {
            process(qa_a, qa_b, &meta_a, &meta_b, &tta_a, &remained_time, &freetime, &prev);
            tta_a = tta_b = 0;
            push_arr(qa_b, generate_time(qa_b->to_process));
            push_arr(qa_a, generate_time(qa_a->to_process));
        }
 
    }
    print_result(meta_a, meta_b, qa_a->count, qa_b->count, freetime);
    
}

