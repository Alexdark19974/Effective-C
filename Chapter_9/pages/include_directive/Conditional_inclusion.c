#include "./example_1/bar.h"

/*
    Chapter 9: Preprocessor
        Subchapter: Conditional Inclusion
            1) Generating errors (a separate file "generating errors.c");
            2) Using Header Guards;
    Pages: 172 - 175
*/

// 1)
#if defined (WIN32) // when defined (WIN32) is evaluted to nonzero, the #if branch is processed, and the rest are not
#include <win32.h>
#elif defined (ANDROID) // #elif branch is processed, if the #if branch is evaluated to 0 and defined (ANDROID) is evaluated to 1
#include <android.h>
#else // if #if and #elif conditions are false or evaluated to 0, the #else branch is processed
#include <stdlib.h>
#ifdef FOO_h // conditional directives can be nested
#include "foo.h"
#endif
#endif // the termination of conditional code inclusion

/* You cannot use a predicate condition to perform operations such as function invocation, etc. 
 * It is not the responsibility of the preprocessor. */

// 2)
/* You can write #ifdef identifier instead of #if defined identifier or #if defined(identifier) */
#ifdef FOO_BAR_H // option 1
#endif

#if defined FOO_BAR_H // option 2
#endif


#if defined (FOO_BAR_H) // option 3
#endif

// 3)
/* You can write #ifndef identifier instead of #if !defined identifier or #if !defined(identifier) */
#ifndef FOO_BAR_H // option 1
#endif

#if !defined FOO_BAR_H // option 2
#endif


#if !defined (FOO_BAR_H) // option 3
#endif

//4)
/* There is no shorthand for #elif defined identifier or #elif !defined identifier */
#if defined (FOO_BAR_H)
#elif defined (FOO_BAZ_H)
#elif !defined FOO_BAR_H && !defined (FOO_BAZ_H)
#endif

int main(void)
{
    /* Conditional inclusion allows us to include headers and define macros 
     * Or ignore them altogether depending on the result of a predicate condition 
     * A predicate condition is a combination of #if / #elif / #else and defined operator
     * Followed by #endif to determine if a macro identifier is defined, thus executing a section of code while ignoring the other. */

    return 0;
}
