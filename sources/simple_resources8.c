#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


#define BUFF_SIZE 1000


typedef struct {
    FILE *input;
    char *line_buffer;
} Resources;

// Construct new Resources
Resources new_resources() {
    return (Resources) {.input = NULL, .line_buffer = NULL};
}

// Clean up Resources
void cleanup(Resources *res) {
    if (res->input != NULL) {
        // Fixed
        fclose(res->input);
        res->input = NULL;
    }
    if (res->line_buffer != NULL) {
        free(res->line_buffer);
        res->line_buffer = NULL;
    }
}

// Initialize Resources
int prepare(Resources *res, char *file_name) {
    res->line_buffer = malloc(sizeof(char) * BUFF_SIZE);
    if (res->line_buffer != NULL) {
        res->input = fopen(file_name, "r");
        if (res->input != NULL) {
            return 1;
        }
    }
    // Fixed
    cleanup(res);
    return 0;
}


int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s FILE1 FILE1\n", argv[0]);
        return 1;
    }

    Resources r1 = new_resources();
    Resources r2 = new_resources();
    if (!prepare(&r1, argv[1]))
        return 2;
    if (!prepare(&r2, argv[2])) {
        cleanup(&r1);
        return 2;
    }

    // Do something with the resources, e.g., parse the file
    sleep(3);

    cleanup(&r1);
    // Fixed
    cleanup(&r2);

    return 0;
}