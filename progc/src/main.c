#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Include the header files for t_processing and s_processing.
#include "../include/t_processing.h"
#include "../include/s_processing.h"

#define MAX_LINE_LENGTH_ 1024

/**
 * @brief Function to verify the CSV file format.
 *
 * @param filename
 * @return int
 */
int verify_csv_format(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        perror("Error opening file");
        return 1; // File opening failed
    }

    char line[MAX_LINE_LENGTH_];
    int line_count = 0;

    while (fgets(line, MAX_LINE_LENGTH_, file))
    {
        line_count++;
        line[strcspn(line, "\n")] = 0;

        if (line_count == 1)
            continue; // Skip header

        char *token = strtok(line, ";");
        int field_count = 0;

        while (token)
        {
            field_count++;
            token = strtok(NULL, ";");
        }

        if (field_count != 6)
        {
            fprintf(stderr, "Error: Line %d is not in the correct format.\n", line_count);
            fclose(file);
            return 1; // Incorrect format
        }
    }

    fclose(file);
    return 0; // Format is correct
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
    if (argc != 4)
    {
        fprintf(stderr, "Usage: %s <option> <input_path> <output_path>\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "-t") == 0)
    {
        // Call the t_processing function with input and output paths.
        t_processing(argv[2], argv[3]);
    }
    else if (strcmp(argv[1], "-s") == 0)
    {
        // Call the s_processing function with input and output paths.
        s_processing(argv[2], argv[3]);
    }
    else
    {
        fprintf(stderr, "Invalid option: %s\n", argv[1]);
        return 1;
    }

    return 0;
}
