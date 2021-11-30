#include "../inc/io.h"

int load_matrix(int *matrix, char *filename, int n, int m)
{
    int error_code = NO_ERROR;
    FILE *f = fopen(filename, "r");
    int total_len = n * m;
    if (f)
    {
        int i = 0;
        int rc;
        while (i++ < total_len && (rc = fscanf(f, "%d", matrix++)) == 1)
        {
        }
        matrix -= i;
        i--;
        int tmp;
        if (i != total_len && (rc = fscanf(f, "%d", &tmp)) == 1)
            error_code = INCORRECT_DATAFILE;
    }
    else
        error_code = INVALID_INPUT;
    
    return error_code;
}

void generate_matrix(int *matrix, int n, int m, int perc)
{
    srand(time(NULL));
    int total_len = n * m;
    int total_el = total_len * perc / 100;
    for (int i = 0; i < total_len; i++)
        *(matrix++) = 0;
    matrix -= total_len;
    if (total_el == 0)
        total_el++;
    int i = 0;
    while (total_el)
    {
        if (!(*(matrix)))
        {
            int chance = rand() % 100;
            if (chance < perc)
            {
                *(matrix) = (rand() % 100) + 1;
                total_el--;
            }
        }
        matrix++;
        i++;
        if (i == total_len)
        {
            i = 0;
            matrix -= total_len;
        }
    }
}

int input_matrix(int *matrix, int n, int m)
{
    int total_len = n * m;
    int i = 0;
    short rc;
    int error_code = NO_ERROR;
    while (i++ < total_len && (rc = scanf("%d", matrix++)) == 1)
    {
    }
    matrix -= i;
    i--;
    if (i != total_len)
        error_code = INVALID_INPUT;

    return error_code;    
}

void print_matrix(int **matrix, int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            printf("%5d ", matrix[i][j]);
        printf("\n");
    }
}

void print_parsed(parse *pars)
{
    printf("non_zero els: %d\n", pars->e_amount);
    printf("non-zero: ");
    for (int i = 0; i < pars->e_amount; i++)
        printf("%d ", pars->elements[i]);
    printf("\nindex-row: ");
    for (int i = 0; i < pars->e_amount; i++)
        printf("%d ", pars->index_row[i]);

    printf("\ncol_en: ");
    for (int i = 0; i < pars->columns; i++)
        printf("%d ", pars->cols_en[i]);
    printf("\n");
}

int get_size(int *n, int *m)
{
    printf("Input rows count of matrix(min value = 2, max value = %d): ", SHORT_VALUE);
    short rc_n = scanf("%d", n);
    printf("\n");
    printf("Input column count of matrix(min value = 2, max value = %d): ", SHORT_VALUE);
    short rc_m = scanf("%d", m);
    printf("\n");
    if (rc_m && rc_n)
        return 1;
    else 
        return 0;
}


int sparse_input(int **matrix, int n, int m, int un_zero)
{
    int total_len = n * m;
    int i = 0;
    int row, col;
    short rc = 3;
    for (int k = 0; k < total_len; k++)
        *(matrix[0] + k) = 0;
    int error_code = NO_ERROR;
    printf("Print <row position | col position | number>\n");
    while (i++ < un_zero && rc == 3)
    {
        rc = scanf("%d %d", &row, &col);
        if (row < n && col < m)
            rc += scanf("%d", (matrix[row] + col));
        else
        {
            rc = 0;
            error_code = INVALID_INPUT;
        }
    }
    matrix -= i;
    i--;
    if (i != un_zero)
        error_code = INVALID_INPUT;

    return error_code;

}