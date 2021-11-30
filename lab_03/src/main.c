#include "../inc/structures.h"
#include "../inc/io.h"
#include "../inc/operations.h"
#include "../inc/errors.h"
#include "../inc/constants.h"
#include "../inc/mem_alloc.h"
#include <string.h>
void print_menu();
void print_error(int);
int main(void)
{
    matrix matrixes[2] = {0};
    matrix matrix_res = {0};
    parse parses[2] = {0};
    parse parse_res = {0};
    int total_len = 0;
    clock_t clocks_parse;
    clock_t clocks_std;
    int n;
    int m;
    int matr_switch;
    short command = -1;
    int type, rc_s;
    char filename[FILE_LEN + 2];
    char filename2[FILE_LEN + 2];
    int error_code = NO_ERROR;
    do
    {
        print_menu();
        int rc_m, rc = scanf("%hd", &command);
        printf("\n");
        if (rc)
        {
            error_code = NO_ERROR;
            switch (command)
            {
            case 1:
                printf("Input File_name1(max length = %d): ", FILE_LEN);
                char junk;
                scanf("%c", &junk);
                fgets(filename, FILE_LEN + 2, stdin);
                printf("\n");
                printf("Input File_name2(max length = %d): ", FILE_LEN);
                scanf("%c", &junk);
                fgets(filename2, FILE_LEN + 2, stdin);
                printf("\n");
                rc = get_size(&n, &m);
                printf("%s", filename);
                if (rc && m > 1 && n > 1 && filename[strlen(filename) - 1] == '\n' && filename[strlen(filename2) - 1] == '\n')
                {
                    filename[strlen(filename) - 1] = '\0';
                    filename[strlen(filename2) - 1] = '\0';

                    matrixes[0].allocated = 0;
                    matrixes[1].allocated = 0;
                    matrix_res.allocated = 0;
                    parses[0].allocated = 0;
                    parses[1].allocated = 0;
                    parse_res.allocated = 0;
                    delete_matr(&matrixes[1]);
                    delete_matr(&matrixes[0]);
                    matrixes[0].matrix = alloc_matrix(n, m);
                    matrixes[1].matrix = alloc_matrix(n, m);
                    if (matrixes[matr_switch].matrix)
                    {
                        matrixes[0].rows = n;
                        matrixes[0].columns = m;
                        
                        matrixes[1].rows = n;
                        matrixes[1].columns = m;
                        
                        error_code = load_matrix(matrixes[0].matrix[0], filename, n, m);
                        if (!error_code)
                        {                   
                            error_code = load_matrix(matrixes[1].matrix[0], filename2, n, m);
                            if (!error_code)
                            {
                                matrixes[0].allocated = 1;
                                matrixes[1].allocated = 1;
                            }
                            else
                                error_code = ALLOC_ERROR;
                        }
                        else
                            error_code = ALLOC_ERROR;
                    }
                    else
                        error_code = ALLOC_ERROR;
                }
                else
                    error_code = INVALID_INPUT;
                break;
            case 2:
                rc = get_size(&n, &m);
                int perc_a, perc_b;
                printf("Input percentage of non_zero elements for A(1 - 100):\n");
                rc_m = scanf("%d", &perc_a);
                printf("\n");
                printf("Input percentage of non_zero elements for B(1 - 100):\n");
                rc_m += scanf("%d", &perc_b);
                printf("\n");
                if (rc && n > 1 && m > 1 && rc_m == 2 && perc_a > 0 && perc_a < 101 && perc_b > 0 && perc_b < 101)
                {
                    matrixes[0].allocated = 0;
                    matrixes[1].allocated = 0;
                    matrix_res.allocated = 0;
                    parses[0].allocated = 0;
                    parses[1].allocated = 0;
                    parse_res.allocated = 0;
                    delete_matr(&matrixes[0]);
                    delete_matr(&matrixes[1]);
                    matrixes[0].matrix = alloc_matrix(n, m);
                    matrixes[1].matrix = alloc_matrix(n, m);
                    if (matrixes[0].matrix && matrixes[1].matrix)
                    {
                        matrixes[0].rows = n;
                        matrixes[0].columns = m;
                        generate_matrix(matrixes[0].matrix[0], n, m, perc_a);
                        matrixes[0].allocated = 1;

                        matrixes[1].rows = n;
                        matrixes[1].columns = m;
                        generate_matrix(matrixes[1].matrix[0], n, m, perc_b);
                        matrixes[1].allocated = 1;
                    }
                    else
                        error_code = ALLOC_ERROR;
                }
                else
                    error_code = INVALID_INPUT;
                break;
            case 3:
                printf("Choose, how you want to fill matrix(Full table = 0, Sparse = 1)");
                rc_s = scanf("%d", &type);
                printf("\n");
                rc = get_size(&n, &m);
                if (rc_s && (type == 0 || type == 1) && rc && n > 1 && m > 1)
                {
                    matrixes[0].allocated = 0;
                    matrixes[1].allocated = 0;
                    matrix_res.allocated = 0;
                    parses[0].allocated = 0;
                    parses[1].allocated = 0;
                    parse_res.allocated = 0;
                    delete_matr(&matrixes[0]);
                    delete_matr(&matrixes[1]);
                    matrixes[0].matrix = alloc_matrix(n, m);
                    matrixes[1].matrix = alloc_matrix(n, m);
                    if (matrixes[matr_switch].matrix)
                    {
                        matrixes[0].rows = n;
                        matrixes[0].columns = m;

                        matrixes[1].rows = n;
                        matrixes[1].columns = m;
                        if (type == 0)
                        {
                            printf("Print Matrix A:\n");
                            error_code = input_matrix(matrixes[0].matrix[0], n, m);
                            if (!error_code)
                            {
                                printf("Print Matrix B:\n");
                                error_code = input_matrix(matrixes[1].matrix[0], n, m);
                            }
                        }
                        else
                        {
                            printf("Print count of non-zero elements for A: ");
                            int non_zero_a = 0;
                            rc_s = scanf("%d", &non_zero_a);
                            printf("\n");
                            printf("Print count of non-zero elements for B: ");
                            int non_zero_b = 0;
                            rc_s += scanf("%d", &non_zero_b);
                            printf("\n");
                            if (rc_s == 2 && non_zero_a <= n * m && non_zero_a > 0 && non_zero_b <= n * m && non_zero_b > 0)
                            {
                                printf("For matrix A\n");
                                error_code = sparse_input(matrixes[0].matrix, n, m, non_zero_a);
                                if (!error_code)
                                {
                                    printf("For matrix B\n");
                                    error_code = sparse_input(matrixes[1].matrix, n, m, non_zero_b);
                                }
                            }
                            else
                                error_code = INVALID_INPUT;
                        }
                        if (!error_code)
                        {
                            matrixes[0].allocated = 1;
                            matrixes[1].allocated = 1;
                        }
                    }
                    else
                        error_code = ALLOC_ERROR;
                }
                else
                    error_code = INVALID_INPUT;
                break;
            case 4:
                printf("Choose, which matrix do you want to show(A = 0, B = 1, Result = 2): ");
                rc_m = scanf("%d", &matr_switch);
                printf("\n");
                if (rc_m && matr_switch > -1 && matr_switch < 3)
                {
                    if (matr_switch == 2 && matrix_res.allocated)
                    {
                        if (matrix_res.allocated)
                            print_matrix(matrix_res.matrix, matrix_res.rows, matrix_res.columns);
                        else
                            error_code = NOT_ALLOCATED;
                    }
                    else if (matrixes[matr_switch].allocated)
                        print_matrix(matrixes[matr_switch].matrix, matrixes[matr_switch].rows, matrixes[matr_switch].columns);
                    else
                        error_code = NOT_ALLOCATED;
                }
                else
                    error_code = INVALID_INPUT;
                break;
            case 5:
                printf("Choose, which matrix do you want to parse(A = 0, B = 1, All = 2): ");
                rc_m = scanf("%d", &matr_switch);
                printf("\n");
                if (rc_m && matr_switch > -1 && matr_switch < 3)
                {
                    if (matr_switch == 2 && matrixes[0].allocated && matrixes[1].allocated)
                    {
                        parse_matr(matrixes, parses);
                        parse_matr(matrixes + 1, parses + 1);
                    }
                    else if (matrixes[matr_switch].allocated)
                    {
                        parse_matr(matrixes + matr_switch, parses + matr_switch);
                    }
                    else
                        error_code = NOT_ALLOCATED;
                }
                break;
            case 6:
                printf("Choose, which parsed matrix do you want to show(A = 0, B = 1, Result = 2): ");
                rc_m = scanf("%d", &matr_switch);
                printf("\n");
                if (rc_m &&  matr_switch > -1 && matr_switch < 3)
                {
                    if (matr_switch == 2)
                    {
                        if (parse_res.allocated)
                            print_parsed(&parse_res);
                        else
                            error_code = NOT_ALLOCATED;
                    }
                    else if (parses[matr_switch].allocated)
                        print_parsed(parses + matr_switch);
                    else
                        error_code = NOT_ALLOCATED;
                }
                break;
            case 7:
                if (matrixes[0].columns != matrixes[1].columns || matrixes[0].rows != matrixes[1].rows)
                    error_code = INCORRECT_MATR_SIZE;
                clocks_std = 0;
                if (!error_code)
                {
                    if (matrixes[0].allocated && matrixes[1].allocated)
                    {
                        error_code = std_sum(matrixes, &matrix_res, &clocks_std);
                        printf("time spend with standard matrixes: %ld\n", clocks_std);
                        printf("memory spend with standard matrixes: %ld bites\n", 3 * sizeof(int) * matrixes->columns * matrixes->rows + 3 * sizeof(matrixes));
                    }
                    else
                        error_code = NOT_ALLOCATED;
                }
                break;
            case 8:
                if (parses[0].columns != parses[1].columns && matrixes[0].rows != matrixes[1].rows)
                    error_code = INCORRECT_MATR_SIZE;

                if (!error_code)
                {
                    if (parses[0].allocated && parses[1].allocated)
                    {    
                        total_len = 0;
                        delete_parse(&parse_res);
                        found_total_len(parses, &total_len);
                        parse_res.elements = malloc(total_len * sizeof(int));
                        parse_res.index_row = malloc(total_len * sizeof(int));
                        parse_res.cols_en = malloc(parses[0].columns * sizeof(int));
                        parse_res.e_amount = total_len;
                        parse_res.columns = parses[0].columns;
                        clocks_parse = 0;
                        parse_sum(parses, &parse_res, &clocks_parse);
                        std_sum(matrixes, &matrix_res, &clocks_std);
                        fill_cols_en(&parse_res, &matrix_res);
                        printf("time spend with parse matrixes: %ld\n", clocks_parse);
                        printf("memory spend with sparce matrixes: %ld bites\n", sizeof(int) * (2 * total_len + parses[0].columns * 3 + parses[0].e_amount * 2 + parses[1].e_amount * 2 + sizeof(parse)));
                    }
                    else
                        error_code = NOT_ALLOCATED;    
                }
                break;
            case 0:
                delete_matr(&matrixes[0]);
                delete_matr(&matrixes[1]);
                delete_matr(&matrix_res);
                delete_parse(&parses[0]);
                delete_parse(&parses[1]);
                delete_parse(&parse_res);
                break;
            default:
                error_code = UNKNOWN_COMMAND;
                break;
            }
            print_error(error_code);
        }
        while(getchar()!='\n')
        {}
    } while (command);

    return 0;
}


void print_menu()
{
    printf("--------------------------------------\n");
    printf("| List of Commands  \n");
    printf("| 1: Load matrix from file \n");
    printf("| 2: Generate random matrix \n");
    printf("| 3: Load Matrix from console \n");
    printf("| 4: Show matrix \n");
    printf("| 5: Parse matrix \n");
    printf("| 6: Show a Parsed matrix \n");
    printf("| 7: Summurize 2 matrixes (using standart forms) \n");
    printf("| 8: Summurize 2 matrixes (sparse) \n");
    printf("| 0: Exit \n");
    printf("--------------------------------------\n");
    printf("| Input command: ");
}

void print_error(int error_code)
{
    if (error_code == INVALID_INPUT)
        printf("Invalid input\n");
    else if (error_code == INCORRECT_DATAFILE)
        printf("Incorrect data file\n");
    else if (error_code == ALLOC_ERROR)
        printf("Allocation error\n");
    else if (error_code == INCORRECT_DATA_ERROR)
        printf("Incorrect data\n");
    else if (error_code == NOT_ALLOCATED)
        printf("Matrix not allocated\n");
    else if (error_code == UNKNOWN_COMMAND)
        printf("Unknown_command\n");
    else if (error_code == INCORRECT_MATR_SIZE)
        printf("Incorrect matr size!\n");
}