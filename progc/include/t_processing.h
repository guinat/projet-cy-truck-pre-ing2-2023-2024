#if !defined(__T__PROCESSING__H__)
#define __T__PROCESSING__H__

typedef struct CityData
{
    char *city;
    int trips_through;
    int trips_start;
} city_data_t;

typedef struct AVLNode
{
    city_data_t city_data;
    int height;
    struct AVLNode *left;
    struct AVLNode *right;
} avl_node_t;

#endif // __T__PROCESSING__H__
