#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

#ifdef DMALLOC
#include "dmalloc.h"
#endif

/* Remedy double-free vulnerability */

typedef struct {
    char *d_buf;
    int d_fd;
} _DIR, *DIRp;


int _closedir(DIRp dirp) {
    int ret = 0;

    if (!dirp) { // check for NULL pointer before executing the main code
        ret = -1;
        return ret;
    }

    if (dirp->d_buf) {
        free(dirp->d_buf);
        dirp->d_buf = NULL; // not necessary but good practice
    }

    ret = close(dirp->d_fd); // first close the dir before free dirp

    free(dirp);
    dirp = NULL;

    return ret; // return the return value of close to the caller
}

int main(void) {

    printf("size of DIR is %zu\n", sizeof(_DIR));

    DIRp someDir = malloc(sizeof(_DIR));
    if (!someDir) { // check for failed allocation before proceeding
        fprintf(stderr, "Failed to allocate memory for DIR\n");
        perror("malloc");
        goto failure;
    }

    someDir->d_buf = NULL, someDir->d_fd = 0;

    someDir->d_buf = malloc(128);
    if (!someDir->d_buf) { // check for failed allocation before invoking _closedir()
        fprintf(stderr, "Failed to allocate memory for DIR buffer\n");
        perror("malloc");
        goto failure;
    }

    if (-1 == _closedir(someDir)) {
        fprintf(stderr, "Failed to properly close DIR\n");
        goto failure;
    }
        return EXIT_SUCCESS;
failure:
    return EXIT_FAILURE;
}

