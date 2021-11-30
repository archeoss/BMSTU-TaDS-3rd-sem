#include "test_ao.h"

void test_arr(int n)
{
    clock_t begin, end, result = 0;
    float *array = calloc(n, sizeof(float));
    arr_t qa;
    qa.array = qa.bottom = qa.head = array;
    qa.size = n;
    qa.count = 0;
    for (int i = 0; i < n; i++)
    {
        begin = clock();
        push_arr(&qa, 1);
        end = clock();
        result += end - begin;
    }

    printf(GREEN"Затрачено времени на %d добавлений: %ld clocks\n"CLR, n, result);
    
    result = 0;
    for (int i = 0; i < n; i++)
    {
        begin = clock();
        popa_arr(&qa);
        end = clock();
        result += end - begin;
    }

    printf(GREEN"Затрачено времени на %d удалений: %ld clocks\n"CLR, n, result);
    printf(GREEN"Memory: %ld \n"CLR, sizeof(float) * n);

    free(qa.array);
}

void test_list(int n)
{
    clock_t begin, end, result = 0;
    list_t ql;
    ql.bottom = ql.head = NULL;
    ql.count = 0;
    for (int i = 0; i < n; i++)
    {
        begin = clock();
        push_list(&ql, 1);
        end = clock();
        result += end - begin;
    }

    printf(GREEN"Затрачено времени на %d добавлений: %ld clocks\n"CLR, n, result);
    
    result = 0;
    for (int i = 0; i < n; i++)
    {
        begin = clock();
        popa_list(&ql);
        end = clock();
        result += end - begin;
    }

    printf(GREEN"Затрачено времени на %d удалений: %ld clocks\n"CLR, n, result);
    printf(GREEN"Memory: %ld \n"CLR, sizeof(node_t) * n);
}