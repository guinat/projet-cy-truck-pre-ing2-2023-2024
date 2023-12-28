#if !defined(__S__PROCESSING__H__)
#define __S__PROCESSING__H__

#define MAX_LINE_LENGTH 1024

typedef struct Node_s
{
    int route_id;
    double min_distance;
    double max_distance;
    double total_distance;
    int step_count;
    struct Node_s *left;
    struct Node_s *right;
    int height;
} node_s_t;

typedef struct
{
    int route_id;
    double min_distance;
    double total_distance;
    double max_distance;
    double distance_diff;
    int step_count;
} route_data_s_t;

node_s_t *node_create_s(int route_id, double min_distance, double max_distance, double total_distance, int step_count);
int height_s(node_s_t *node);
int max_s(int a, int b);
int get_balance_s(node_s_t *node);
node_s_t *right_rotate_s(node_s_t *y);
node_s_t *left_rotate_s(node_s_t *x);
node_s_t *node_insert_s(node_s_t *node, int route_id, double distance);

void process_csv_file_s(const char *file_path, node_s_t **root);

int compare_route_data_s(const void *a, const void *b);
void collect_data_s(node_s_t *node, route_data_s_t *data, int *index);
void write_top_50_results_s(node_s_t *root, const char *outputFile);

void free_avl_tree_s(node_s_t *root);

void s_processing(const char *input_path, const char *output_path);

#endif // __S__PROCESSING__H__
