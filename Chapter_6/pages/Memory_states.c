#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <errno.h>

/* 
    Chapter 6: Dynamically Allocated Memory
        Subchapter: Memory States
    Pages: 109 - 110
*/

void explain_memory_states(void);

int main(void) {
    explain_memory_states();
}

void explain_memory_states(void)
{
    /* 
        There are 3 states in which dynamically allocated memory can exist:
            1) unallocated and unitialized within the memory manager;
            2) allocated but unitialized (what malloc, realloc, and reallocarray do);
            3) allocated and initialized (what calloc() does);

    /* 
        Depending on the state of memory, there are actions you can or cannot do
    */
    
    char *p = malloc(24); // allocated but unitialized: can be written to, freed, but must not be read before initialization

    free(p);
    p = NULL;

    p = calloc(1, 24); // allocated and intialized: can be read, written to or freed

    free(p);
    p = NULL;
}
