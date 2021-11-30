#ifndef _README_H_

#define _README_H_

#define NO_ERROR 0
#define INPUT_ERROR 1
#define DATA_ERROR 2

#define LEN 30
#define P 5

typedef struct
{
    char number[LEN];
    short int len;
    char sign;
    short int after_dot_len;
    int order;
} number;

int read_flt(number *number_flt, char *);
int read_int(number *, char *);

#endif