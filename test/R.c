#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "R.h"

/**
 * @brief Function to get the maximum of two integers
 *
 * @param a
 * @param b
 * @return int
 */
int max_r(int a, int b)
{
    return (a > b) ? a : b;
}

/**
 * @brief Function to get the height of a route
 *
 * @param node
 * @return int
 */
int height_r(routes_t *node)
{
    if (node == NULL)
        return 0;
    return node->height;
}

/**
 * @brief Function to create a new route
 *
 * @param routeID
 * @return routes_t*
 */
routes_t *new_route(int routeID)
{
    routes_t *node = (routes_t *)malloc(sizeof(routes_t));
    if (!node)
    {
        fprintf(stderr, "Error allocating memory for route\n");
        exit(EXIT_FAILURE);
    }
    node->routeID = routeID;
    node->route_element = NULL;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

/**
 * @brief Function to right rotate a route
 *
 * @param y
 * @return routes_t*
 */
routes_t *right_rotate_r(routes_t *y)
{
    routes_t *x = y->left;
    routes_t *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max_r(height_r(y->left), height_r(y->right)) + 1;
    x->height = max_r(height_r(x->left), height_r(x->right)) + 1;

    return x;
}

/**
 * @brief Function to left rotate a route
 *
 * @param x
 * @return routes_t*
 */
routes_t *left_rotate_r(routes_t *x)
{
    routes_t *y = x->right;
    routes_t *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max_r(height_r(x->left), height_r(x->right)) + 1;
    y->height = max_r(height_r(y->left), height_r(y->right)) + 1;

    return y;
}

/**
 * @brief Function to get the balance of a route
 *
 * @param node
 * @return int
 */
int get_balance_r(routes_t *node)
{
    if (node == NULL)
        return 0;
    return height_r(node->left) - height_r(node->right);
}

/**
 * @brief Function to insert a route
 *
 * @param node
 * @param routeID
 * @return routes_t*
 */
routes_t *insert_route(routes_t *node, int routeID)
{
    if (node == NULL)
        return (new_route(routeID));

    if (routeID < node->routeID)
        node->left = insert_route(node->left, routeID);
    else if (routeID > node->routeID)
        node->right = insert_route(node->right, routeID);
    else
        return node;

    node->height = 1 + max_r(height_r(node->left), height_r(node->right));

    int balance = get_balance_r(node);

    if (balance > 1 && routeID < node->left->routeID)
        return right_rotate_r(node);
    if (balance < -1 && routeID > node->right->routeID)
        return left_rotate_r(node);
    if (balance > 1 && routeID > node->left->routeID)
    {
        node->left = left_rotate_r(node->left);
        return right_rotate_r(node);
    }
    if (balance < -1 && routeID < node->right->routeID)
    {
        node->right = right_rotate_r(node->right);
        return left_rotate_r(node);
    }

    return node;
}

/**
 * @brief Function to write townA for step id one
 *
 * @param root
 * @param file
 */
void write_townA_for_stepID_one(routes_t *root, FILE *file)
{
    if (root != NULL)
    {
        write_townA_for_stepID_one(root->left, file);

        route_element_t *element = root->route_element;
        while (element != NULL)
        {
            if (element->stepID == 1)
            {
                fprintf(file, "%s\n", element->townA);
                break; // Arrêter la recherche après avoir trouvé stepID = 1
            }
            element = (element->stepID < 1) ? element->right : element->left;
        }

        write_townA_for_stepID_one(root->right, file);
    }
}

/**
 * @brief Write in file the cities for step id one
 *
 * @param root
 * @param filename
 */
void write_stepID_one_townA_to_file(routes_t *root, const char *filename)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        perror("Unable to open file");
        return;
    }

    write_townA_for_stepID_one(root, file);

    fclose(file);
}

/**
 * @brief Function to write cities
 *
 * @param route
 * @param start_file
 * @param count_file
 */
void write_cities_for_route(routes_t *route, FILE *start_file, FILE *count_file)
{

    if (route != NULL)
    {

        write_cities_for_route(route->left, start_file, count_file);
        city_t *city_root = NULL;
        write_city_details(route->route_element, start_file, count_file, &city_root);
        free_city(city_root);
        write_cities_for_route(route->right, start_file, count_file);
    }
}

/**
 * @brief Function to write city details
 *
 * @param root
 */
void write_cities_to_file(routes_t *root)
{
    FILE *start_file = fopen("start.txt", "w");
    FILE *count_file = fopen("count.txt", "w");
    if (start_file == NULL || count_file == NULL)
    {
        perror("Erreur à l'ouverture des fichiers");
        return;
    }

    write_cities_for_route(root, start_file, count_file);

    fclose(start_file);
    fclose(count_file);
}

/**
 * @brief Function to free a route element
 *
 * @param root
 */
void free_routes(routes_t *root)
{
    if (root != NULL)
    {
        free_routes(root->left);
        free_routes(root->right);
        free_route_element(root->route_element);
        free(root);
    }
}
