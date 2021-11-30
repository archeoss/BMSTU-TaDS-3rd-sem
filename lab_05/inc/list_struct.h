#ifndef _LIST_STRUCT_H_

#define _LIST_STRUCT_H_


typedef struct node
{
    float work_time;
    struct node *next;
} node_t;

typedef struct List
{
    node_t *head;
    node_t *bottom;
    int count;
    inter_t to_arrive, to_process;
} list_t;

typedef struct node_mem
{
    size_t address;
    struct node_mem *next;
} mem_t;

#endif