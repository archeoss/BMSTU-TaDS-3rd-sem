#ifndef _GRAPHVIS_H_

#define _GRAPGVIS_H_

#include "errors.h"
#include "colors.h"
#include "structures.h"
#include <stdlib.h>
#include <stdio.h>

void graph_tree_to_dot(char *cwd, char *tree_name, node_t *self, int show_dots);

#endif
