#define MAX_CITIES 10000
#define LINE_LENGTH 100

typedef struct City
{
    char name[50];
    int total_count;
    int start_count;
} city_t;

typedef struct Node_t
{
    city_t data;
    struct Node_t *left;
    struct Node_t *right;
    int height;
} node_t_t;

// Function prototypes

int height_t(node_t_t *node);
int max_t(int a, int b);
int get_balance_t(node_t_t *node);
node_t_t *node_create_t(city_t city);
node_t_t *right_rotate_t(node_t_t *y);
node_t_t *left_rotate_t(node_t_t *x);
node_t_t *node_insert_t(node_t_t *node, city_t city);

void top_10_cities_t(node_t_t *root, city_t top_cities[], int *count);
void sort_cities_alphabetically_t(city_t cities[], int n);
void write_top_cities_t(const char *filename, city_t cities[], int n);
void inOrderT(node_t_t *root);
void t_processing(const char *input_path, const char *output_path);