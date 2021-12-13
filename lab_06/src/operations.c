#include "operations.h"

int bfactor(node_avl_t* p)
{
	return height(p->right) - height(p->left);
}

static int is_prime(int n)
{
    int a = 2;
    while (n % a)
        a++;
    
    if (n == a)
        return 1;
    else
        return 0;
}

int make_prime(int n)
{
    while (!is_prime(n))
        n++;

    return n;
}

node_t *create_node(int n)
{
    node_t *new_node = malloc(sizeof(node_t));
    new_node->data = n;
    new_node->left = NULL;
    new_node->right = NULL;

    return new_node;
}

node_t *insert(node_t *cur_node, int n)
{
    if (cur_node == NULL)
        return create_node(n);

    if (n - cur_node->data < 0)
        cur_node->left = insert(cur_node->left, n);
    else if (n - cur_node->data > 0)
        cur_node->right = insert(cur_node->right, n);

    return cur_node;
}

void read_nodes(node_t *src, int *values, int *size)
{
    if (!src)
        return;

    read_nodes(src->left, values, size);
    values[(*size)++] = src->data;
    read_nodes(src->right, values, size);
}

node_avl_t *build_tree(int *values, int start, int end)
{
    if (start > end)
        return NULL;
    int mid = (start + end) / 2;
    node_avl_t *root = create_avl_node(values[mid]);
    root->left = build_tree(values, start, mid - 1);
    root->right = build_tree(values, mid + 1, end);
    if (root->left && root->right)
        root->height = root->left->height > root->right->height ? root->left->height : root->right->height;
    else if (root->left)
        root->height = root->left->height;
    else if (root->right)
        root->height = root->right->height;
    root->height++;
    
    return root;
}

node_avl_t *balance_tree(tree_arr *tree_src)
{
    int *values = malloc(sizeof(int) * tree_src->size);
    int size = 0;                           
    read_nodes(tree_src->arr, values, &size);

    node_avl_t *bal_tree = build_tree(values, 0, size - 1);
    free(values);

    return bal_tree;
}

void replace_node(node_t **node, int *cmp_count)
{
    (*cmp_count)++;
    if (!(*node)->left && !(*node)->right)
        *node = NULL;
    else if ((*node)->left)
    {
        (*cmp_count)++;
        node_t *tmp = (*node)->left;
        if (!tmp->right && !tmp->left)
        {
            (*node)->data = tmp->data;
            free(tmp);
            (*node)->left = NULL;
        }
        else if (tmp->right)
        {
            while (tmp->right->right)
            {
                (*cmp_count)++;
                tmp = tmp->right;
            }
            node_t *tmp_b = tmp->right;
            (*node)->data = tmp->right->data;
            tmp->right = tmp->right->left;
            free(tmp_b);
        }
        else if (tmp->left)
        {
            (*node)->data = tmp->data;
            (*node)->left = tmp->left;
            free(tmp);
        }
    }
    else if ((*node)->right)
    {
        (*cmp_count)++;
        node_t *tmp = (*node)->right;
        if (!tmp->right && !tmp->left)
        {
            (*node)->data = tmp->data;
            free(tmp);
            (*node)->right = NULL;
        }
        else if (tmp->left)
        {
            while (tmp->left->left)
            {
                (*cmp_count)++;
                tmp = tmp->left;
            }
            node_t *tmp_b = tmp->left;
            (*node)->data = tmp->left->data;
            tmp->left = tmp->left->right;
            free(tmp_b);
        }
        else if (tmp->right)
        {
            (*node)->data = tmp->data;
            (*node)->right = tmp->right;
            free(tmp);
        }
    }

}

int pop_from_bin(node_t **node, int num_to_del)
{
    int cmp_count = 0;
    node_t *father_node = *node;
    node_t *res_find = find_bin(&father_node, num_to_del, &cmp_count);
    if (father_node == res_find)
        replace_node(node, &cmp_count);
    else if (!res_find->left && !res_find->right)
    {
        if (res_find == father_node->left)
            father_node->left = NULL;
        else
            father_node->right = NULL;
        free(res_find);
    }
    else if (father_node->left && father_node->left->data == num_to_del)
        replace_node(&father_node->left, &cmp_count);
    else if (father_node->right && father_node->right->data == num_to_del)
        replace_node(&father_node->right, &cmp_count);

    return cmp_count;
}

node_t *find_bin(node_t **node, int num_to_find, int *cmp_count)
{
    if (!(*node))
        return NULL;
    if ((*node)->data == num_to_find)
        return *node;
    if ((*node)->left && (*node)->left->data == num_to_find)
        return (*node)->left;
    if ((*node)->right && (*node)->right->data == num_to_find)
        return (*node)->right;
    (*cmp_count)++;
    node_t *tmp = (*node)->left;
    node_t *res_node = find_bin(&tmp, num_to_find, cmp_count);
    if (res_node == NULL)
    {
        tmp = (*node)->right;
        res_node = find_bin(&tmp, num_to_find, cmp_count);
    }
    *node = tmp;
    
    return res_node;
}

int pop_from_file(char *filename, int num_to_del)
{
    int cmp_count = 1;
    FILE *f = fopen(filename, "r");
    FILE *f_tmp = fopen("temp2.txt", "w+");
    int tmp;
    while (fscanf(f, "%d", &tmp) != EOF && tmp != num_to_del)
    {
        cmp_count++;
        fprintf(f_tmp, "%d\n", tmp);
    }
    while (fscanf(f, "%d", &tmp) != EOF)
        fprintf(f_tmp, "%d\n", tmp);
    
    fclose(f);
    rewind(f_tmp);
    f = fopen(filename, "w");
    f_tmp = fopen("temp2.txt", "r");
    while (fscanf(f_tmp, "%d", &tmp) != EOF)
        fprintf(f, "%d\n", tmp);
    fclose(f);
    fclose(f_tmp);
    remove("temp2.txt");

    return cmp_count;
}

size_t tree_size(node_t *node)
{
    if (!node)
        return 0;
    
    size_t size = tree_size(node->left);
    size += sizeof(node_t);
    size += tree_size(node->right);
    
    return size;
}

size_t tree_avl_size(node_avl_t *node)
{
    if (!node)
        return 0;
    
    size_t size = tree_avl_size(node->left);
    size += sizeof(node_avl_t);
    size += tree_avl_size(node->right);
    
    return size;
}

size_t file_size(char *filename)
{
    FILE *f = fopen(filename, "r");
    fseek(f, 0L, SEEK_END);
    size_t size = ftell(f);
    fclose(f);

    return size;
}

void free_tree(node_t *node)
{
    if (!node)
        return;
    
    free_tree(node->left);
    free_tree(node->right);
    free(node);
}

void free_avl_tree(node_avl_t *node)
{
    if (!node)
        return;
    
    free_avl_tree(node->left);
    free_avl_tree(node->right);
    free(node);
}

static void check_in(node_t *node, int *max_depth, int *min_depth, int cur_depth)
{
    if (!node)
    {
        if (*min_depth > cur_depth)
            *min_depth = cur_depth;
        if (*max_depth < cur_depth)
            *max_depth = cur_depth;

        return;
    }
    cur_depth++;
    check_in(node->left, max_depth, min_depth, cur_depth);
    check_in(node->right, max_depth, min_depth, cur_depth);
}

int check_avl(node_t *node)
{
    int max_depth = 0, min_depth = INT_MAX;
    check_in(node, &max_depth, &min_depth, 0);

    return max_depth - min_depth;
}

void get_avg_time(char *filename_src, uint64_t *bin_time, uint64_t *bal_time, uint64_t *hash_time, uint64_t *file_time)
{
    char command[BUFSIZ];
    snprintf(command, BUFSIZ, "cp %s %s", filename_src, "temp.txt");
    system(command);
    char filename[] = "temp.txt";
    int count;
    uint64_t t;
    FILE *f = fopen(filename, "r");
    int cur_n;
    tree_arr tree_copy;
    read_tree(f, &tree_copy);
    fclose(f);

    tree_avl bal_tree;
    bal_tree.size = tree_copy.size;
    bal_tree.arr = balance_tree(&tree_copy);

    hash_t hash_table;
    hash_table.size = make_prime(bal_tree.size * HASH_RATE * HASH_RATE);
    hash_table.hash_num = make_prime(bal_tree.size * HASH_RATE * HASH_RATE);
    gen_hashtable(filename, &hash_table, B);

    fopen(filename, "r");
    while (fscanf(f, "%d", &cur_n) != EOF)
    {
        count++;
        int tmp = 0;
        t = tick();
        remove_me(&bal_tree.arr, cur_n, &tmp);
        t = tick() - t;
        *bal_time += t;
        
        t = tick();
        pop_from_bin(&tree_copy.arr, cur_n);
        t = tick() - t;
        *bin_time += t;
        
        t = tick();
        pop_from_hash(&hash_table, cur_n, B);
        t = tick() - t;
        *hash_time += t;

        fclose(f);
        t = tick();
        pop_from_file(filename, cur_n);
        t = tick() - t;
        *file_time += t;
        fopen(filename, "r");
    }
    *bal_time = *bal_time / count;
    *bin_time = *bin_time / count;
    *hash_time = *hash_time / count;
    *file_time = *file_time / count;
    free_avl_tree(bal_tree.arr);
    free_tree(tree_copy.arr);
    free(hash_table.hash_table);
    free(hash_table.is_occupied);
    remove("temp.txt");   














    // if (*bin_time < *bal_time)
    // {
    //     uint64_t ttt = *bin_time;
    //     *bin_time = *bal_time;
    //     *bal_time = ttt;
    // }
}