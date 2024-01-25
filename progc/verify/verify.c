#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/**
 * @brief Get the filename
 *
 * @param path
 * @return char*
 */
char *get_filename(const char *path)
{
    char *base = strrchr(path, '/');
    if (base)
        base++;
    else
        base = (char *)path;

    char *ret = strdup(base);
    char *lastdot = strrchr(ret, '.');
    if (lastdot != NULL)
        *lastdot = '\0';

    return ret; // Return filename without ext
}

/**
 * @brief Write errors
 *
 * @param log_file
 * @param line_count
 * @param line
 */
void log_error(FILE *log_file, int line_count, char *line)
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    fprintf(log_file, "Error: Line %d is not in the correct format: %s Checked on %d-%02d-%02d %02d:%02d:%02d\n", line_count, line, tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
}

/**
 * @brief Function to verify the CSV file format
 *
 * @param path
 * @return int
 */
int verify_csv_format(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        fprintf(stderr, "Could not open file %s\n", filename);
        return 1;
    }

    char *base_filename = get_filename(filename);
    char log_filename[256];
    sprintf(log_filename, "../../data/%s.log", base_filename);

    FILE *log_file = fopen(log_filename, "a");
    if (log_file == NULL)
    {
        fprintf(stderr, "Error: Could not open log file.\n");
        fclose(file);
        return 1;
    }

    char line[1024];
    int line_count = 0;
    int error_detected = 0;

    while (fgets(line, sizeof(line), file))
    {
        line_count++;

        char *token = strtok(line, ";");
        if (!token)
        {
            log_error(log_file, line_count, "Missing route_id");
            error_detected = 1;
            continue;
        }
        int route_id = atoi(token);

        token = strtok(NULL, ";");
        if (!token)
        {
            log_error(log_file, line_count, "Missing step_id");
            error_detected = 1;
            continue;
        }
        int step_id = atoi(token);

        token = strtok(NULL, ";");
        if (!token)
        {
            log_error(log_file, line_count, "Missing town_a");
            error_detected = 1;
            continue;
        }
        char town_a[256];
        strncpy(town_a, token, sizeof(town_a));

        token = strtok(NULL, ";");
        if (!token)
        {
            log_error(log_file, line_count, "Missing town_b");
            error_detected = 1;
            continue;
        }
        char town_b[256];
        strncpy(town_b, token, sizeof(town_b));

        token = strtok(NULL, ";");
        if (!token)
        {
            log_error(log_file, line_count, "Missing distance");
            error_detected = 1;
            continue;
        }
        double distance = atof(token);

        token = strtok(NULL, ";");
        if (!token)
        {
            log_error(log_file, line_count, "Missing driver_name");
            error_detected = 1;
            continue;
        }
        char driver_name[256];
        strncpy(driver_name, token, sizeof(driver_name));
    }

    if (!error_detected)
    {
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        fprintf(log_file, "File is correct. Checked on %d-%02d-%02d %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    }

    fclose(file);
    fclose(log_file);
    return error_detected ? 1 : 0;
}

/**
 * @brief Verify the file format
 *
 * @param argc
 * @param argv
 * @return int
 */
int main(int argc, char *argv[])
{
    if (argc != 2)
        return 1;

    if (verify_csv_format(argv[1]) != 0)
        return 1;

    return 0;
}