/* See LICENSE file for copyright and license details. */
#ifndef UTILITIES_H
#define UTILITIES_H

#include <stdlib.h>

#define MAX_DEPS 16
#define MAX_CMDS 16
#define MAX_RULES 128

#define COLOR_GREEN "\033[32m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_GRAY "\033[90m"
#define COLOR_RED "\033[31m"
#define COLOR_RESET "\033[0m"

/* simple DIE macro. */
#define DIE(msg)                      \
    do {                              \
        fprintf(stderr, "%s\n", msg); \
        exit(1);                      \
    } while (0)

#define GLOB(x) (void)(x)

#endif
