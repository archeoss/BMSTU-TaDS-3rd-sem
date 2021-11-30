#include "operations.h"

void arr_setup(arr_t *qa_a, arr_t *qa_b, int size)
{
    qa_a->size = qa_b->size = size;
    qa_a->bottom = qa_a->head = qa_a->array;
    qa_b->bottom = qa_b->head = qa_b->array;
    qa_a->count = qa_b->count = 0;
}

void list_setup(list_t *qa_a, list_t *qa_b)
{
    qa_a->bottom = qa_a->head = NULL;
    qa_b->bottom = qa_b->head = NULL;
    qa_a->count = qa_b->count = 0;
}

double generate_time(inter_t inter)
{
    double res = inter.begin + (rand() % ((inter.end - inter.begin) * 1000 + 1)) / 1000.0;

    return res;
}

float get_expected(inter_t to_arrive, inter_t to_process)
{
    float inter_tta = (float)(to_arrive.end + to_arrive.begin) / 2;
    float inter_ttp = (float)(to_process.end + to_process.begin) / 2;
    float res = inter_tta > inter_ttp ? inter_tta * PROCESSED_AMOUNT : inter_ttp * PROCESSED_AMOUNT;
    
    return res;
}

void clear_queue(list_t *ql)
{
    while (ql->bottom)
    {
        node_t *tmp = ql->bottom;
        ql->bottom = ql->bottom->next;
        free(tmp);
        (ql->count)--;
    }
}