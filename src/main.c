// Developer: Sreeraj
// GitHub: https://github.com/s-r-e-e-r-a-j 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include "../include/display.h"
#include "../include/utils.h"

void print_help() {
    printf("Usage: supertree [options] [path]\n\n");
    printf("Options:\n");
    printf("  -L <depth>       Limit recursion depth\n");
    printf("  -S               Sort entries by size (largest first)\n");
    printf("  --dirs-only      Show only directories\n");
    printf("  --size           Show file sizes\n");
    printf("  --json           Output in JSON format\n");
    printf("  -h, --help       Show this help message\n\n");
    printf("Example:\n  supertree -L 2 -S --size /etc\n");
}

int main(int argc, char *argv[]) {
    char path[PATH_MAX];
    getcwd(path, sizeof(path));

    int max_depth = -1;
    int show_dirs_only = 0;
    int show_size = 0;
    int json_output = 0;
    int sort_by_size = 0;

    // Parse args
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            print_help();
            return 0;
        } else if (strcmp(argv[i], "-L") == 0 && i + 1 < argc) {
            max_depth = atoi(argv[++i]);
        } else if (strcmp(argv[i], "--dirs-only") == 0) {
            show_dirs_only = 1;
        } else if (strcmp(argv[i], "--size") == 0) {
            show_size = 1;
        } else if (strcmp(argv[i], "--json") == 0) {
            json_output = 1;
        } else if (strcmp(argv[i], "-S") == 0) {
            sort_by_size = 1;
        } else {
            strcpy(path, argv[i]);
        }
    }

    if (!path_exists(path)) {
        fprintf(stderr, "Error: path '%s' does not exist.\n", path);
        return 1;
    }

    print_dir(path, 0, max_depth, show_dirs_only, show_size, json_output, 1, sort_by_size);
    if (json_output) printf("}\n");

    return 0;
}
