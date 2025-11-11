// Developer: Sreeraj
// GitHub: https://github.com/s-r-e-e-r-a-j 

#ifndef DISPLAY_H
#define DISPLAY_H

#include <stddef.h>

void print_dir(
    const char *path,
    int level,
    int max_depth,
    int dirs_only,
    int show_size,
    int json,
    int is_root,
    int sort_by_size
);

void format_size(long size, char *buffer, size_t buffer_size);

#endif
