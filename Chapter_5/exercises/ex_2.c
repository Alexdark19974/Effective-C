#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>

/* Change the find_element function from Listing 5-13 to return
 * The position of the key in a.
 * Don't forget to return an error indication if the key is not found */

size_t find_element(size_t len, char arr[len], int key) {
    size_t pos = (size_t)-1;
    printf("pos = %lu\n", pos);
    // traverse arr and search for key
    for (size_t i = 0; i < len; ++i) {
        if (arr[i] == key) {
            pos = i;
            break;  // terminate loop
            // code here will not be executed
        }
    }
    return pos; // returning pos of key in arr
}

void break_statement(void)
{
    char arr[] = "abcdefghklmnop";
    if (sizeof(arr) == ULONG_MAX) {
        fprintf(stderr, "error: len of arr cannot be %lu\n", sizeof(arr));
    }
    size_t element = find_element(sizeof(arr), arr, 'y');
    if (element == ULONG_MAX) {
        fprintf(stderr, "failed to find element in arr (%s)\n", arr);
    } else {
        fprintf(stdout, "element = %lu\n", element);
    }
}

int main(void)
{
    break_statement();

    return EXIT_SUCCESS;
}
