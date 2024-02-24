#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <limits.h>

/* Modify the function from Listing 5-11 or make it clear to the caller which file could not be opened */

typedef struct object_t {
    char str[256];
} object_t;

int do_something(void)
{
    FILE *file1, *file2;
    object_t *obj = NULL;

    int ret_val = 0;

    file1 = fopen("a_file", "w");
    if (file1 == NULL) {
        fprintf(stderr, "error: failed to open a_file; cause: %s\n", strerror(errno));
        ret_val = -1;
        goto FAIL_FILE1;
    }

    file2 = fopen("another_file", "w");
    if (file2 == NULL) {
        fprintf(stderr, "error: failed to open another_file; cause: %s\n", strerror(errno));
        ret_val = -1;
        goto FAIL_FILE2;
    }

    obj = malloc(sizeof(object_t));
    if (obj == NULL) {
        fprintf(stderr, "error: failed to mallocate memory for obj; cause: %s\n", strerror(errno));
        perror("malloc");
        ret_val = -1;
        goto FAIL_OBJ;
    }

    free(obj);

FAIL_OBJ:
    fclose(file2);
FAIL_FILE2:
    fclose(file1);
FAIL_FILE1:
    return ret_val;
}

int main(void)
{
    if (0 == do_something()) {
        fprintf(stdout, "Did something.\n");
    } else {
        fprintf(stderr, "Failed to do something.\n");
    }

    return EXIT_SUCCESS;
}

