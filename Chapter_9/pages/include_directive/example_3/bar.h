#ifndef BAR_H // if false
#define BAR_H // define macro; next time, when BAR_H is met, it will be defined, thus the insides of the condition will be ignored

#include <stdio.h>

/* As #include directive has transitive properties, the contents of various headers can be included twice, which results in compile error */

/* To enable headers to be included only once, we use header guards.
   They prevent redeclarations and double inclusions in a resulting translation unit */

/* Use the salient parts (the path, name and its extention) of the header file from #include directive to create a macro:
   #include "bar.h" > #define BAR_H
   #include "./foo/bar.h" > #define FOO_BAR_H */

/* Do NOT use an underscore at the beginning (_FOO_H) -> such headers are reserved by the system */

/* It's always a good idea to guard headers, especially in large projects */

int func(void); // declaration of function with func identifier

#endif /* BAR_H */ // all conditional directives must be followed by #endif directive

