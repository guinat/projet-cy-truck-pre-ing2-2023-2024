#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/t_processing.h"

/**
 * @brief Function to insert a new city in the AVL tree
 *
 * @param node
 * @param city
 * @return node_t_t*
 */
node_t_t *node_insert_t(node_t_t *node, city_t city)
{
    if (node == NULL)
        return (node_create_t(city));

    if (city.total_count < node->data.total_count)
        node->left = node_insert_t(node->left, city);
    else if (city.total_count > node->data.total_count)
        node->right = node_insert_t(node->right, city);
    else
        return node;

    node->height = 1 + max_t(height_t(node->left), height_t(node->right));

    int balance = get_balance_t(node);

    if (balance > 1 && city.total_count < node->left->data.total_count)
        return right_rotate_t(node);

    if (balance < -1 && city.total_count > node->right->data.total_count)
        return left_rotate_t(node);

    if (balance > 1 && city.total_count > node->left->data.total_count)
    {
        node->left = left_rotate_t(node->left);
        return right_rotate_t(node);
    }

    if (balance < -1 && city.total_count < node->right->data.total_count)
    {
        node->right = right_rotate_t(node->right);
        return left_rotate_t(node);
    }

    return node;
}

/**
 * @brief Function to get the height of the tree
 *
 * @param node
 * @return int
 */
int height_t(node_t_t *node)
{
    if (node == NULL)
        return 0;
    return node->height;
}

/**
 * @brief Function to get the max between two integers
 *
 * @param a
 * @param b
 * @return int
 */
int max_t(int a, int b)
{
    return (a > b) ? a : b;
}

/**
 * @brief Function to create a new node
 *
 * @param city
 * @return node_t_t*
 */
node_t_t *node_create_t(city_t city)
{
    node_t_t *node = (node_t_t *)malloc(sizeof(node_t_t));
    if (!node)
    {
        perror("Error allocating memory");
        exit(EXIT_FAILURE);
    }
    node->data = city;

    node->left = NULL;
    node->right = NULL;

    node->height = 1;

    return node;
}

/**
 * @brief Function to right rotate a node
 *
 * @param y
 * @return node_t_t*
 */
node_t_t *right_rotate_t(node_t_t *y)
{
    node_t_t *x = y->left;
    node_t_t *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max_t(height_t(y->left), height_t(y->right)) + 1;
    x->height = max_t(height_t(x->left), height_t(x->right)) + 1;

    return x;
}

/**
 * @brief Function to left rotate a node
 *
 * @param x
 * @return node_t_t*
 */
node_t_t *left_rotate_t(node_t_t *x)
{
    node_t_t *y = x->right;
    node_t_t *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max_t(height_t(x->left), height_t(x->right)) + 1;
    y->height = max_t(height_t(y->left), height_t(y->right)) + 1;

    return y;
}

/**
 * @brief Get the Balance object
 *
 * @param node
 * @return int
 */
int get_balance_t(node_t_t *node)
{
    if (node == NULL)
        return 0;
    return height_t(node->left) - height_t(node->right);
}

/**
 * @brief Function to print the tree in order
 *
 * @param root
 * @param top_cities
 * @param count
 */
void top_10_cities_t(node_t_t *root, city_t top_cities[], int *count)
{
    if (root != NULL && *count < 10)
    {
        top_10_cities_t(root->right, top_cities, count);
        if (*count < 10)
        {
            top_cities[*count] = root->data;
            (*count)++;
        }
        top_10_cities_t(root->left, top_cities, count);
    }
}

/**
 * @brief Function to sort the cities alphabetically
 *
 * @param cities
 * @param n
 */
void sort_cities_alphabetically_t(city_t cities[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (strcmp(cities[j].name, cities[j + 1].name) > 0)
            {
                city_t temp = cities[j];
                cities[j] = cities[j + 1];
                cities[j + 1] = temp;
            }
        }
    }
}

/**
 * @brief Function to write the top cities in a file
 *
 * @param filename
 * @param cities
 * @param n
 */
void write_top_cities_t(const char *filename, city_t cities[], int n)
{
    FILE *file = fopen(filename, "w");
    if (!file)
    {
        perror("Error opening file");
        return;
    }

    for (int i = 0; i < n; i++)
    {
        fprintf(file, "%s;%d;%d\n", cities[i].name, cities[i].total_count, cities[i].start_count);
    }

    fclose(file);
}

/**
 * @brief Main processing function for t_processing.
 *
 * @param input_path
 * @param output_path
 */
void t_processing(const char *input_path, const char *output_path)
{
    node_t_t *root = NULL;
    city_t top_cities[10];
    int top_count = 0;

    FILE *file = fopen(input_path, "r");
    if (!file)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char line[LINE_LENGTH];
    while (fgets(line, sizeof(line), file))
    {
        city_t new_city;
        sscanf(line, "%[^;];%d;%d", new_city.name, &new_city.total_count, &new_city.start_count);
        root = node_insert_t(root, new_city);
    }
    fclose(file);

    top_10_cities_t(root, top_cities, &top_count);

    sort_cities_alphabetically_t(top_cities, top_count);

    write_top_cities_t(output_path, top_cities, top_count);
}