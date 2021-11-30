#ifndef _ARR_AO_H_

#define _ARR_AO_H_

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "io.h"
#include "structures.h"
#include "arr_struct.h"
#include "errors.h"
#include "operations.h"
#include "colors.h"
#include "constants.h"

void simulation_arr(arr_t *, arr_t *);

void push_arr_back(arr_t *qa);
void push_arr(arr_t *qa, float);
float popa_arr(arr_t *qa);

#endif