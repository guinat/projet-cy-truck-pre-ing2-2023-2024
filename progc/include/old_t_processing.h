#if !defined(__T__PROCESSING__H__)
#define __T__PROCESSING__H__

// Define a constant for the maximum line length.
#define MAX_LINE_LENGTH 1024

// Define a struct for a binary tree node.
typedef struct Node
{
    char *city_name;
    int count_trips_through;
    int count_trips_start;
    struct Node *left;
    struct Node *right;
    int height;
} node_t;

// Function prototypes for AVL tree operations.
node_t *node_create(const char *city_name, int count_trips_through, int count_trips_start);
int height(node_t *node);
int max(int a, int b);
int get_balance(node_t *node);
node_t *right_rotate(node_t *y);
node_t *left_rotate(node_t *x);
node_t *node_insert(node_t *node, const char *city_name, int count_trips_through, int count_trips_start);

// Function prototype for CSV processing.
void process_csv_file(const char *file_path, node_t **root);

// Function prototypes for data manipulation and output.
int count_nodes(node_t *root);
int compare_nodes(const void *a, const void *b);
int compare_nodes_for_alpha(const void *a, const void *b);
void store_nodes_in_array(node_t *node, node_t *node_array[], int *index);
void write_top_cities_to_file(node_t *root, const char *output_path, int city_count);

// Function prototype for freeing memory allocated for the AVL tree.
void free_avl_tree(node_t *node);

// Main processing function prototype.
void old_t_processing(const char *input_path, const char *output_path);

#endif // __T__PROCESSING__H__