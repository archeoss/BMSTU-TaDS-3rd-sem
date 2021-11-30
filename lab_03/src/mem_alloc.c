#include "../inc/mem_alloc.h"

int** alloc_matrix(int n, int m)
{
    int **ptrs, *matrix;
    ptrs = malloc(n * sizeof(double*));
    if (!ptrs)
        return NULL;
    matrix = malloc(n * m * sizeof(double));
    if (!matrix)
    {
        free(ptrs);
        return NULL;
    }
    for (int i = 0; i < n; i++)
        ptrs[i] = matrix + i * m;
    
    return ptrs;
}

void delete_matr(matrix *matr)
{
    if (matr->matrix)
    {
        free(matr->matrix[0]);
        free(matr->matrix);
    }
}

void delete_parse(parse *pars)
{
    if (pars->elements)
    {
        free(pars->elements);
        free(pars->index_row);
        free(pars->cols_en);
    }
}