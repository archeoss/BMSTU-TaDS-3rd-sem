#ifndef _README_H_

#define _README_H_

#define NO_ERROR 0
#define INPUT_ERROR 1
#define DATA_ERROR 2

#define N_DB 300
#define DB_COUNT 10
#define JUNK_SIZE 25

#include "apartment.h"
#include <time.h>

void table_init(apartment *, apartment_key *, apartment_key *, int);
int add_field(apartment *table, apartment_key *table_key, apartment_key *unsorted_table_key, int len);
int delete_field(apartment *table, apartment_key *table_key, apartment_key *, int len, int pos);

void copykey(apartment_key *k_orig, apartment_key *k_copy, int len);
void copytable(apartment *t_orig, apartment *t_copy, int len);

void update_keys(apartment_key *table_key, int len);
void update_uns_keys(apartment *table,apartment_key *table_key, int len);
void key_add_square(apartment_key *table_key, int squre_price, int len);

clock_t gettime_table(apartment *table, int len);
clock_t gettime_simple(apartment_key *table, int len);
clock_t gettime_qsort(apartment_key *table, int len);
clock_t gettime_qtable(apartment *table, int len);

#endif