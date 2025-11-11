// Developer: Sreeraj
// GitHub: https://github.com/s-r-e-e-r-a-j 

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include "../include/display.h"
#include "../include/color.h"
#include "../include/utils.h"

typedef struct {
    char name[512];
    char full_path[4096];
    off_t size;
    off_t total_size;
    int is_dir;
} Entry;

static int compare_by_total_size(const void *a, const void *b) {
    const Entry *x = (const Entry *)a;
    const Entry *y = (const Entry *)b;
    if (x->total_size < y->total_size) return 1;
    if (x->total_size > y->total_size) return -1;
    return strcmp(x->name, y->name);
}

void print_dir(const char *path, int level, int max_depth, int dirs_only,
               int show_size, int json, int is_root, int sort_by_size) {
    if (max_depth != -1 && level > max_depth)
        return;

    DIR *dir;
    struct dirent *entry;
    if (!(dir = opendir(path))) return;

    Entry *entries = NULL;
    size_t count = 0, capacity = 0;

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        char full_path[4096];
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

        if (dirs_only && !is_dir(full_path))
            continue;

        struct stat s;
        if (lstat(full_path, &s) == -1) continue;

        if (count == capacity) {
            capacity = capacity ? capacity * 2 : 32;
            entries = realloc(entries, capacity * sizeof(Entry));
        }

        strncpy(entries[count].name, entry->d_name, sizeof(entries[count].name) - 1);
        entries[count].name[sizeof(entries[count].name) - 1] = '\0';

        strncpy(entries[count].full_path, full_path, sizeof(entries[count].full_path) - 1);
        entries[count].full_path[sizeof(entries[count].full_path) - 1] = '\0';

        entries[count].size = s.st_size;
        entries[count].is_dir = S_ISDIR(s.st_mode);
        entries[count].total_size = entries[count].is_dir
            ? get_total_size(full_path)
            : entries[count].size;

        count++;
    }
    closedir(dir);

    if (sort_by_size && count > 1) {
        qsort(entries, count, sizeof(Entry), compare_by_total_size);
    }

    if (json && is_root) printf("{\n");

    for (size_t i = 0; i < count; i++) {
        char size_str[32] = "";
        if (show_size) format_size(entries[i].total_size, size_str, sizeof(size_str));

        if (!json) {
            for (int j = 0; j < level; j++) printf("│   ");
            printf("├── ");
            color_print(entries[i].full_path, entries[i].name, show_size ? size_str : NULL);
        } else {
            for (int j = 0; j < level; j++) printf("  ");
            printf("\"%s\": ", entries[i].name);
        }

        if (entries[i].is_dir) {
            if (json) printf("{\n");
            print_dir(entries[i].full_path, level + 1, max_depth, dirs_only,
                      show_size, json, 0, sort_by_size);
            if (json) {
                for (int j = 0; j < level; j++) printf("  ");
                printf("},\n");
            }
        } else if (json) {
            printf("\"file\",\n");
        }
    }

    free(entries);
}
