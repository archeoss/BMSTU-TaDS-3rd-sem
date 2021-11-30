#ifndef _OPERATIONS_H_

#define _OPERATIONS_H_

#include "errors.h"
#include "colors.h"
#include "structures.h"
#include "arr_struct.h"
#include "list_struct.h"
#include "operations.h"
#include <stdlib.h>
#include "constants.h"

void arr_setup(arr_t *qa_a, arr_t *qa_b, int size);
void list_setup(list_t *qa_a, list_t *qa_b);
double generate_time(inter_t inter);
float get_expected(inter_t to_arrive, inter_t to_process);
void clear_queue(list_t *ql);

#endif