#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef DMALLOC
#include "dmalloc.h"
#endif

/* Explore more features of dmalloc */

void usage(char **msg) {
    if (!msg || !*msg)
        return;
    fprintf(stderr, "%s", *msg);
    free(*msg);
    *msg = NULL;
    return;
}

int main(int argc, char *argv[]) {

    if (argc != 3 && argc != 4) {
        /* error message won't be more than 80 chars */
        char *errmsg = (char *)malloc(80);
        if (!errmsg) {
            fprintf(stderr, "Failed to allocate memory for error message!\n");
            goto failure;
        }
        sprintf(
            errmsg,
            "Sorry %s,\nUsage: ceasar secret_file keys_file [output_file]\n",
            getenv("USER")
                );
        usage(&errmsg);
        free(errmsg); // double free vulnerability remedied by modifying usage()
        exit(EXIT_FAILURE);
    }

    char *filep = malloc(128); // will be detected as unfreed pointer
//---snip---
    exit(EXIT_SUCCESS);

failure:
    exit(EXIT_FAILURE);
}

