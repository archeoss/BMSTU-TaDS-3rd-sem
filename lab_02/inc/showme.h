#ifndef _SHOWME_H_

#define _SHOWME_H_

#define NO_ERROR 0
#define KEY_ERROR 1
#define INCORRECT_DATA_ERROR 2
#define NOT_FOUND 3

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "apartment.h"

#include <time.h>

void print_by_key(apartment *table, apartment_key *table_key, int len);
void print_table(apartment *table, int len);

void compare_two_sort(clock_t time_key1, clock_t time_key2, uint64_t mem_key1, uint64_t mem_key2);
void compare_simple_table(clock_t time_key, clock_t time_table, uint64_t mem_key, uint64_t mem_table);
void compare_qsort_table(clock_t time_key, clock_t time_table, uint64_t mem_key, uint64_t mem_table);
void compare_simple_qtable(clock_t time_key, clock_t time_table, uint64_t mem_key, uint64_t mem_table);
void compare_qsort_qtable(clock_t time_key, clock_t time_table, uint64_t mem_key, uint64_t mem_table);

void find_by_req(apartment *table, int len);

#endif