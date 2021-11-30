#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "showme.h"
#include "apartment.h"

#define NO_ERROR 0
#define INPUT_ERROR 1
#define DATA_ERROR 2

void print_table(apartment *table, int len)
{
    for (int i = 0; i < len; i++)
    {
        printf("--------------------------------------\n");
        printf("| %-3d: %s", i + 1, table[i].address);
        printf("| Squares: %-5hd, Room count: %-5hd, Price per square: %-15d\n", table[i].square, table[i].room_count, table[i].square_price);
        if (table[i].t == 0)
            printf("| Type: primary, Trim: %-5hd\n", table[i].tp.prim.trim);
        else
            printf("| Type: secondary, Build date: %-5hd, Owner Count: %-5hd, Count of last Owner: %-5hd, Was animal? : %-5hd\n", table[i].tp.sec.build_date, table[i].tp.sec.owner_count, table[i].tp.sec.last_owner_count, table[i].tp.sec.was_animal);
    }
}

void print_by_key(apartment *table, apartment_key *table_key, int len)
{
    for (int j = 0; j < len; j++)
    {
        int i = table_key[j].index_orig;
        printf("--------------------------------------\n");
        printf("| %-3d: %s", i + 1, table[i].address);
        printf("| Squares: %-5hd, Room count: %-5hd, Price per square: %-15d\n", table[i].square, table[i].room_count, table[i].square_price);
        if (table[i].t == 0)
            printf("| Type: primary, Trim: %-5hd\n", table[i].tp.prim.trim);
        else
            printf("| Type: secondary, Build date: %-5hd, Owner Count: %-5hd, Count of last Owner: %-5hd, Was animal? : %-5hd\n", table[i].tp.sec.build_date, table[i].tp.sec.owner_count, table[i].tp.sec.last_owner_count, table[i].tp.sec.was_animal);
    }
}

void compare_qsort_table(clock_t time_key, clock_t time_table, uint64_t mem_key, uint64_t mem_table)
{
    
    printf("| Time spend with qsort key: %ld\n", time_key);
    printf("| Memory spend with qsort key: %ld\n", mem_key);

    printf("| Time spend with bubble Table sort: %ld\n", time_table);
    printf("| Memory spend with bubble Table sort: %ld\n", mem_table);

    printf("|\n");
    printf("Efficency of qsort: %.2lf%%\n", (1  - (double)time_key / (double)time_table) * 100);
}

void compare_simple_table(clock_t time_key, clock_t time_table, uint64_t mem_key, uint64_t mem_table)
{
    printf("| Time spend with simple sort key: %ld\n", time_key);
    printf("| Memory spend with simple sort key: %ld\n", mem_key);

    printf("| Time spend with bubble Table sort: %ld\n", time_table);
    printf("| Memory spend with bubble Table sort: %ld\n", mem_table);

    printf("|\n");
    printf("Efficency of simple sort: %.2lf%%\n", (1  - (double)time_key / (double)time_table) * 100);
}
void compare_qsort_qtable(clock_t time_key, clock_t time_table, uint64_t mem_key, uint64_t mem_table)
{
    
    printf("| Time spend with qsort key: %ld\n", time_key);
    printf("| Memory spend with qsort key: %ld\n", mem_key);

    printf("| Time spend with qsort Table sort: %ld\n", time_table);
    printf("| Memory spend with qsort Table sort: %ld\n", mem_table);

    printf("|\n");
    printf("Efficency of qsort: %.2lf%%\n", (1  - (double)time_key / (double)time_table) * 100);
}

void compare_simple_qtable(clock_t time_key, clock_t time_table, uint64_t mem_key, uint64_t mem_table)
{
    printf("| Time spend with simple sort key: %ld\n", time_key);
    printf("| Memory spend with simple sort key: %ld\n", mem_key);

    printf("| Time spend with qsort Table sort: %ld\n", time_table);
    printf("| Memory spend with qsort Table sort: %ld\n", mem_table);

    printf("|\n");
    printf("Efficency of qsort Table: %.2lf%%\n", (1  - (double)time_table / (double)time_key) * 100);
}

void compare_two_sort(clock_t time_key1, clock_t time_key2, uint64_t mem_key1, uint64_t mem_key2)
{   
    printf("| Time spend with init sort: %ld\n", time_key1);
    printf("| Memory spend with init sort: %ld\n", mem_key1);

    printf("| Time spend with simple sort: %ld\n", time_key2);
    printf("| Memory spend with simple sort: %ld\n", mem_key2);

    printf("|\n");
    printf("Efficency of qsort: %.2lf%%\n", (1  - (double)time_key1 / (double)time_key2) * 100);
}

void find_by_req(apartment *table, int len)
{
    int begin, end;
    printf("Введите два числа в качестве ценового диапазона: ");
    int rc = scanf("%d %d", &begin, &end);
    printf("\n");
    if (rc == 2)
    {
        short flag = 1;
        for (int i = 0; i < len; i++)
            if (table[i].room_count == 2 && table[i].t == 1 && table[i].tp.sec.was_animal == 0 && table[i].square_price >= begin && table[i].square_price <= end)
            {
                flag = 0;
                printf("--------------------------------------\n");
                printf("| %-3d: %s", i + 1, table[i].address);
                printf("| Squares: %-5hd, Room count: %-5hd, Price per square: %-15d\n", table[i].square, table[i].room_count, table[i].square_price);
                if (table[i].t == 0)
                    printf("| Type: primary, Trim: %-5hd\n", table[i].tp.prim.trim);
                else
                    printf("| Type: secondary, Build date: %-5hd, Owner Count: %-5hd, Count of last Owner: %-5hd, Was animal? : %-5hd\n", table[i].tp.sec.build_date, table[i].tp.sec.owner_count, table[i].tp.sec.last_owner_count, table[i].tp.sec.was_animal);
            }
        if (flag)
            printf("No such apartments ;(\n");
    }
    else
        printf("Invalid input");
}