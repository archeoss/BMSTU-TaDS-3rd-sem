#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "readme.h"
#include "sort.h"
#define LEN_TABLE 350
#define N_SORT 10

void table_init(apartment *table, apartment_key *table_key, apartment_key *unsorted_table_key, int len)
{
    char files[][40] = {"./DB/rand_adr", "./DB/rand_squares", "./DB/rand_room_cnt", "./DB/rand_price", "./DB/rand_type", 
                                "./DB/rand_trim", "./DB/rand_date", "./DB/rand_owner", "./DB/rand_last_owner", "./DB/rand_animal"};
    FILE *f = fopen(files[0], "r");
    for (int i = 0; i < len; i++)
        fgets(table[i].address, ADDRESS_LEN, f);
    fclose(f);
    f = fopen(files[1], "r");
    for (int i = 0; i < len; i++)
        fscanf(f, "%hd", &table[i].square);
    fclose(f);
    f = fopen(files[2], "r");
    for (int i = 0; i < len; i++)
        fscanf(f, "%hd", &table[i].room_count);
    fclose(f);
    f = fopen(files[3], "r");
    for (int i = 0; i < len; i++)
    {
        int tmp;
        fscanf(f, "%d", &tmp);
        table[i].square_price = tmp;
        unsorted_table_key[i].square_price = tmp;
        unsorted_table_key[i].index_orig = i;
        key_add_square(table_key, tmp, i);
    }
    fclose(f);
    f = fopen(files[4], "r");
    for (int i = 0; i < len; i++)
        fscanf(f, "%hd", &table[i].t);
    fclose(f);
    FILE* f_prim1 = fopen(files[5], "r");
    FILE* f_sec1 = fopen(files[6], "r");
    FILE* f_sec2 = fopen(files[7], "r");
    FILE* f_sec3 = fopen(files[8], "r");
    FILE* f_sec4 = fopen(files[9], "r");
    for (int i = 0; i < len; i++)
    {
        if (table[i].t == 1)
        {
            fscanf(f_sec1, "%hd", &table[i].tp.sec.build_date);
            fscanf(f_sec2, "%hd", &table[i].tp.sec.owner_count);
            fscanf(f_sec3, "%hd", &table[i].tp.sec.last_owner_count);
            fscanf(f_sec4, "%hd", &table[i].tp.sec.was_animal);
        }
        else
            fscanf(f_prim1, "%hd", &table[i].tp.prim.trim);
    }
    fclose(f_prim1);
    fclose(f_sec1);
    fclose(f_sec2);
    fclose(f_sec3);
    fclose(f_sec4);   
}

int add_field(apartment *table, apartment_key *table_key, apartment_key *unsorted_table_key, int len)
{
    int error_code = NO_ERROR;

    printf("Input Address(LESS THAN %d SYMBOLS): \n", ADDRESS_LEN);
    char tmp[ADDRESS_LEN + 2];
    char junk;
    scanf("%c", &junk);
    fgets(tmp, ADDRESS_LEN + 2, stdin);
    if (tmp[strlen(tmp) - 1] != '\n')
    {
        error_code = INPUT_ERROR;
        while(getchar()!='\n')
        {}
    }
    else
        strcpy(table[len].address, tmp);
    
    short sh_tmp = 0;
    int n_tmp = 0;
    int rc;
    if (error_code == NO_ERROR)
    {
        printf("Input squares(Max Value = %d): ", SHORT_VALUE);
        rc = scanf("%hd", &sh_tmp);
        if (rc && sh_tmp > 16)
            table[len].square = sh_tmp;
        else
            error_code = INPUT_ERROR;
    }

    if (error_code == NO_ERROR)
    {
        printf("Input room count(Max Value = %d): ", SHORT_VALUE);
        rc = scanf("%hd", &sh_tmp);
        if (rc && sh_tmp > 0)
            table[len].room_count = sh_tmp;
        else
            error_code = INPUT_ERROR;
    }

    if (error_code == NO_ERROR)
    {
        printf("Input square price(Max Value = %d): ", INT_VALUE);
        rc = scanf("%d", &n_tmp);
        if (n_tmp > 0 && rc)
        {
            unsorted_table_key[len].square_price = n_tmp;
            unsorted_table_key[len].index_orig = len;
            table[len].square_price = n_tmp;
            key_add_square(table_key, n_tmp, len);
        }
        else
            error_code = INPUT_ERROR;
    }
    
    if (error_code == NO_ERROR)
    {
        printf("Input type(Primary = 0, Secondary = 1): ");
        rc = scanf("%hd", &sh_tmp);
        if (rc && (sh_tmp == 0 || sh_tmp == 1))
            table[len].t = sh_tmp;
        else
            error_code = INPUT_ERROR;
    }
    if (error_code == NO_ERROR)
    {
        if (table[len].t == 0)
        {
            printf("Input trim existance(No = 0, Yes = 1): ");
            rc = scanf("%hd", &sh_tmp);
            if (error_code == NO_ERROR && rc && (sh_tmp == 0 || sh_tmp == 1))
                table[len].tp.prim.trim = sh_tmp;
            else
                error_code = INPUT_ERROR;
        }
        else
        {
            printf("Input date of build(Min Value = 1801, Max Value = %d): ", SHORT_VALUE);
            rc = scanf("%hd", &sh_tmp);
            if (rc && sh_tmp > 1800)
                table[len].tp.sec.build_date = sh_tmp;
            else
                error_code = INPUT_ERROR;
            if (error_code == NO_ERROR)
            {
                printf("Input owners count(Max Value = %d): ", SHORT_VALUE);
                rc = scanf("%hd", &sh_tmp);
                if (sh_tmp > 0 && rc)
                    table[len].tp.sec.owner_count = sh_tmp;
                else
                    error_code = INPUT_ERROR;
            }
            if (error_code == NO_ERROR)
            {            
                printf("Input last owners count(Max Value = %d): ", SHORT_VALUE);
                rc = scanf("%hd", &sh_tmp);
                if (sh_tmp > 0 && rc)
                    table[len].tp.sec.last_owner_count = sh_tmp;
                else
                    error_code = INPUT_ERROR;
            }
            if (error_code == NO_ERROR)
            {    
                printf("Input was there an animal(No = 0, Yes = 1): ");
                rc = scanf("%hd", &sh_tmp);
                if (rc && (sh_tmp == 0 || sh_tmp == 1))
                    table[len].tp.sec.was_animal = sh_tmp;
                else
                    error_code = INPUT_ERROR;
            }
        }
    }
    
    return error_code;
}

int delete_field(apartment *table, apartment_key *table_key, apartment_key *unsorted_table_key, int len, int n)
{
    int error_code = NO_ERROR;
    n--;
    int pos = n;
    int pos_s;
    if (pos < len && pos > -1)
    {
        for (int i = 0; i < len; i++)
            if (table_key[i].index_orig == pos)
                pos_s = i;
        for (; pos < len - 1; pos++)
        {
            table[pos] = table[pos + 1];
            unsorted_table_key[pos] = unsorted_table_key[pos + 1];
        }
        for (; pos_s < len; pos_s++)
        {
            table_key[pos_s] = table_key[pos_s + 1];
            if (table_key[pos_s].index_orig > n)
                table_key[pos_s].index_orig--;
        }
    }
    else
        error_code = DATA_ERROR;
    
    return error_code;
}

void key_add_square(apartment_key *table_key, int squre_price, int len)
{
    int flag = 1;
    int n = 0;
    int index = len;
    while (flag && n < len)
    {
        if (table_key[n].square_price > squre_price)
        {
            flag = 0;
            short tmp = table_key[n].square_price;
            short tmp_i = table_key[n].index_orig;
            table_key[n].square_price = squre_price;
            table_key[n].index_orig = index;
            squre_price = tmp;
            index = tmp_i;
        }
        n++;
    }
    for (; n < len + 1; n++)
    {
        short tmp = table_key[n].square_price;
        short tmp_i = table_key[n].index_orig;
        table_key[n].square_price = squre_price;
        table_key[n].index_orig = index;
        squre_price = tmp;
        index = tmp_i;
    }
}

void update_keys(apartment_key *table_key, int len)
{
    for (int i = 0; i < len; i++)
        table_key[i].index_orig = i;
}
void update_uns_keys(apartment *table, apartment_key *table_key, int len)
{
    for (int i = 0; i < len; i++)
    {
        table_key[i].index_orig = i;
        table_key[i].square_price = table[i].square_price;
    }
}

void copykey(apartment_key *k_orig, apartment_key *k_copy, int len)
{
    for (int i = 0; i < len; i++)
        k_copy[i] = k_orig[i];
}

void copytable(apartment *t_orig, apartment *t_copy, int len)
{
    for (int i = 0; i < len; i++)
        t_copy[i] = t_orig[i];
}

clock_t gettime_simple(apartment_key *table, int len)
{
    clock_t time[N_SORT] = {0};
    for (int i = 0; i < N_SORT; i++)
    {
        apartment_key table_copy[LEN_TABLE];
        copykey(table, table_copy, len);
        time[i] = -clock();
        sort_key(table_copy, (size_t)len, sizeof(table_copy), (int(*)(const void *, const void *))comp);
        time[i] += clock();
    }
    for (int k = 0; k < N_SORT; k++)
    {
        if (time[k] > time[0])
        {
            clock_t tmp = time[k];
            time[k] = time[0];
            time[0] = tmp;
        }
        if (time[k] < time[1])
        {
            clock_t tmp = time[k];
            time[k] = time[1];
            time[1] = tmp;
        }
    }
    clock_t result = 0;
    for (int k = 2; k < N_SORT; k++)
        result += time[k];
    return result / (N_SORT - 2);
}

clock_t gettime_qsort(apartment_key *table, int len)
{
    clock_t time[N_SORT] = {0};
    for (int i = 0; i < N_SORT; i++)
    {
        apartment_key table_copy[LEN_TABLE];
        copykey(table, table_copy, len);
        time[i] = -clock();
        qsort_key(table_copy, 0, len - 1);
        time[i] += clock();
    }
    for (int k = 0; k < N_SORT; k++)
    {
        if (time[k] > time[0])
        {
            clock_t tmp = time[k];
            time[k] = time[0];
            time[0] = tmp;
        }
        if (time[k] < time[1])
        {
            clock_t tmp = time[k];
            time[k] = time[1];
            time[1] = tmp;
        }
    }
    clock_t result = 0;
    for (int k = 2; k < N_SORT; k++)
        result += time[k];
    return result / (N_SORT - 2);
}

clock_t gettime_table(apartment *table, int len)
{
    clock_t time[N_SORT] = {0};
    for (int i = 0; i < N_SORT; i++)
    {
        apartment table_copy[LEN_TABLE];
        copytable(table, table_copy, len);
        clock_t begin = clock();
        sort_table(table_copy, (size_t)len, sizeof(table_copy), (int(*)(const void *, const void *))comp);
        clock_t end = clock();
        time[i] = (end - begin); 
    }
    for (int k = 0; k < N_SORT; k++)
    {
        if (time[k] > time[0])
        {
            clock_t tmp = time[k];
            time[k] = time[0];
            time[0] = tmp;
        }
        if (time[k] < time[1])
        {
            clock_t tmp = time[k];
            time[k] = time[1];
            time[1] = tmp;
        }
    }
    clock_t result = 0;
    for (int k = 2; k < N_SORT; k++)
        result += time[k];
    return result / (N_SORT - 2);
}


clock_t gettime_qtable(apartment *table, int len)
{
    clock_t time[N_SORT] = {0};
    for (int i = 0; i < N_SORT; i++)
    {
        apartment table_copy[LEN_TABLE];
        copytable(table, table_copy, len);
        clock_t begin = clock();
        qsort_table(table_copy, 0, len - 1);
        clock_t end = clock();
        time[i] = (end - begin); 
    }
    for (int k = 0; k < N_SORT; k++)
    {
        if (time[k] > time[0])
        {
            clock_t tmp = time[k];
            time[k] = time[0];
            time[0] = tmp;
        }
        if (time[k] < time[1])
        {
            clock_t tmp = time[k];
            time[k] = time[1];
            time[1] = tmp;
        }
    }
    clock_t result = 0;
    for (int k = 2; k < N_SORT; k++)
        result += time[k];
    return result / (N_SORT - 2);
}