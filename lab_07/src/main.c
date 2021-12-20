#include "io.h"
#include "errors.h"
#include "colors.h"
#include <time.h>
#include "structures.h"
#include "operations.h"
#include "graphvis.h"
#include "timer.h"

/*
Задан граф - не дерево. Проверить, можно ли
превратить его в дерево удалением одной
вершины вместе с ее ребрами.
*/

int main(int args, char **keys)
{
    uint64_t t;
    int tmp, tmp_rc;
    int error_code = NO_ERROR;
    FILE *f;
    graph_t grph;
    if (args != 2 || (f = fopen(keys[1], "r")) == NULL || (tmp_rc = fscanf(f, "%d", &tmp)) == EOF || tmp_rc == 0)
    {
        printf(RED"Incorrect file! Exiting the programm\n"CLR);
        return INVALID_INPUT;
    }
    rewind(f);
    char graphs_dir[] = "graphs/";
    char graph_name[] = "graph";
    char graph_del_name[] = "new_graph";
    char command[BUFSIZ];
    error_code = read_graph(f, &grph);
    fclose(f);
    graph_to_dot(graphs_dir, graph_name, &grph, NOTHING_TODEL);
    snprintf(command, BUFSIZ, "dot -Tpng %s%s.dot -o %s%s.png", graphs_dir, graph_name, graphs_dir, graph_name);
    system(command);
    printf(GREEN"%s.png generated at %s\n"CLR, graph_name, graphs_dir);
    
    if (error_code == NO_ERROR)
    {
        grph.edges = count_edges(&grph);
        int todel;
        t = tick();
        if (grph.edges == grph.size - 1)
        {
            todel = check_connect(&grph, NOTHING_TODEL);
            if (todel == NOT_CONNECTED)
            {
                int n = find_notconnected(&grph);
                if (n != NOTHING_TODEL)
                    todel = check_connect(&grph, n);
            }
        }
        else
            todel = wannabe_tree(&grph);
        t = tick() - t;

        if (todel == NOTHING_TODEL)
            printf(GREEN"Граф уже является деревом\n"CLR);
        else if (todel == NOT_CONNECTED)
            printf(RED"Перестройка из графа в дерево невозможно\n"CLR);
        else
        {
            printf(YELLOW"\nДля преобразования графа в дерево,\nнеобходимо удалить %d узел\n\n"CLR, todel);
            graph_to_dot(graphs_dir, graph_del_name, &grph, todel);
            snprintf(command, BUFSIZ, "dot -Tpng %s%s.dot -o %s%s.png", graphs_dir, graph_del_name, graphs_dir, graph_del_name);
            system(command);
            printf(GREEN"%s.png generated at %s\n"CLR, graph_del_name, graphs_dir);
        }
        printf(BLUE"\nНа нахождение нужного узла было затрачено %ld тиков\n"CLR, t);
        printf(BLUE"Граф, на основе списка смежности занимает %ld байт\n"CLR, get_size(&grph));
        free_array(grph.array, grph.size);
    }
    
    return error_code;
}
