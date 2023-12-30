#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#include "../include/s_processing.h"

/**
 * @brief Function to create a new AVL tree node.
 *
 * @param route_id
 * @param min_distance
 * @param max_distance
 * @param total_distance
 * @param step_count
 * @return node_s_t*
 */
node_s_t *node_create_s(int route_id, double min_distance, double max_distance, double total_distance, int step_count)
{
    node_s_t *new_node = (node_s_t *)malloc(sizeof(node_s_t));
    if (new_node == NULL)
    {
        fprintf(stderr, "Error allocating memory for new node\n");
        return NULL;
    }

    new_node->route_id = route_id;
    new_node->min_distance = min_distance;
    new_node->max_distance = max_distance;
    new_node->total_distance = total_distance;
    new_node->step_count = step_count;
    new_node->left = new_node->right = NULL;
    new_node->height = 1;

    return new_node;
}

/**
 * @brief Function to get the height of a node.
 *
 * @param node
 * @return int
 */
int height_s(node_s_t *node)
{
    if (node == NULL)
        return 0;
    return node->height;
}

/**
 * @brief Function to return the maximum of two integers.
 *
 * @param a
 * @param b
 * @return int
 */
int max_s(int a, int b)
{
    return (a > b) ? a : b;
}

/**
 * @brief Function to get the balance factor of a node.
 *
 * @param node
 * @return int
 */
int get_balance_s(node_s_t *node)
{
    if (node == NULL)
        return 0;
    return height_s(node->left) - height_s(node->right);
}

/**
 * @brief Function to perform a right rotation on a node.
 *
 * @param y
 * @return node_s_t*
 */
node_s_t *right_rotate_s(node_s_t *y)
{
    node_s_t *x = y->left;
    node_s_t *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max_s(height_s(y->left), height_s(y->right)) + 1;
    x->height = max_s(height_s(x->left), height_s(x->right)) + 1;

    return x;
}

/**
 * @brief Function to perform a left rotation on a node.
 *
 * @param x
 * @return node_s_t*
 */
node_s_t *left_rotate_s(node_s_t *x)
{
    node_s_t *y = x->right;
    node_s_t *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max_s(height_s(x->left), height_s(x->right)) + 1;
    y->height = max_s(height_s(y->left), height_s(y->right)) + 1;

    return y;
}

/**
 * @brief Function to insert a node into an AVL tree.
 *
 * @param node
 * @param route_id
 * @param distance
 * @return node_s_t*
 */
node_s_t *node_insert_s(node_s_t *node, int route_id, double distance)
{
    if (node == NULL)
        return node_create_s(route_id, distance, distance, distance, 1);

    if (route_id < node->route_id)
        node->left = node_insert_s(node->left, route_id, distance);
    else if (route_id > node->route_id)
        node->right = node_insert_s(node->right, route_id, distance);
    else
    {
        node->step_count++;
        node->total_distance += distance;
        node->min_distance = (distance < node->min_distance) ? distance : node->min_distance;
        node->max_distance = (distance > node->max_distance) ? distance : node->max_distance;
    }

    node->height = 1 + max_s(height_s(node->left), height_s(node->right));

    int balance = get_balance_s(node);

    if (balance > 1 && route_id < node->left->route_id)
        return right_rotate_s(node);

    if (balance < -1 && route_id > node->right->route_id)
        return left_rotate_s(node);

    if (balance > 1 && route_id > node->left->route_id)
    {
        node->left = left_rotate_s(node->left);
        return right_rotate_s(node);
    }

    if (balance < -1 && route_id < node->right->route_id)
    {
        node->right = right_rotate_s(node->right);
        return left_rotate_s(node);
    }

    return node;
}

/**
 * @brief Function to process a CSV file and build an AVL tree.
 *
 * @param file_path
 * @param root
 */
void process_csv_file_s(const char *file_path, node_s_t **root)
{
    FILE *file = fopen(file_path, "r");
    if (!file)
    {
        fprintf(stderr, "Error opening file: %s\n", file_path);
        return;
    }

    char line[1024];
    int lineCount = 0;

    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file))
    {
        lineCount++;
        char *token = strtok(line, ";");
        if (!token)
        {
            fprintf(stderr, "Malformed line at %d: Missing route_id\n", lineCount);
            continue;
        }
        int route_id = atoi(token);

        token = strtok(NULL, ";");
        for (int i = 0; i < 3; i++)
        {
            token = strtok(NULL, ";");
            if (!token)
            {
                fprintf(stderr, "Malformed line at %d: Missing data\n", lineCount);
                break;
            }
        }

        if (token)
        {
            double distance = atof(token);
            if (distance > 0)
            {
                *root = node_insert_s(*root, route_id, distance);
            }
            else
            {
                fprintf(stderr, "Invalid distance at line %d\n", lineCount);
            }
        }
    }

    fclose(file);
}

/**
 * @brief Comparison function for qsort.
 *
 * @param a
 * @param b
 * @return int
 */
int compare_route_data_s(const void *a, const void *b)
{
    double diff = ((route_data_s_t *)b)->distance_diff - ((route_data_s_t *)a)->distance_diff;
    return (diff > 0) - (diff < 0);
}

/**
 * @brief Function to collect data from AVL tree nodes into an array.
 *
 * @param node
 * @param data
 * @param index
 */
void collect_data_s(node_s_t *node, route_data_s_t *data, int *index)
{
    if (node == NULL)
    {
        return;
    }
    collect_data_s(node->left, data, index);
    data[*index].route_id = node->route_id;
    data[*index].min_distance = node->min_distance;
    data[*index].total_distance = node->total_distance;
    data[*index].max_distance = node->max_distance;
    data[*index].distance_diff = node->max_distance - node->min_distance;
    data[*index].step_count = node->step_count;
    (*index)++;
    collect_data_s(node->right, data, index);
}

/**
 * @brief Function to write the top 50 results to an output file.
 *
 * @param root
 * @param output_file
 */
void write_top_50_results_s(node_s_t *root, const char *output_file)
{
    int estimated_size = pow(2, root->height) - 1;
    route_data_s_t *data = malloc(estimated_size * sizeof(route_data_s_t));
    if (!data)
    {
        fprintf(stderr, "Error allocating memory for data\n");
        return;
    }

    int index = 0;
    collect_data_s(root, data, &index);

    qsort(data, index, sizeof(route_data_s_t), compare_route_data_s);

    FILE *file = fopen(output_file, "w");
    if (!file)
    {
        fprintf(stderr, "Error opening output file: %s\n", output_file);
        free(data);
        return;
    }

    for (int i = 0; i < 50 && i < index; i++)
    {
        fprintf(file, "%d;%d;%.3f;%.3f;%.3f;%.3f\n",
                i + 1, data[i].route_id, data[i].min_distance, data[i].total_distance / data[i].step_count,
                data[i].max_distance, data[i].distance_diff);
    }

    fclose(file);
    free(data);
}

/**
 * @brief Function to free memory allocated for the AVL tree.
 *
 * @param node
 */
void free_avl_tree_s(node_s_t *node)
{
    if (node != NULL)
    {
        free_avl_tree_s(node->left);
        free_avl_tree_s(node->right);
        free(node);
    }
}

/**
 * @brief Main processing function.
 *
 * @param input_path
 * @param output_path
 */
void s_processing(const char *input_path, const char *output_path)
{
    node_s_t *root = NULL;

    process_csv_file_s(input_path, &root);
    write_top_50_results_s(root, output_path);
    free_avl_tree_s(root);
}
