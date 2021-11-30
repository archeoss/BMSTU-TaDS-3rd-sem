#include "../inc/operations.h"
#define B_BIGGER 10
#define A_BIGGER 20
#define EQUAL 30
#define UNDEF 40
int parse_matr(matrix *matr, parse *pars)
{
    if ((pars->elements) || (pars->cols_en) || (pars->index_row))
    {
        if (pars->elements)
            free(pars->elements);
        if (pars->cols_en)
            free(pars->cols_en);
        if (pars->index_row)
            free(pars->index_row);
    }
    pars->elements = NULL;
    pars->cols_en = NULL;
    pars->index_row = NULL;
    int error_code  = NO_ERROR;
    pars->e_amount = 0;
    int total_len = matr->columns * matr->rows;
    for (int i = 0; i < total_len; i++)
        if (*(matr->matrix[0] + i) != 0)
            pars->e_amount++;
    pars->elements = malloc(pars->e_amount * sizeof(int));
    pars->index_row = malloc(pars->e_amount * sizeof(int));
    pars->cols_en = malloc(matr->columns * sizeof(int));

    if (!(pars->elements) || !(pars->cols_en) || !(pars->index_row))
    {
        error_code = ALLOC_ERROR;
        if (pars->elements)
            free(pars->elements);
        if (pars->cols_en)
            free(pars->cols_en);
        if (pars->index_row)
            free(pars->index_row);
            
        pars->elements = NULL;
        pars->cols_en = NULL;
        pars->index_row = NULL;
    }

    if (!error_code)
    {
        int ind = 0;
        pars->allocated = 1;
        int n = matr->columns;
        int m = matr->rows;
        pars->columns = matr->columns;
        fill_en(pars);
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if ((matr->matrix[j][i]) != 0)
                {
                    if (pars->cols_en[i % matr->columns] == -1)
                        pars->cols_en[i % matr->columns] = ind;
                    pars->index_row[ind] = j;
                    pars->elements[ind++] = matr->matrix[j][i];
                }
            }
            if (pars->cols_en[i % matr->columns] == -1)
                pars->cols_en[i % matr->columns] = ind;
        }
        
    }

    return error_code;
}

int std_sum(matrix *matr, matrix *res, clock_t *clocks)
{
    int error_code = NO_ERROR;
    if (matr[0].rows != matr[1].rows || matr[0].columns != matr[1].columns)
        error_code = INCORRECT_MATR_SIZE;

    if (!error_code)
    {
        delete_matr(res);
        res->matrix = alloc_matrix(matr[0].rows, matr[0].columns);
        if (res->matrix)
        {
            res->allocated = 1;
            res->rows = matr[0].rows;
            res->columns = matr[0].columns;
            clock_t start = clock();
            for (int i = 0; i < matr[0].rows; i++)
                for (int j = 0; j < matr[0].columns; j++)
                    res->matrix[i][j] = matr[0].matrix[i][j] + matr[1].matrix[i][j];
                
            clock_t end = clock();
            *clocks = end - start;
        }
        else
            error_code = ALLOC_ERROR;
    }

    return error_code;
}

void fill_en(parse *pars)
{
    for (int i = 0; i < pars->columns; i++)
        pars->cols_en[i] = -1;
}

int arrays_min(int *a_arr, const int a_len, int *b_arr, const int b_len)
{
    
    if (a_len == 0 && b_len != 0)
        return A_BIGGER;

    if (b_len == 0 && a_len != 0)
        return B_BIGGER;

    int a_min = *a_arr, b_min = *b_arr;
    int a_pos = 0, b_pos = 0;
    for (int a = 0; a < a_len; ++a)
        if (*(a_arr + a) < a_min)
        {
            a_min = *(a_arr + a);
            a_pos = a;
        }
    for (int b = 0; b < b_len; ++b)
        if (*(b_arr + b) < b_min)
        {
            b_min = *(b_arr + b);
            b_pos = b;
        }
    if (a_min < b_min)
    {
        *(a_arr + a_pos) = 99999;
        return B_BIGGER;
    }
    if (b_min < a_min)
    {
        *(b_arr + b_pos) = 99999;
        return A_BIGGER;
    }

    if (a_min == b_min && a_min == 99999 && b_min == 99999)
        return UNDEF;
    *(a_arr + a_pos) = 99999;
    *(b_arr + b_pos) = 99999;
    return EQUAL;
}

void parse_sum(parse *pars, parse *parse_res, clock_t *clocks)
{
    parse_res->allocated = 1;
    int cur_el = 0;
    int a_glob = 0;
    int b_glob = 0;
    for (int j = 0; j < pars[0].columns; ++j)
    {
        int *a_arr;
        int *b_arr;
        int aind = 0, bind = 0;
        int cur_a, cur_b;
        if (j + 1 != pars[0].columns)
        {
            cur_a = *(pars[0].cols_en + j + 1);
            cur_b = *(pars[1].cols_en + j + 1);
        }
        else
        {
            cur_a = pars[0].e_amount;
            cur_b = pars[1].e_amount;
        }
        int a_column = cur_a - *(pars[0].cols_en + j);
        int b_column = cur_b - *(pars[1].cols_en + j);
        a_arr = calloc(a_column, sizeof(int));
        b_arr = calloc(b_column, sizeof(int));
        for (int a_col = *(pars[0].cols_en + j); a_col < cur_a; a_col++)
        {
            if (a_arr)
                *(a_arr + aind) = *(pars[0].index_row + a_col);
            aind++;
        }

        for (int b_col = *(pars[1].cols_en + j); b_col < cur_b; b_col++)
        {
            if (b_arr)
                *(b_arr + bind) = *(pars[1].index_row + b_col);
            bind++;
        }

        int matches = 0;

        for (int i = 0; i < a_column; i++)
            for (int k = i; k < b_column; k++)
                if (*(a_arr + i) == *(b_arr + k))
                    matches++;

        int range = a_column + b_column - matches;
        clock_t start = clock();
        for (int i = 0; i < range; i++)
        {
            int result = arrays_min(a_arr, a_column, b_arr, b_column);

            if (result == B_BIGGER)
            {
                *(parse_res->elements + cur_el) = *(pars[0].elements + a_glob);
                *(parse_res->index_row + cur_el) = *(pars[0].index_row + a_glob);
                cur_el++;
                a_glob++;
            }

            if (result == A_BIGGER)
            {
                *(parse_res->elements + cur_el) = *(pars[1].elements + b_glob);
                *(parse_res->index_row + cur_el) = *(pars[1].index_row + b_glob);
                cur_el++;
                b_glob++;
            }

            if (result == EQUAL)
            {
                *(parse_res->elements + cur_el) = *(pars[0].elements + a_glob) + *(pars[1].elements + b_glob);
                *(parse_res->index_row + cur_el) = *(pars[0].index_row + a_glob);
                cur_el++;
                a_glob++;
                b_glob++;
            }
        }

        clock_t end = clock();
        *clocks += end - start;

        free(a_arr);
        free(b_arr);
    }
}

int found_total_len(parse *pars, int *total_len)
{
    for (int j = 0; j < pars[0].columns; ++j)
    {
        int *a_arr;
        int *b_arr;
        int aind = 0, bind = 0;
        int cur_a, cur_b;

        if (j + 1 != pars[0].columns)
        {
            cur_a = *(pars[0].cols_en + j + 1);
            cur_b = *(pars[1].cols_en + j + 1);
        }
        else
        {
            cur_a = pars[0].e_amount;
            cur_b = pars[1].e_amount;
        }

        int a_column = cur_a - *(pars[0].cols_en + j);
        int b_column = cur_b - *(pars[1].cols_en + j);
        a_arr = calloc(a_column, sizeof(int));
        b_arr = calloc(b_column, sizeof(int));

        for (int a_col = *(pars[0].cols_en + j); a_col < cur_a; ++a_col)
        {
            if (a_arr)
                *(a_arr + aind) = *(pars[0].index_row + a_col);
            aind++;
        }

        for (int b_col = *(pars[1].cols_en + j); b_col < cur_b; ++b_col)
        {
            if (b_arr)
                *(b_arr + bind) = *(pars[1].index_row + b_col);
            bind++;
        }

        int matches = 0;

        for (int i = 0; i < a_column; i++)
            for (int k = i; k < b_column; k++)
                if (*(a_arr + i) == *(b_arr + k))
                    matches++;

        *total_len += a_column + b_column - matches;

        free(a_arr);
        free(b_arr);
    }

    return 0;
}

void fill_cols_en(parse *parse_res, matrix *matrix_res)
{
    fill_en(parse_res);
    int ind = 0;
    int n = matrix_res->columns;
    int m = matrix_res->rows;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if ((matrix_res->matrix[j][i]) != 0)
            {
                if (parse_res->cols_en[i % matrix_res->columns] == -1)
                    parse_res->cols_en[i % matrix_res->columns] = ind;
                ind++;
            }
        }
        if (parse_res->cols_en[i % matrix_res->columns] == -1)
            parse_res->cols_en[i % matrix_res->columns] = ind;   
    }
}