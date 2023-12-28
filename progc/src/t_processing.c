#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/t_processing.h"

node_t *node_create(const char *city_name, int count_trips_through, int count_trips_start)
{
    node_t *node = (node_t *)malloc(sizeof(node_t));
    if (!node)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    node->city_name = strdup(city_name);
    if (!(node->city_name))
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    node->count_trips_through = count_trips_through;
    node->count_trips_start = count_trips_start;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;

    return node;
}

int height(node_t *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

node_t *right_rotate(node_t *y)
{
    node_t *x = y->left;
    node_t *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

node_t *left_rotate(node_t *x)
{
    node_t *y = x->right;
    node_t *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

int get_balance(node_t *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

node_t *node_insert(node_t *node, const char *city_name, int count_trips_through, int count_trips_start)
{
    if (node == NULL)
        return node_create(city_name, count_trips_through, count_trips_start);

    int cmp = strcmp(city_name, node->city_name);
    if (cmp < 0)
    {
        node->left = node_insert(node->left, city_name, count_trips_through, count_trips_start);
    }
    else if (cmp > 0)
    {
        node->right = node_insert(node->right, city_name, count_trips_through, count_trips_start);
    }
    else
    {
        node->count_trips_through += count_trips_through;
        node->count_trips_start += count_trips_start;
        return node;
    }

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = get_balance(node);

    if (balance > 1 && strcmp(city_name, node->left->city_name) < 0)
        return right_rotate(node);

    if (balance < -1 && strcmp(city_name, node->right->city_name) > 0)
        return left_rotate(node);

    if (balance > 1 && strcmp(city_name, node->left->city_name) > 0)
    {
        node->left = left_rotate(node->left);
        return right_rotate(node);
    }

    if (balance < -1 && strcmp(city_name, node->right->city_name) < 0)
    {
        node->right = right_rotate(node->right);
        return left_rotate(node);
    }

    return node;
}

void process_csv_file(const char *file_path, node_t **root)
{
    FILE *file = fopen(file_path, "r");
    if (!file)
    {
        fprintf(stderr, "Unable to open file: %s\n", file_path);
        return;
    }

    char line[MAX_LINE_LENGTH];
    const char *delimiter = ";";

    fgets(line, MAX_LINE_LENGTH, file);

    while (fgets(line, MAX_LINE_LENGTH, file))
    {
        char *route_id = strtok(line, delimiter);
        char *step_id_str = strtok(NULL, delimiter);
        char *start_city = strtok(NULL, delimiter);
        char *end_city = strtok(NULL, delimiter);

        if (end_city)
        {
            *root = node_insert(*root, strdup(end_city), 1, 0);
        }

        int step_id = atoi(step_id_str);
        if (start_city && step_id == 1)
        {
            *root = node_insert(*root, strdup(start_city), 1, 1);
        }
    }

    fclose(file);
}

int count_nodes(node_t *node)
{
    if (node == NULL)
        return 0;
    return 1 + count_nodes(node->left) + count_nodes(node->right);
}

int compare_nodes(const void *a, const void *b)
{
    const node_t *nodeA = *(const node_t **)a;
    const node_t *nodeB = *(const node_t **)b;
    int totalA = nodeA->count_trips_through + nodeA->count_trips_start;
    int totalB = nodeB->count_trips_through + nodeB->count_trips_start;

    return totalB - totalA;
}

int compare_nodes_for_alpha(const void *a, const void *b)
{
    const node_t *nodeA = *(const node_t **)a;
    const node_t *nodeB = *(const node_t **)b;
    return strcmp(nodeA->city_name, nodeB->city_name);
}

void store_nodes_in_array(node_t *node, node_t *node_array[], int *index)
{
    if (node != NULL)
    {
        store_nodes_in_array(node->left, node_array, index);
        node_array[*index] = node;
        (*index)++;
        store_nodes_in_array(node->right, node_array, index);
    }
}

void write_top_cities_to_file(node_t *root, const char *output_path, int city_count)
{
    node_t *node_array[city_count];
    int index = 0;

    store_nodes_in_array(root, node_array, &index);

    qsort(node_array, city_count, sizeof(node_t *), compare_nodes);

    FILE *file = fopen(output_path, "w");
    if (!file)
    {
        fprintf(stderr, "Unable to open file for writing: %s\n", output_path);
        return;
    }

    qsort(node_array, (city_count > 10 ? 10 : city_count), sizeof(node_t *), compare_nodes_for_alpha);

    for (int i = 0; i < 10 && i < city_count; i++)
    {
        node_t *node = node_array[i];
        fprintf(file, "%s;%d;%d\n", node->city_name, node->count_trips_through, node->count_trips_start);
    }

    fclose(file);
}

void free_avl_tree(node_t *node)
{
    if (node != NULL)
    {
        free_avl_tree(node->left);
        free_avl_tree(node->right);
        free(node->city_name);
        free(node);
    }
}

void t_processing(const char *input_path, const char *output_path)
{
    node_t *root = NULL;

    process_csv_file(input_path, &root);

    int city_count = count_nodes(root);

    write_top_cities_to_file(root, output_path, city_count);

    free_avl_tree(root);
}
