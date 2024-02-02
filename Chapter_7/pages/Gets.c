#define __STDC_WANT_LIB_EXT1__ 1
#include <stdio.h>
#include <stdlib.h>

void get_y_or_n(void);
char *_gets(char *);
char *_gets_s(char *, size_t);

int main(void)
{
    get_y_or_n();
    return EXIT_SUCCESS;
}

void get_y_or_n(void)
{
    /* The infamous function gets() is error-prone and leads to vulnerabilities because it doesn't verify arrray bounds at all
     * You can even hack systems with it (see gets() and password vulnerabilities) */

    /* In any project, anywehere, avoid gets(). Use either gets_s() from c11, or fgets() which provides bound checking */
    char response[8] = {0};
    puts("Continue? [y] n: ");
#ifndef GETS_SAFE
    _gets(response);
    // gets(response); // will produce a warning; undefined behavior if >8 bytes are written to an array
#else
    /* This will not work because Annex K from C11 is supported by Microsoft and is not needed in Linux */
    // gets_s(response, sizeof(response));
    _gets_s(response, sizeof(response) - 1); // sizeof() - 1 to leave the last byte for null-terminator
    printf("response = %s\n", response);
#endif
    if (response[0] == 'n')
        exit(0);
    return;
}



/* Even though, C11 offers a great variety of strings-handling functions that properly check bounds and null terminate,
 * The standard is not widely adopted.
 * Moreover _s functions are poorly supported by implementations */
char *_gets(char *dest) {
    int c;
    char *p = dest;

    /* Similar to K&R get_line(), but without bound checking */
    while ((c = getchar()) != EOF && c != '\n') {
        *p++ = c;
    }
    *p = '\0';

    return dest;
}

char *_gets_s(char *dest, size_t len) {
    int c;
    char *p = dest;

    /* Similar to K&R get_line(), but without bound checking */
    while (len-- > 0 && (c = getchar()) != EOF && c != '\n') {
        *p++ = c;
    }
    *p = '\0';

    return dest;
}
