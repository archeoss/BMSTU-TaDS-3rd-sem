#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "readme.h"
#include "apartment.h"

#define NO_ERROR 0
#define INPUT_ERROR 1
#define DATA_ERROR 2

void sort_table(apartment *table, size_t num, size_t size, int (*compare)(int *, int *))
{
    if (table != NULL && size > 0 && num > 0 && compare != NULL)
    {
        for (size_t i = 0; i < num - 1; i++)
        {
            for (size_t j = 0; j < num - 1 - i; j++)
            {
                int res = (*compare)(&table[j].square_price, &table[j + 1].square_price);
                if (res > 0)
                {
                    apartment tmp = table[j];
                    table[j] = table[j + 1];
                    table[j + 1] = tmp;
                }
            }
        }
    }
}

void qsort_table(apartment *table, const int first, const int last)
{
    int i, j, pivot;
    i = first;
    j = last;
    pivot = table[(i + j) / 2].square_price;
    apartment tmp;

    while (i <= j)
    {
        while (table[i].square_price < pivot)
            i++;
        while (table[j].square_price > pivot)
            j--;
        if (i <= j)
        {
            tmp = table[i];
            table[i] = table[j];
            table[j] = tmp;
            i++;
            j--;
        }
    }

    if (j > first)
        qsort_table(table, first, j);
    if (i < last)
        qsort_table(table, i, last);
    
}

void sort_key(apartment_key *table, size_t num, size_t size, int (*compare)(const void *, const void *))
{
    if (table != NULL && size > 0 && num > 0 && compare != NULL)
    {
        for (size_t i = 0; i < num - 1; i++)
        {
            for (size_t j = 0; j < num - 1 - i; j++)
            {
                int res = (*compare)(&table[j].square_price, &table[j + 1].square_price);
                if (res > 0)
                {
                    apartment_key tmp = table[j];
                    table[j] = table[j + 1];
                    table[j + 1] = tmp;
                }
            }
        }
    }
}

void qsort_key(apartment_key *table, const int first, const int last)
{
    int i, j, pivot;
    i = first;
    j = last;
    pivot = table[(i + j) / 2].square_price;
    apartment_key tmp;

    while (i <= j)
    {
        while (table[i].square_price < pivot)
            i++;
        while (table[j].square_price > pivot)
            j--;
        if (i <= j)
        {
            tmp = table[i];
            table[i] = table[j];
            table[j] = tmp;
            i++;
            j--;
        }
    }

    if (j > first)
        qsort_key(table, first, j);
    if (i < last)
        qsort_key(table, i, last);
    
}


int comp(const int *i, const int *j)
{
    return *i - *j;
}