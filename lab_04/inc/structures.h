#ifndef _STRUCTURES_H_

#define _STRUCTURES_H_

typedef struct node
{
    float data;
    struct node *next;
} node_t;

typedef struct frmem
{
    long address;
    struct frmem *next;
} frmem_t;

#endif