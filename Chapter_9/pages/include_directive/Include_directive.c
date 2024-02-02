#include <stdio.h>

/*
    Chapter 9: Preprocessor
        Subchapter: File Inclusion
            1) Quoted and Angle Bracket Include Strings;
    Pages: 171 - 172
*/

void include_directive(void);

int main(void)
{
    include_directive();

    return 0;
}

void include_directive(void)
{
    /* #include directive allows us to include the contents of one source file into another */

    /* Such files are called header files or headers to distinguish them from other source files (with a ".c" extention)
     * Headers typically contain declarations of various sorts for other programs to conveniently use them */

    /* For example, #include <stdio.h> is an inclusion of the contents of stdio.h 
     * Into our source files searched by the system path */

    /* #include directive has transitive properties */

    /* Also, there's a difference between #include with quoted names ("hello.h") And angle-bracketed names (<hello.h>).
     * 1) #include <hello.h>
     * Angle-bracketed headers are used by the preprocessor to find them in standard/system libraries and directories (SYSTEM PATH)
     * Where headers such as stdio.h, stdlib.h, etc. can be found 
     *
     * 2) #include "hello.h" 
     * Quoted headers are used by the processor to find them locally, possibly in the same directory with the same source files (USER path)
     *  * Quoted headers may include full path; "../../../include/header.h" or just the name("header.h").

     * In the latter case, the header should be either in the same directory as other sources files are
     * OR the path is included using "-I" flag:
     *  "gcc source.c -o source -I../../../include/header.h" */

}
