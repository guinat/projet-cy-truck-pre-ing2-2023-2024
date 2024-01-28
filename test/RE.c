#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "RE.h"

/**
 * @brief Function to get the maximum of two integers
 *
 * @param a
 * @param b
 * @return int
 */
int max_re(int a, int b)
{
    return (a > b) ? a : b;
}

/**
 * @brief Function to get the height of a route element
 *
 * @param node
 * @return int
 */
int height_re(route_element_t *node)
{
    if (node == NULL)
        return 0;
    return node->height;
}

/**
 * @brief Function to create a new route element
 *
 * @param townA
 * @param townB
 * @param stepID
 * @return route_element_t*
 */
route_element_t *new_route_element(char *townA, char *townB, int stepID)
{
    route_element_t *node = (route_element_t *)malloc(sizeof(route_element_t));
    if (!node)
    {
        fprintf(stderr, "Error allocating memory for route element\n");
        exit(EXIT_FAILURE);
    }
    node->townA = strdup(townA);
    node->townB = strdup(townB);
    node->stepID = stepID;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

/**
 * @brief Function to right rotate a route element
 *
 * @param y
 * @return route_element_t*
 */
route_element_t *right_rotate_re(route_element_t *y)
{
    route_element_t *x = y->left;
    route_element_t *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max_re(height_re(y->left), height_re(y->right)) + 1;
    x->height = max_re(height_re(x->left), height_re(x->right)) + 1;

    return x;
}

/**
 * @brief Function to left rotate a route element
 *
 * @param x
 * @return route_element_t*
 */
route_element_t *left_rotate_re(route_element_t *x)
{
    route_element_t *y = x->right;
    route_element_t *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max_re(height_re(x->left), height_re(x->right)) + 1;
    y->height = max_re(height_re(y->left), height_re(y->right)) + 1;

    return y;
}

/**
 * @brief Get the Balance R E object
 *
 * @param node
 * @return int
 */
int get_balance_re(route_element_t *node)
{
    if (node == NULL)
        return 0;
    return height_re(node->left) - height_re(node->right);
}

/**
 * @brief Function to insert a route element
 *
 * @param node
 * @param townA
 * @param townB
 * @param stepID
 * @return route_element_t*
 */
route_element_t *insert_route_element(route_element_t *node, char *townA, char *townB, int stepID)
{
    if (node == NULL)
        return (new_route_element(townA, townB, stepID));

    if (stepID < node->stepID)
        node->left = insert_route_element(node->left, townA, townB, stepID);
    else if (stepID > node->stepID)
        node->right = insert_route_element(node->right, townA, townB, stepID);
    else
        return node;

    node->height = 1 + max_re(height_re(node->left), height_re(node->right));

    int balance = get_balance_re(node);

    if (balance > 1 && stepID < node->left->stepID)
        return right_rotate_re(node);
    if (balance < -1 && stepID > node->right->stepID)
        return left_rotate_re(node);
    if (balance > 1 && stepID > node->left->stepID)
    {
        node->left = left_rotate_re(node->left);
        return right_rotate_re(node);
    }
    if (balance < -1 && stepID < node->right->stepID)
    {
        node->right = right_rotate_re(node->right);
        return left_rotate_re(node);
    }

    return node;
}

/**
 * @brief Function to write city details to file
 *
 * @param element
 * @param start_file
 * @param count_file
 * @param city_root
 */
void write_city_details(route_element_t *element, FILE *start_file, FILE *count_file, city_t **city_root)
{
    if (element != NULL)
    {
        write_city_details(element->left, start_file, count_file, city_root);

        // Écrire townA pour stepID == 1 dans start.txt, sinon dans count.txt
        if (!search_city(*city_root, element->townA))
        {
            *city_root = insert_c(*city_root, element->townA);
            fprintf(element->stepID == 1 ? start_file : count_file, "%s\n", element->townA);
        }

        // Écrire townB toujours dans count.txt
        if (!search_city(*city_root, element->townB))
        {
            *city_root = insert_c(*city_root, element->townB);
            fprintf(count_file, "%s\n", element->townB);
        }

        write_city_details(element->right, start_file, count_file, city_root);
    }
}

/**
 * @brief Function to free a route element
 *
 * @param root
 */
void free_route_element(route_element_t *root)
{
    if (root != NULL)
    {
        free_route_element(root->left);
        free_route_element(root->right);
        free(root->townA);
        free(root->townB);
        free(root);
    }
}
