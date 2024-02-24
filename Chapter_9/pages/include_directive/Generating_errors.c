#include "./example_1/bar.h"

// option 1
#if __STDC__ && __STDC_NO_THREADS__ != 1
#include <threads.h>
#elif POSIX_THREADS == 200809L
#include <pthread.h>
#else
int compile_error[-1]; // Induce a compilation error
#endif

#if __STDC__ && __STDC_NO_THREADS__ != 1
#include <threads.h>
#elif POSIX_THREADS == 200809L
#include <pthread.h>
#else
#error Neither <threads.h> nor <pthread.h> is available
#endif

int main(void)
{

    /* Preprocessor also allows us to generate an error message if
       None of the conditions are true
       There are 2 ways to go about it:
       1) generate a compile error;
       2) use #error directive;
       To reproduce an error, simply copy and paste #error message outside of conditions */

    return 0;
}

