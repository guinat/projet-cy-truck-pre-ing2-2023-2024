#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "RE.h"
#include "R.h"

/**
 * @brief Function to process a CSV file
 *
 * @param filename
 * @param root
 */
void process_csv(const char *filename, routes_t **root)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        perror("Unable to open file");
        exit(1);
    }

    char line[1024];

    fgets(line, sizeof(line), file); // skip header line

    while (fgets(line, sizeof(line), file))
    {
        char *townA, *townB;
        int routeID, stepID;
        char *token = strtok(line, ";");
        if (token)
        {
            routeID = atoi(token);
            token = strtok(NULL, ";");
        }
        if (token)
        {
            stepID = atoi(token);
            token = strtok(NULL, ";");
        }
        if (token)
        {
            townA = strdup(token);
            token = strtok(NULL, ";");
        }
        if (token)
        {
            townB = strdup(token);
            *root = insert_route(*root, routeID);
            routes_t *route_node = *root;
            while (route_node && route_node->routeID != routeID)
            {
                if (routeID < route_node->routeID)
                {
                    route_node = route_node->left;
                }
                else
                {
                    route_node = route_node->right;
                }
            }
            if (route_node)
            {
                route_node->route_element = insert_route_element(route_node->route_element, townA, townB, stepID);
            }
            free(townA);
            free(townB);
        }
    }
    fclose(file);
}

/**
 * @brief Main function
 *
 * @param argc
 * @param argv
 * @return int
 */
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <input csv file>\n", argv[0]);
        return 1;
    }

    routes_t *root = NULL;
    process_csv(argv[1], &root);

    // write_stepID_one_townA_to_file(root, "output.txt");

    write_cities_to_file(root);

    // city_t *city_root = NULL;

    // city_root = insert_c(city_root, "Paris");
    // city_root = insert_c(city_root, "Lyon");
    // city_root = insert_c(city_root, "Marseille");

    // if (search_city(city_root, "Paris"))
    //     printf("Paris found\n");
    // else
    //     printf("Paris not found\n");

    // free_city(city_root);

    free_routes(root);

    return 0;
}
