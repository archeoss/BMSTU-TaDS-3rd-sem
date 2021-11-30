#ifndef _MEM_ALLOC_H_

#define _MEM_ALLOC_H_

#include <stdlib.h>
#include "structures.h"

int **alloc_matrix(int n, int m);

void delete_matr(matrix *matr);

void delete_parse(parse *pars);

#endif