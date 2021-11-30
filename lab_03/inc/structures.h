#ifndef _STRUCTURES_H_

#define _STRUCTURES_H_

typedef struct
{
    int **matrix;
    int rows;
    int columns;
    short allocated;
} matrix;


typedef struct
{
    int *elements;
    int *index_row;
    int *cols_en;
    int e_amount;
    int columns;
    short allocated;
} parse;

#endif