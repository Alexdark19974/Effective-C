#include <stdio.h>

/* since the exercise is loosely defined,
   I took it upon myself to use pointer to static unsigned int and
   and use pointer to function as an argument/parameter passed to retrieve function
   This way, the OG code isn't really different apart from " ptr = &counter" line
   Other (better) options:
   1) elevate static unsigned int counter to file-scope and change pass it to the function retrieve() 
   2) rewrite increment() so that it returns unsinged int
   3) mix all of the above */

typedef unsigned int uint;
static uint *ptr = NULL;

uint retrieve(void (*incr)(void))
{
    incr();
    return *ptr;
}

void increment(void)
{
    static uint counter = 0;
    counter++;
    printf("%d ", counter);
    ptr = &counter;
}

int main(void)
{
    uint ret = 0;

    for (int i = 0; i < 5; i++) {
        ret = retrieve(increment);
        printf("retrieved val from counter = %d\n", ret);
    }
    putchar('\n');
    return 0;
}

