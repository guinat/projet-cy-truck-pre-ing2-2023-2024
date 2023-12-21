#if !defined(__D2__PROCESSING__H__)
#define __D2__PROCESSING__H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Driver
{
    char name[100]; // char *name;
    double totalDistance;
} driver_t;

typedef struct AVL_Node
{
    driver_t driver;
    struct AVLNode *left, *right;
    int height;
} avl_node_t;

#endif // __D2__PROCESSING__H__
