#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Chapter 7: Character And Strings
    Subchapter: POSIX and Microsoft;
   Pages: 144 - 145 */

void _strdup(void);
void _strndup(void);

int main(void)
{
    _strdup();

    return EXIT_SUCCESS;
}

void _strdup(void)
{
    /* There are also 2 POSIX string-handling functions
        1) strdup - allocate space for a string and copy it there or return NULL
        2) strndup allocate n bytes of a string, and copy it there or return NULL\

        Both functions require free() after being done with them
        Both functions copy strings and null-terminate them
        Safety in exchange for malloc() and free(), which is costly. */

    const char *temp = getenv("USER");
    if (temp != NULL) {
        char *tmpvar = strdup(temp);
        if (tmpvar != NULL) {
            printf("USER = %s.\n", tmpvar);
            free(tmpvar);
        }
    }

    temp = getenv("USER");
    if (temp != NULL) {
        char *tmpvar = strndup(temp, strlen(temp) - 1); // n allows to specify how many bytes to be copied
        if (tmpvar != NULL) {
            printf("USER = %s.\n", tmpvar);
            free(tmpvar);
        }
    }
}

