#include <stdio.h>
#include <stdlib.h>

void func(int arr[5]) {
    static int incr = 0;
    for (int i = 0; i < 5; i++) {
        arr[i] = ++incr;
        printf("arr[%d] = %d\n", i, incr);
    }
    printf("---------------------\n");
}

int main(int argc, char **argv)
{
    unsigned int i = 0;
    unsigned int j = 0;
    int arr[3][5];
    int *argv_int = NULL;
    printf("---------------------\n");
    for (int i = 0; i < 3; i++) {
        func(arr[i]);
    }
    printf("i = %d\n", i);
    printf("size of arr[i] = %lu\n", sizeof(*arr)); // arr[i] == *(arr + (i +sizeof(*arr))) -> pointer arithmetic
    printf("size of arr[i][j] = %lu\n", sizeof(**arr)); // arr[i][j] == *(*(arr + (i +sizeof(*arr))) + (j + sizeof(**arr))) -> pointer arithmetic
    printf("value of arr[i][j] =%i\n", *(*(arr + i) + j) /**arr*/);
    int x = arr[i][i];

    argv_int = (int *) arr[i];
    printf("argv=%p\nargv_int + 1=%p\n*argv=%d, *(argv + 1)=%d\n",  argv_int,  argv_int + 1, *argv_int, *(argv_int + 1));

    // argv_int + 1 == argv_int + (1 * sizeof(*argv_int))

    if (argc <= 1) {
        return EXIT_SUCCESS;
    }

    i = 1;

    printf("argv=%p\n argv + i=%p\n"
            "argv + i + 1=%p\n"
            "*argv=%p\n"
            "*(argv + i)=%p\n"
            "*(argv + i + 1)=%p\n",
            (void **) argv,
            (void **) argv + i,         // argv + (i * sizeof(*argv)) = 8
            (void **) argv + i + 1,     // argv + ((i + 1)  * sizeof(*argv)) = 8
            (void *) *argv,             // *argv == argv[i]
            (void *) *(argv + i),       // *(argv + (i * sizeof(*argv)))
            (void *) *(argv + i + 1));  // *(argv + ((i + 1) * sizeof(*argv)))

    return EXIT_SUCCESS;
}

