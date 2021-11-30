#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "readme.h"
#include "showme.h"
#include "apartment.h"
#include "sort.h"

#define LEN_TABLE 350
#define N_SORTS 10
void print_menu();

int main(void)
{
    apartment table[LEN_TABLE] = {0};
    apartment_key table_key[LEN_TABLE] = {0};
    apartment_key unsorted_table_key[LEN_TABLE] = {0};
    apartment_key table_copy[LEN_TABLE];
    short flag_key = 0;
    clock_t time2_sort;
    clock_t time1_sort;
    int type;
    uint64_t mem1 = 0;
    uint64_t mem2 = 0;
    uint64_t mem_table = 0;
    int len = N_DB;
    table_init(table, table_key, unsorted_table_key, N_DB);
    int command;
    do
    {
        print_menu();
        int rc = scanf(" %d", &command);
        printf("\n--------------------------------------\n");
        if (rc == 0)
            printf("|Invalid Command\n--------------------------------------\n");
        else
            switch (command)
            {
                case 1:
                    if (len < LEN_TABLE)
                    {
                        flag_key = 0;
                        rc = add_field(table, table_key, unsorted_table_key, len);
                        if (rc == NO_ERROR)
                            len++;
                        else
                            printf("|Invalid Input\n");
                    }
                    else
                        printf("TABLE OVERFLOW\n Delete a Field before add a new one\n");
                    break;
                case 2:
                    printf("Print position (start from 1): ");
                    int pos = 0;
                    rc = scanf("%d", &pos);
                    printf("\n");
                    if (rc == 1)
                    {
                        rc = delete_field(table, table_key, unsorted_table_key, len, pos);
                        if (rc == NO_ERROR)
                            len--;
                        else
                            printf("Incorrect position\n");
                    }
                    else
                        printf("Incorrect position\n");
                    break;
                case 3:
                    printf("Choose type of sort(0 - Fast, 1 - Simple): ");
                    type = 0;
                    rc = scanf("%d", &type);
                    printf("\n");
                    if (rc && (type == 1 || type == 0))
                    {  
                        flag_key = 1;
                        if (type == 1)
                        {
                            copykey(unsorted_table_key, table_copy, len);
                            sort_key(table_copy, (size_t)len, sizeof(unsorted_table_key), (int(*)(const void *, const void *))comp);
                            print_by_key(table, table_copy, len);
                        }
                        else
                        {
                            copykey(unsorted_table_key, table_copy, len);
                            qsort_key(table_copy, 0, len - 1);
                            print_by_key(table, table_copy, len);
                        }
                    }
                    else
                        printf("Incorrect input!\n");
                    break;
                case 4:
                    printf("Which sort to use(0 - fast, 1 - simple): ");
                    type = 0;
                    rc = scanf("%d", &type);
                    printf("\n");
                    if (rc && (type == 1 || type == 0))
                    {
                        if (type == 1)
                        {
                            sort_table(table, (size_t)len, sizeof(table_key), (int(*)(const void *, const void *))comp);
                            print_table(table, len);
                            update_keys(table_key, len);
                            update_uns_keys(table, unsorted_table_key, len);
                        }
                        else
                        {
                            qsort_table(table, 0, len - 1);
                            print_table(table, len);
                            update_keys(table_key, len);
                            update_uns_keys(table, unsorted_table_key, len);
                        }
                    }

                    break;
                case 5:
                    printf("Which table to show(0 - raw, 1 - sorted): ");
                    type = 0;
                    rc = scanf("%d", &type);
                    printf("\n");
                    if (rc && (type == 1 || type == 0))
                    {
                        if (type == 1)
                        {
                            printf("| N  | index_orig | square_price |\n");
                            printf("--------------------------------------\n");
                            for (int i = 0; i < len; i++)
                                printf("| %-3d| %-11d| %-13d|\n", i + 1, table_key[i].index_orig, table_key[i].square_price);
                        }
                        else
                        {
                            printf("| N  | index_orig | square_price |\n");
                            printf("--------------------------------------\n");
                            for (int i = 0; i < len; i++)
                                printf("| %-3d| %-11d| %-13d|\n", i + 1, unsorted_table_key[i].index_orig, unsorted_table_key[i].square_price);
                        }
                    }
                    else
                        printf("Invalid type\n");
                    break;
                case 6:
                    printf("Which table to show(0 - raw, 1 - sorted by key): ");
                    type = 0;
                    rc = scanf("%d", &type);
                    printf("\n");
                    if (rc && (type == 1 || type == 0))
                    {
                        if (type == 0)
                            print_table(table, len);
                        else if (flag_key)
                            print_by_key(table, table_copy, len);
                        else
                            printf("Keys were not sorted\n");
                    }
                    else
                        printf("Invalid type\n");
                    break;
                case 7:
                    mem1 = sizeof(apartment) * len + sizeof(apartment_key) * len + sizeof(len) + 4 * sizeof(size_t) + sizeof(int) + sizeof(apartment_key);
                    mem2 = sizeof(apartment) * len + sizeof(apartment_key) * len + sizeof(len) + 4 * sizeof(size_t) + sizeof(int) + sizeof(apartment_key);
                    mem_table = sizeof(apartment) * len + sizeof(len)  + 4 * sizeof(size_t) + sizeof(int) + sizeof(apartment);
                    printf("Which sort to compare(0 - Fast, 1 - Simple): ");
                    short type_key = 0;
                    rc = scanf("%hd", &type_key);
                    printf("\n");
                    printf("Which table to compare(0 - Fast, 1 - Simple): ");
                    short type_table = 0;
                    rc = scanf("%hd", &type_table);
                    printf("\n");
                    if (rc && (type_key == 1 || type_key == 0) && (type_table == 1 || type_table == 0))
                    {  
                        if (type_key == 1 && type_table == 1)
                        {
                            time1_sort = gettime_simple(unsorted_table_key, len);
                            time2_sort = gettime_table(table, len);
                            compare_simple_table(time1_sort, time2_sort, mem1, mem_table);
                        }
                        else if (type_key == 0 && type_table == 1)
                        {
                            time1_sort = gettime_qsort(unsorted_table_key, len);
                            time2_sort = gettime_table(table, len);
                            compare_qsort_table(time1_sort, time2_sort, mem1, mem_table);
                        }
                        else if (type_key == 1 && type_table == 0)
                        {
                            time1_sort = gettime_simple(unsorted_table_key, len);
                            time2_sort = gettime_qtable(table, len);
                            compare_simple_qtable(time1_sort, time2_sort, mem1, mem_table);
                        }
                        else if (type_key == 0 && type_table == 0)
                        {
                            time1_sort = gettime_qsort(unsorted_table_key, len);
                            time2_sort = gettime_qtable(table, len);
                            compare_qsort_qtable(time1_sort, time2_sort, mem1, mem_table);
                        }
                    }
                    else
                        printf("Incorrect type\n");
                    break;
                case 8:
                    mem1 = sizeof(apartment) * len + sizeof(apartment_key) * len + sizeof(len) + 4 * sizeof(size_t) + sizeof(int) + sizeof(apartment_key);
                    mem2 = sizeof(apartment) * len + sizeof(apartment_key) * len + sizeof(len) + 4 * sizeof(size_t) + sizeof(int) + sizeof(apartment_key);
                    time1_sort = gettime_qsort(unsorted_table_key, len);
                    time2_sort = gettime_simple(unsorted_table_key, len);
                    compare_two_sort(time1_sort, time2_sort, mem1, mem2);
                    break;
                case 9:
                    find_by_req(table, len);
                    break;
                case 0:
                    break;
                default:
                    printf("Incorrect Command\n");
                    break;
            }
        while(getchar() != '\n') // Input clear
        {}
    } while (command);
    return 0; 
}

void print_menu()
{
    printf("--------------------------------------\n");
    printf("| List of Commands  \n");
    printf("| 1: Add a Field  \n");
    printf("| 2: Delete a Field  \n");
    printf("| 3: Sort Table by Table of Keys and show it  \n");
    printf("| 4: Sort original Table and show it  \n");
    printf("| 5: Show a Table of Keys \n");
    printf("| 6: Show a Table  \n");
    printf("| 7: Compare 3 and 4 command  \n");
    printf("| 8: Compare different sorts  \n");
    printf("| 9: Find secondary apartm. with 2 rooms without animals and within certain price range  \n");
    printf("| 0: Exit  \n");
    printf("--------------------------------------\n");
    printf("| Input command: ");
}
