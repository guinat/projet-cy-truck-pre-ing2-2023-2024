#if !defined(__RE_H__)
#define __RE_H__

#include <stdbool.h>

#include "city.h"

typedef struct RouteElement
{
    char *townA;
    char *townB;
    int stepID;
    struct RouteElement *left;
    struct RouteElement *right;
    int height;
} route_element_t;

int max_re(int a, int b);
int height_re(route_element_t *node);
route_element_t *new_route_element(char *townA, char *townB, int stepID);
route_element_t *right_rotate_re(route_element_t *y);
route_element_t *left_rotate_re(route_element_t *x);
int get_balance_re(route_element_t *node);
route_element_t *insert_route_element(route_element_t *node, char *townA, char *townB, int stepID);
void write_city_details(route_element_t *element, FILE *start_file, FILE *count_file, city_t **city_root);
void free_route_element(route_element_t *root);

#endif // __RE_H__
