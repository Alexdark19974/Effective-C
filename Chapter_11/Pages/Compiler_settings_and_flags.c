#include <stdio.h>
#include <stdlib.h>

/* Chapter 11: Debugging, Testing, and Analysis
    Subchapter: Compiler Settings and Flags:
        1) Static assertions;
    Pages: 203 - 208 */

void phases_of_software_development(void);

int main(void)
{
    phases_of_software_development();
    return EXIT_SUCCESS;
}

void phases_of_software_development(void)
{
    /* When compiling code, compilers, by default, do not enable optimization,
       Thorough error checking and security hardening.
       To enable them, we need to pass flags to the compiler */

    /* For example: gcc -c program.c -o ./bin/program.o -Wall -Wextra -std=c99 -pedantic -O2 */

    /* But different flags are good for different phases of development */

    /* 1. Analysis a.k.a tring to compile your code
        Although tedious, turning on as many diagnostic messages as possible
        to eleminate bugs and defects is good practice
        Flags to turn on during analysis:
            -Wall (enables a lot of warnings but not all of them);
            -Wextra (provides for flags that -Wall lacks);
            -std=c99 (enables warnings that when your code does not conform with the standard (of your choosing);
            -pedantic (enables strict adherence to the standard you choose)
            -Werror (turns all warnings into errors; excellent to promote meticulousness and discipline);
            (you can google to see what kind of flags are there to turn on (there are many more))
            -O2 (if you want some additional flags for optimized builds)

       Also a good idea is to use static_assert() and cppcheck (static analysis)
       A rule of thumb: enable as many flags as possible at this phase,
       And modify your code to eliminate them before debugging and testing;
       This reduces testing time, makes code secure less error-prone */

    /* 2. Debugging. a.k.a my code doesn't work, produces segfaults, and behaves unexpectedly.
        This is when you should use gdb as well as severl compile flags to get as much debugging info as
        Possible:
            -Og (the code is optimized for debugging, turns off optimizations);
            -g2/3 (the compiler produces plenty of debugging information for you to analylize with gdb)
            -O0 (turns off most optimizations, although the combo of -Og and -g3 is preferred
        Aside from gdb, you can use valgrind if your code contains dynamic memory allocation
        Also, a good idea would be to enable runtime assert() to verify assumptions */

    /* 3. Testing a.k.a the program is ready, seems not to contain bugs (if it does, return to phase 2)
        But the functionality needs testing */

    /* Here are the following flags to be turned on:
        -O1/2/3 (enables code optimizations for speed/space efficiency);
        -D_FORITFY_SOURCE=2 (detect runtime buffer overflows);
       A good idea is to keep runtime assertions on
       Turn off all flags related to debugging info production (-g, -Og, etc.) */

    /* Acceptance testing / deployment a.k.a releasing production code
       Turn off all assert() both dynamic and static
       Turn off all debugging flags
       Make sure the set of flags is not different (may trigger new defects) from the one
       Used for phases 1,2, and 3. */

    /* Other useful flags to consider:
        1) -fpic (enables position independent code to disable text relocations for shared libraries);
        2) -shared (create a shared library)
        3) -Wl, (pass options to the linker, separated by a comma), -pie (enable ASLR to compile a program with position independent code);
        (-pie flag is enabled by default)
        PIE - position-independent executable (a.k.a just like shared libraries with -fpic, but the whole program's address space layout is randomized) */
i}

