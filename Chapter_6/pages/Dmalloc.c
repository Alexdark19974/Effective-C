#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef DMALLOC
#include "dmalloc.h"
#endif

/* Chapter 6: Dynamically Allocated Memory
    Subchapter: Debugging Allocated Storage Problems
        1) Dmalloc;
   Pages: 115 - 116 */

void usage(char *msg) {
    fprintf(stderr, "%s", msg);
    free(msg);
    return;
}

int main(int argc, char *argv[]) {

/* dmalloc library replaces malloc, calloc, realloc, free, and other memory management features
    With routines that provide debugging facilities that you can configure at runtime  */

    if (argc != 3 && argc != 4) {
        /* error message won't be more than 80 chars */
        char *errmsg = (char *)malloc(80);
        sprintf(
            errmsg,
            "Sorry %s,\nUsage: ceasar secret_file keys_file [output_file]\n",
            getenv("USER")
                );
        usage(errmsg);
        free(errmsg); // double free vulnerability
        exit(EXIT_FAILURE);
    }
//---snip---
    exit(EXIT_SUCCESS);
}

