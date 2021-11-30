#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "readme.h"

int read_int(number *number_int, char *number)
{
    int error_code = NO_ERROR;
    int skip = 0;
    number_int->len = 0;
    number_int->after_dot_len = 0;
    number_int->order = 0;
    if ((number[0] == '+' || number[0] == '-') && isdigit(number[1]))
    {
        number_int->sign = number[0];
        if (number[1] == '0' && number[2] == '\n')
        {
            skip = 1;
            number_int->number[0] = '0';
        }
    }
    else if (number[0] >= '1' && number[0] <= '9')
    {
        number_int->sign = '+';
        number_int->len++;
        number_int->number[0] = number[0];
    }
    else if (number[0] == '0' && number[1] == '\n')
    {
        skip = 1;
        number_int->number[0] = '0';
        number_int->sign = '+';
        number_int->len++;
    }
    else
        error_code = INPUT_ERROR;
    int i = 1;
    char c = number[i];
    if (!skip)
        while (c != '\0' && c != '\n' && error_code == NO_ERROR && number_int->len < LEN)
        {
            if ((isdigit(c) && number_int->len > 0) || (c >= '1' && c <= '9'))
            {
                number_int->number[number_int->len++] = c;
                c = number[++i];
            }
            else
                error_code = INPUT_ERROR;
        }
    if (c != '\0' && c != '\n')
        error_code = INPUT_ERROR;
    number_int->order = number_int->len;
    return error_code;
}

int read_flt(number *number_flt, char *number)
{
    char *order;
    int error_code = NO_ERROR;
    order = strtok(number, "E");
    order = strtok(NULL, "E");
    if (order != NULL)
    {
        int n = 0;
        number_flt->order = 0;
        if (*order == ' ')
            order++;
        if (*order == '-')
        {
            order++;
            while (n++ < 5 && error_code == NO_ERROR && *order != '\n')
            {
                if (isdigit(*order))
                    number_flt->order = number_flt->order * 10 - *order + '0';
                else
                    error_code = INPUT_ERROR;
                order++;
            }
        }
        else if (*order == '+' || isdigit(*order))
        {
            if (*order == '+')
                order++;
            while (n++ < 5 && error_code == NO_ERROR && *order != '\n')
            {
                if (isdigit(*order))
                    number_flt->order = number_flt->order * 10 + *order - '0';
                else
                    error_code = INPUT_ERROR;
                order++;
            }
        }
        if (*order != ' ' && *order != '\n')
            error_code = INPUT_ERROR;
    }
    else
        number_flt->order = 0;
    int dot_flag = 0;
    number_flt->len = 0;
    number_flt->after_dot_len = 0;
    int i = 0;
    int skip = 0;
    if ((number[0] == '+' || number[0] == '-'))
    {
        i++;
        number_flt->sign = number[0];
        if ((number[1] == '0' && number[2] == '.') || number[1] == '.')
        {
            i += 2;
            number_flt->number[1] = number[1];
            number_flt->len++;
            dot_flag = 1;
        }
        if (number[1] == '0' && number[1] == '\n')
        {
            skip = 1;
            number_flt->number[0] = '0';
        }
    } 
    else if (number[0] >= '1' && number[0] <= '9')
    {
        i++;
        number_flt->sign = '+';
        number_flt->len++;
        number_flt->number[0] = number[0];
    }
    else if((number[0] == '0' && number[1] == '.') || number[0] == '.')
    {
        number_flt->sign = '+';
        i += 2;
        number_flt->number[0] = number[0];
        number_flt->len++;
        dot_flag = 1;
    }
    else if (number[0] == '0' && number[1] == '\n')
    {
        skip = 1;
        number_flt->number[0] = '0';
        number_flt->sign = '+';
        number_flt->len++;
    }
    else
        error_code = INPUT_ERROR;
    char c = number[i];
    if (c == ' ')
    {
        i++;
        c = number[i];
    }
    if (!skip)
    {
        while (c != '\0' && c != '\n' && c != ' ' && c != 'E' && error_code == NO_ERROR && number_flt->len < LEN)
        {
            if ((isdigit(c) && number_flt->len > 0) || (c >= '0' && c <= '9'))
            {
                if (dot_flag)
                    number_flt->after_dot_len++;
                number_flt->number[number_flt->len++] = c;
                c = number[++i];
            }
            else if (c == '.' && !dot_flag)
            {
                dot_flag = 1;
                c = number[++i];
            }
            else
                error_code = INPUT_ERROR;
        }
        if (c != '\0' && c != 'E' && c != '\n' && c != ' ' && number[i+1] != 'E')
            error_code = INPUT_ERROR;
        else
        {
            while (number_flt->number[0] == '0')
            {
                for (int j = 0; j < number_flt->len; j++)
                    number_flt->number[j] = number_flt->number[j + 1];
                number_flt->len--;
            }
            number_flt->order += (number_flt->len - number_flt->after_dot_len);
        }
    }
    return error_code;
}