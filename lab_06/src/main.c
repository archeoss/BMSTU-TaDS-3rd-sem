#include "io.h"
#include "errors.h"
#include "colors.h"
#include <time.h>
#include "structures.h"
#include "operations.h"
#include "graphvis.h"
#include "hash.h"
#include "timer.h"

int main(int args, char **keys)
{
    uint64_t t;
    int tmp, tmp_rc;
    int error_code = NO_ERROR;
    FILE *f;
    int mode = A;
    tree_arr tree;
    if (args != 2 || (f = fopen(keys[1], "r")) == NULL || (tmp_rc = fscanf(f, "%d", &tmp)) == EOF || tmp_rc == 0)
    {
        printf(RED"Incorrect file! Exiting the programm\n"CLR);
        return INVALID_INPUT;
    }
    rewind(f);
    char graphs_dir[] = "graphs/";
    char bin_tree_name[] = "bin_tree";
    char bal_tree_name[] = "balanced_tree";
    char bal_del_tree_name[] = "balanced_tree_del";
    char bin_del_tree_name[] = "bin_tree_del";
    char command[BUFSIZ];
    t = tick();
    read_tree(f, &tree);
    t = tick() - t;
    fclose(f);

    graph_tree_to_dot(graphs_dir, bin_tree_name, tree.arr, tree.size);
    snprintf(command, BUFSIZ, "dot -Tpng %s%s.dot -o %s%s.png", graphs_dir, bin_tree_name, graphs_dir, bin_tree_name);
    system(command);
    printf(GREEN"%s.png generated at %s\n"CLR, bin_tree_name, graphs_dir);
    printf(YELLOW"Tree generated in %ld ticks\n"CLR, t);
    //system("xdg-open graphs/kek.png");
    tree_arr bal_tree;
    bal_tree.size = tree.size;
    t = tick();
    bal_tree.arr = balance_tree(&tree);
    t = tick() - t;
    graph_tree_to_dot(graphs_dir, bal_tree_name, bal_tree.arr, tree.size);
    snprintf(command, BUFSIZ, "dot -Tpng %s%s.dot -o %s%s.png", graphs_dir, bal_tree_name, graphs_dir, bal_tree_name);
    system(command);
    printf(GREEN"%s.png generated at %s\n"CLR, bal_tree_name, graphs_dir);
    printf(YELLOW"Balanced tree generated in %ld ticks\n"CLR, t);
    //system("xdg-open graphs/kek2.png");

    int max_comparison;
    printf("Input maximun comparison count: ");
    tmp_rc = scanf("%d", &max_comparison);
    if (!tmp_rc || max_comparison < 1)
    {
        printf(RED"Incorrect input! Exiting the program."CLR);
        free_tree(tree.arr);
        free_tree(bal_tree.arr);
        return INVALID_INPUT;
    }
    printf("\n");
    hash_t hash_table;
    hash_table.size = bal_tree.size * HASH_RATE;
    hash_table.hash_num = bal_tree.size * HASH_RATE;
    t = tick();
    int cmp = gen_hashtable(keys[1], &hash_table, A);
    t = tick() - t;
    while (cmp > max_comparison)
    {
        mode = B;
        printf(RED"Current compares (%d) is more than max (%d). Re-generating hash-table...\n"CLR, cmp, max_comparison);
        hash_table.size *= HASH_RATE;
        hash_table.hash_num *= HASH_RATE;
        free(hash_table.hash_table);
        free(hash_table.is_occupied);
        t = tick();
        cmp = gen_hashtable(keys[1], &hash_table, B);
        t = tick() - t;
    }
    print_hash(&hash_table);
    printf(YELLOW"Maximum comparison in that hash table: %d\n"CLR, cmp);
    printf(YELLOW"Hash-table generated in %ld ticks\n"CLR, t);

    int num_to_del;
    printf("Input number to delete: ");
    tmp_rc = scanf("%d", &num_to_del);
    printf("\n");
    tmp = 0;
    if (tmp_rc && hash_find(&hash_table, num_to_del, &tmp, hash_func_a) > -1)
    {
        t = tick();
        int cmp_count = pop_from_hash(&hash_table, num_to_del, mode);
        t = tick() - t;
        print_hash(&hash_table);
        printf(BPURPLE"Hash-table\n"CLR);
        printf(YELLOW"Deletion from hash-table consumed %ld ticks\n"CLR, t);
        printf(YELLOW"Size of hash-table with %d elements: %ld\n", hash_table.size, sizeof(int) * 2 * hash_table.size);
        printf(YELLOW"Comparisons count: %d\n", cmp_count);
        t = tick();
        cmp_count = pop_from_bin(&tree.arr, num_to_del);
        t = tick() - t;
        printf(BPURPLE"Binary tree (non-balanced)\n"CLR);
        printf(YELLOW"Deletion from binary tree consumed %ld ticks\n"CLR, t);
        printf(YELLOW"Size of binary tree with %d elements: %ld\n"CLR, tree.size, tree_size(tree.arr));
        printf(YELLOW"Comparisons count: %d\n", cmp_count);
        graph_tree_to_dot(graphs_dir, bin_del_tree_name, tree.arr, --tree.size);
        snprintf(command, BUFSIZ, "dot -Tpng %s%s.dot -o %s%s.png", graphs_dir, bin_del_tree_name, graphs_dir, bin_del_tree_name);
        system(command);
        t = tick();
        cmp_count = pop_from_bin(&bal_tree.arr, num_to_del);
        t = tick() - t;
        printf(BPURPLE"Binary tree (balanced)\n"CLR);
        printf(YELLOW"Deletion from binary balanced tree consumed %ld ticks\n"CLR, t);
        printf(YELLOW"Size of tree with %d elements: %ld\n"CLR, bal_tree.size, tree_size(bal_tree.arr));
        printf(YELLOW"Comparisons count: %d\n", cmp_count);
        graph_tree_to_dot(graphs_dir, bal_del_tree_name, bal_tree.arr, --bal_tree.size);
        snprintf(command, BUFSIZ, "dot -Tpng %s%s.dot -o %s%s.png", graphs_dir, bal_del_tree_name, graphs_dir, bal_del_tree_name);
        system(command);
        t = tick();
        cmp_count = pop_from_file(keys[1], num_to_del);
        t = tick() - t;
        printf(BPURPLE"File\n"CLR);
        printf(YELLOW"Deletion from binary balanced tree consumed %ld ticks\n"CLR, t);
        printf(YELLOW"Size of file with %d elements: %ld\n"CLR, bal_tree.size + 1, file_size(keys[1]));
        printf(YELLOW"Comparsions count: %d\n"CLR, cmp_count);
    }
    else
        printf(RED"Number not found.\n"CLR);

    free(hash_table.hash_table);
    free(hash_table.is_occupied);
    free_tree(tree.arr);
    free_tree(bal_tree.arr);

    return error_code;
}
