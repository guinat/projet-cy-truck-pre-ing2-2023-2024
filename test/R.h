#if !defined(__R__H__)
#define __R__H__

#include "RE.h"
#include "city.h"

#define MAX_TOWNS 1000

typedef struct Routes
{
    int routeID;
    route_element_t *route_element;
    struct Routes *left;
    struct Routes *right;
    int height;
} routes_t;

int max_r(int a, int b);
int height_r(routes_t *node);
routes_t *new_route(int routeID);
routes_t *right_rotate_r(routes_t *y);
routes_t *left_rotate_r(routes_t *x);
int get_balance_r(routes_t *N);
routes_t *insert_route(routes_t *node, int routeID);
void write_stepID_one_townA_to_file(routes_t *root, const char *filename);
void write_cities_for_route(routes_t *route, FILE *start_file, FILE *count_file);
void write_cities_to_file(routes_t *root);
void write_city_details(route_element_t *element, FILE *start_file, FILE *count_file, city_t **city_root);
void free_routes(routes_t *root);

#endif // __R__H__
