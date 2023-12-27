#if !defined(__T__PROCESSING__H__)
#define __T__PROCESSING__H__

#define MAX_LINE_LENGTH 1024

typedef struct Node
{
    char *city_name;
    int count_trips_through;
    int count_trips_start;
    struct Node *left;
    struct Node *right;
    int height;
} node_t;

node_t *node_create(const char *city_name, int count_trips_through, int count_trips_start);
int height(node_t *N);
int max(int a, int b);
int get_balance(node_t *N);
node_t *right_rotate(node_t *y);
node_t *left_rotate(node_t *x);
node_t *node_insert(node_t *node, const char *city_name, int count_trips_through, int count_trips_start);

void process_csv_file(const char *file_path, node_t **root);
int count_nodes(node_t *root);
int compare_nodes(const void *a, const void *b);
int compare_nodes_for_alpha(const void *a, const void *b);
void store_nodes_in_array(node_t *node, node_t *node_array[], int *index);
void write_top_cities_to_file(node_t *root, const char *output_path, int city_count);

void free_node(node_t *node);
void free_avl_tree(node_t *node);

void t_processing(const char *input_path, const char *output_path);

#endif // __T__PROCESSING__H__
