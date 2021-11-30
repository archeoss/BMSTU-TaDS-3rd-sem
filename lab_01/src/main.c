#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "readme.h"
#include "operations.h"

#define NO_ERROR 0
#define INPUT_ERROR 1
#define DATA_ERROR 2
#define ORDER_OVERFLOW 3

#define LEN 30
#define P 5

int main()
{
    char int_number[LEN + 10];
    char flt_number[LEN + 10];
    int rc = 0;
    int error_code;
    number number_int;
    number number_flt;
    number result;
    printf("Input integer: ");
    rc += fgets(int_number, LEN+10, stdin) != NULL;
    printf("Input float: ");
    rc += fgets(flt_number, LEN+10, stdin) != NULL;
    if (rc == 2)
    {
        error_code = read_int(&number_int, int_number);
        if (error_code == NO_ERROR)
            error_code = read_flt(&number_flt, flt_number);
        if (error_code == NO_ERROR)
            error_code = multiplication(&number_int, &number_flt, &result);
    }
    else
        error_code = INPUT_ERROR;
    if (error_code == NO_ERROR)    
        printf("%c0.%s E %d\n", result.sign, result.number, result.order);
    else if (error_code == INPUT_ERROR)
        printf("Invalid Input\n");
    else if (error_code == DATA_ERROR)
        printf("Data Error\n");
    else if (error_code == ORDER_OVERFLOW)
        printf("Order Overflow\n");
    return error_code;   
}