#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/t_processing.h"
#include "../include/s_processing.h"

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        fprintf(stderr, "Usage: %s <option> <input_path> <output_path>\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "-t") == 0)
    {
        t_processing(argv[2], argv[3]);
    }
    else if (strcmp(argv[1], "-s") == 0)
    {
        s_processing(argv[2], argv[3]);
    }
    else
    {
        fprintf(stderr, "Invalid option: %s\n", argv[1]);
        return 1;
    }

    return 0;
}