#include "hash.h"

static void hash_it(FILE *f, hash_t *hash_table, int *cur_max_comparison, int (*hash_func)(hash_t *hash_table, int a))
{
    int cur_n;
    while (fscanf(f, "%d", &cur_n) != EOF)
    {
        int key = hash_func(hash_table, cur_n);
        int cur_comparison = 1;
        while (hash_table->is_occupied[key] == 1)
        {
            key--;
            if (key < 0)
                key = hash_table->size - 1;
            cur_comparison++;
        }
        *cur_max_comparison = cur_comparison > *cur_max_comparison ? cur_comparison : *cur_max_comparison;
        hash_table->is_occupied[key] = 1;
        hash_table->hash_table[key] = cur_n;
    }
}

int hash_func_a(hash_t *hash_table, int a)
{
    long key = (a * a) % hash_table->hash_num;

    return key;
}

int hash_func_b(hash_t *hash_table, int a)
{
    int key = abs((a << 1)) % hash_table->hash_num;

    return key;
}

int gen_hashtable(char *filename, hash_t *hash_table, int mode)
{
    FILE *f = fopen(filename, "r");
    hash_table->hash_table = malloc(sizeof(int) * hash_table->size);
    hash_table->is_occupied = calloc(sizeof(int), hash_table->size);
    int cur_max_comparison = 0;
    if (mode == A)
        hash_it(f, hash_table, &cur_max_comparison, hash_func_a);
    else
        hash_it(f, hash_table, &cur_max_comparison, hash_func_b);
    fclose(f);
    
    return cur_max_comparison;
}

int pop_from_hash(hash_t *hash_table, int num_to_del, int mode)
{
    int comparsions = 0;
    int key;
    if (mode == A)
        key = hash_find(hash_table, num_to_del, &comparsions, hash_func_a);
    else
        key = hash_find(hash_table, num_to_del, &comparsions, hash_func_b);
    if (key != -1)
        hash_table->is_occupied[key] = 0;

    return comparsions;
}

int hash_find(hash_t *hash_table, int num_to_find, int *comprasions, int (*hash_func)(hash_t *, int))
{
    int key = hash_func(hash_table, num_to_find);
    int key_copy = key - 1;
    *comprasions = 1;
    
    if (!hash_table->is_occupied[key] || hash_table->hash_table[key] != num_to_find)
    {
        while ((hash_table->is_occupied[key_copy] == 0 || hash_table->hash_table[key_copy] != num_to_find) && key_copy != key)
        {
            (*comprasions)++;
            if (--key_copy < 0)
                key_copy = hash_table->size - 1;
        }
        if (key == key_copy)
            key_copy = -1;
    }
    else
        key_copy = key;

    return key_copy;
}