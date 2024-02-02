#ifndef COMMON_H

#define COMMON_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>

#define PRINT_ERR(err_func, fmt, args...) \
        do { fprintf(stderr, (fmt), ##args); perror(#err_func); } while(0)

#endif /* COMMON_H */
