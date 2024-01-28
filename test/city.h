#if !defined(__CITY__H__)
#define __CITY__H__

typedef struct City
{
    char *city;
    struct City *left;
    struct City *right;
    int height;
} city_t;

int max_c(int a, int b);
int height_c(city_t *city);
city_t *new_city(char *city);
city_t *right_rotate_c(city_t *y);
city_t *left_rotate_c(city_t *x);
int get_balance_c(city_t *city);
city_t *insert_c(city_t *city, char *city_name);
int search_city(city_t *city, char *city_name);
void free_city(city_t *city);

#endif // __CITY__H__
