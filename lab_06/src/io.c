#include "io.h"

int get_count(FILE *f)
{
    int n = 0;
    int tmp;
    while (fscanf(f, "%d", &tmp) != EOF)
        n++;
    rewind(f);

    return n;
}

int read_tree(FILE *f, tree_arr *tree)
{
    if (!f)
        return INVALID_INPUT;
    int n = get_count(f);
    
    if (n == 0)
        return INVALID_INPUT;

    tree->size = n;
    tree->arr = malloc(sizeof(node_t));
    int cur_n;
    fscanf(f, "%d", &cur_n);
    tree->arr->data = cur_n;
    tree->arr->left = NULL;
    tree->arr->right = NULL;
    if (!tree->arr)
        return ALLOC_ERROR;
    
    while (fscanf(f, "%d", &cur_n) != EOF)
        tree->arr = insert(tree->arr, cur_n);
    rewind(f);

    return 0;    
}

void print_tree(node_t *tree, int spaces)
{
    if (tree)
    {
        print_tree(tree->right, spaces + 5);
        for (int i = 0; i < spaces; i++)
            printf(" ");
        printf("%d\n", tree->data);
        print_tree(tree->left, spaces + 5);
    }
}

void print_hash(hash_t *hash_table)
{
    printf(CYAN"====================================\n"CLR);
    for (int i = 0; i < hash_table->size; i++)
    {
        if (hash_table->is_occupied[i])
        {
            printf(CYAN"     %d  |   %d"\
            "\n====================================\n"CLR, i, hash_table->hash_table[i]);
        }
    }
}