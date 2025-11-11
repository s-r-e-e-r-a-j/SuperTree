// Developer: Sreeraj
// GitHub: https://github.com/s-r-e-e-r-a-j 

#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>

bool is_dir(const char *path);
bool path_exists(const char *path);
long get_total_size(const char *path);
void format_size(long size, char *buf, size_t buf_size); 

#endif
