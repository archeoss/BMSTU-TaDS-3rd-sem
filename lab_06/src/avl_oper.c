#include "avl_oper.h"

int height(node_avl_t* node)
{
	return node ? node->height : 0;
}

void replace_avl_node(node_avl_t **node, int *cmp_count)
{
    (*cmp_count)++;
    if (!(*node)->left && !(*node)->right)
        *node = NULL;
    else if ((*node)->left)
    {
        (*cmp_count)++;
        node_avl_t *tmp = (*node)->left;
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
            node_avl_t *tmp_b = tmp->right;
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
        node_avl_t *tmp = (*node)->right;
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
            node_avl_t *tmp_b = tmp->left;
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

int pop_from_avl(node_avl_t **node, int num_to_del)
{
    int cmp_count = 0;
    node_avl_t *father_node = *node;
    node_avl_t *res_find = find_avl(&father_node, num_to_del, &cmp_count);
    if (father_node == res_find)
        replace_avl_node(node, &cmp_count);
    else if (!res_find->left && !res_find->right)
    {
        if (res_find == father_node->left)
            father_node->left = NULL;
        else
            father_node->right = NULL;
        free(res_find);
    }
    else if (father_node->left && father_node->left->data == num_to_del)
        replace_avl_node(&father_node->left, &cmp_count);
    else if (father_node->right && father_node->right->data == num_to_del)
        replace_avl_node(&father_node->right, &cmp_count);
    
    
    return cmp_count;
}

node_avl_t *find_avl(node_avl_t **node, int num_to_find, int *cmp_count)
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
    node_avl_t *tmp = (*node)->left;
    node_avl_t *res_node = find_avl(&tmp, num_to_find, cmp_count);
    if (res_node == NULL)
    {
        tmp = (*node)->right;
        res_node = find_avl(&tmp, num_to_find, cmp_count);
    }
    *node = tmp;
    
    return res_node;
}

node_avl_t *create_avl_node(int n)
{
    node_avl_t *new_node = malloc(sizeof(node_avl_t));
    new_node->data = n;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->height = 0;

    return new_node;
}

static void fixheight(node_avl_t* node)
{
	int hl = height(node->left);
	int hr = height(node->right);
	node->height = (hl > hr ? hl : hr) + 1;
}

static node_avl_t* rotateright(node_avl_t* node) 
{
	node_avl_t* q = node->left;
	node->left = q->right;
	q->right = node;
	fixheight(node);
	fixheight(q);

	return q;
}

static node_avl_t* rotateleft(node_avl_t* q)
{
	node_avl_t* node = q->right;
	q->right = node->left;
	node->left = q;
	fixheight(q);
	fixheight(node);

	return node;
}

node_avl_t* balance(node_avl_t* node)
{
	fixheight(node);
	if (bfactor(node) > 1)
	{
		if(bfactor(node->right) < 0 )
			node->right = rotateright(node->right);
		return rotateleft(node);
	}
	if (bfactor(node) < -1)
	{
		if( bfactor(node->left) > 0  )
			node->left = rotateleft(node->left);
		return rotateright(node);
	}

	return node;
}

node_avl_t* findmin(node_avl_t* node, int *cmp_count) 
{
    (*cmp_count)++;
	return node->left ? findmin(node->left, cmp_count) : node;
}

node_avl_t* removemin(node_avl_t* node, int *cmp_count)
{
    (*cmp_count)++;
	if (node->left == 0)
		return node->right;
	node->left = removemin(node->left, cmp_count);
	
    return balance(node);
}

void remove_me(node_avl_t **node, int num_to_del, int *cmp_count)
{
	if (!*node)
        return;

    (*cmp_count)++;
    if (num_to_del < (*node)->data)
		remove_me(&(*node)->left, num_to_del, cmp_count);
	else if (num_to_del > (*node)->data)
		remove_me(&(*node)->right, num_to_del, cmp_count);
    else
	{
		node_avl_t *left = (*node)->left;
		node_avl_t *right = (*node)->right;
		
        if (!right)
        {
            *node = left;
            return;
        }

        node_avl_t* min = findmin(right, cmp_count);
		min->right = removemin(right, cmp_count);
		min->left = left;
		
        *node = balance(min);
        return;
	}

    *node = balance(*node);
    return;
}