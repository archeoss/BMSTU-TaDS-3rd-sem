#ifndef _SORT_H_

#define _SORT_H_

#define NO_ERROR 0
#define KEY_ERROR 1
#define INCORRECT_DATA_ERROR 2
#define NOT_FOUND 3

#include <stdio.h>
#include <stdlib.h>
#include "apartment.h"
void sort_key(apartment_key *table, size_t num, size_t size, int (*compare)(const void *, const void *));
void sort_table(apartment *table, size_t num, size_t size, int (*compare)(const void *, const void *));
void qsort_key(apartment_key *table, const int first, const int last);
void qsort_table(apartment *table, const int first, const int last);



int comp(const int *i, const int *j);
#endif