#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "city.h"

/**
 * @brief Function to get the maximum of two integers
 *
 * @param a
 * @param b
 * @return int
 */
int max_c(int a, int b)
{
    return (a > b) ? a : b;
}

/**
 * @brief Function to get the height of a city
 *
 * @param city
 * @return int
 */
int height_c(city_t *city)
{
    if (city == NULL)
        return 0;
    return city->height;
}

/**
 * @brief Function to create a new city
 *
 * @param city
 * @return city_t*
 */
city_t *new_city(char *city)
{
    city_t *new_city = (city_t *)malloc(sizeof(city_t));

    new_city->city = strdup(city);
    if (!new_city->city)
    {
        fprintf(stderr, "Error allocating memory for city name\n");
        exit(EXIT_FAILURE);
    }

    new_city->left = NULL;
    new_city->right = NULL;

    new_city->height = 1;

    return new_city;
}

/**
 * @brief Function to right rotate a city
 *
 * @param y
 * @return city_t*
 */
city_t *right_rotate_c(city_t *y)
{
    city_t *x = y->left;
    city_t *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max_c(height_c(y->left), height_c(y->right)) + 1;
    x->height = max_c(height_c(x->left), height_c(x->right)) + 1;

    return x;
}

/**
 * @brief Function to left rotate a city
 *
 * @param x
 * @return city_t*
 */
city_t *left_rotate_c(city_t *x)
{
    city_t *y = x->right;
    city_t *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max_c(height_c(x->left), height_c(x->right)) + 1;
    y->height = max_c(height_c(y->left), height_c(y->right)) + 1;

    return y;
}

/**
 * @brief Function to get the balance of a city
 *
 * @param city
 * @return int
 */
int get_balance_c(city_t *city)
{
    if (city == NULL)
        return 0;
    return height_c(city->left) - height_c(city->right);
}

/**
 * @brief Function to insert a city
 *
 * @param node
 * @param cityName
 * @return city_t*
 */
city_t *insert_c(city_t *node, char *city_name)
{
    if (node == NULL)
    {
        printf("Insertion : %s (nouveau noeud)\n", city_name);
        return new_city(city_name);
    }

    int cmp = strcmp(city_name, node->city);
    if (cmp < 0)
    {
        node->left = insert_c(node->left, city_name);
    }
    else if (cmp > 0)
    {
        node->right = insert_c(node->right, city_name);
    }
    else
    {
        printf("Insertion : %s (déjà présent)\n", city_name);
        return node;
    }

    node->height = 1 + max_c(height_c(node->left), height_c(node->right));
    int balance = get_balance_c(node);

    if (balance > 1 && strcmp(city_name, node->left->city) < 0)
        return right_rotate_c(node);

    if (balance < -1 && strcmp(city_name, node->right->city) > 0)
        return left_rotate_c(node);

    if (balance > 1 && strcmp(city_name, node->left->city) > 0)
    {
        node->left = left_rotate_c(node->left);
        return right_rotate_c(node);
    }

    if (balance < -1 && strcmp(city_name, node->right->city) < 0)
    {
        node->right = right_rotate_c(node->right);
        return left_rotate_c(node);
    }

    return node;
}

/**
 * @brief Function to search a city
 *
 * @param city
 * @param cityName
 * @return int
 */
int search_city(city_t *city, char *city_name)
{
    while (city != NULL)
    {
        int cmp = strcmp(city_name, city->city);
        if (cmp == 0)
        {
            printf("Ville trouvée : %s\n", city_name);
            return 1;
        }
        else if (cmp < 0)
        {
            city = city->left;
        }
        else
        {
            city = city->right;
        }
    }
    printf("Ville non trouvée : %s\n", city_name);
    return 0;
}

/**
 * @brief Function to print a city in order
 *
 * @param city
 */
void print_in_order(city_t *city)
{
    if (city != NULL)
    {
        print_in_order(city->left);
        printf("%s\n", city->city);
        print_in_order(city->right);
    }
}

/**
 * @brief Function to free a city
 *
 * @param root
 */
void free_city(city_t *root)
{
    if (root != NULL)
    {
        free_city(root->left);
        free_city(root->right);
        printf("Freeing %s\n", root->city); // erreur ?
        free(root->city);
        free(root);
    }
}