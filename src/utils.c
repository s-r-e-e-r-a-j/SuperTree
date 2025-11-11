// Developer: Sreeraj
// GitHub: https://github.com/s-r-e-e-r-a-j 

#include <sys/stat.h>
#include <stdbool.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/utils.h"

bool is_dir(const char *path) {
    struct stat s;
    if (stat(path, &s) == 0 && S_ISDIR(s.st_mode))
        return true;
    return false;
}

bool path_exists(const char *path) {
    return access(path, F_OK) == 0;
}

long get_total_size(const char *path) {
    struct stat st;
    long total = 0;

    if (lstat(path, &st) == 0)
        total += st.st_size;

    if (S_ISDIR(st.st_mode)) {
        DIR *dir = opendir(path);
        if (!dir) return total;

        struct dirent *entry;
        char full[4096];
        while ((entry = readdir(dir)) != NULL) {
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;
            snprintf(full, sizeof(full), "%s/%s", path, entry->d_name);
            total += get_total_size(full);
        }
        closedir(dir);
    }

    return total;
}

void format_size(long size, char *buf, size_t buf_size) {
    const char *units[] = {"B", "KB", "MB", "GB", "TB"};
    int i = 0;
    double s = (double)size;

    while (s >= 1024 && i < 4) {
        s /= 1024;
        i++;
    }

    snprintf(buf, buf_size, "%.2f %s", s, units[i]);
}
