// Developer: Sreeraj
// GitHub: https://github.com/s-r-e-e-r-a-j 

#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include "../include/color.h"

#define COLOR_RESET  "\033[0m"
#define COLOR_DIR    "\033[1;34m"
#define COLOR_EXE    "\033[1;32m"
#define COLOR_LINK   "\033[1;36m"
#define COLOR_FILE   "\033[0m"

void color_print(const char *path, const char *name, const char *size_str) {
    struct stat s;
    if (lstat(path, &s) == -1) {
        printf("%s\n", name);
        return;
    }

    if (S_ISDIR(s.st_mode))
        printf("%s%s%s", COLOR_DIR, name, COLOR_RESET);
    else if (S_ISLNK(s.st_mode))
        printf("%s%s%s", COLOR_LINK, name, COLOR_RESET);
    else if (s.st_mode & S_IXUSR)
        printf("%s%s%s", COLOR_EXE, name, COLOR_RESET);
    else
        printf("%s%s%s", COLOR_FILE, name, COLOR_RESET);

    if (size_str && strlen(size_str) > 0) {
        printf(" [%s]", size_str);
    }

    printf("\n");
}
