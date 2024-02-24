#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

/* Chapter 11: Debugging, Testing, and Analysis
    Subchapter: Assertions:
        1) Static assertions;
    Pages: 199 - 202 */

void staticAssert(void);

int main(void)
{
    staticAssert();

    return 0;
}

void staticAssert(void)
{
    void Exhibit_A(void);
    void Exhibit_B(void);
    void Exhibit_C(void);
    /* Static assert allows for printing diagnostic messages at compile time
    If the predicate (the 1st argument) is false (1st argument is Boolean) */

    /* The second (argument is a string literal that will be displayed. */

    /* In order to user static assert, use macro static_assert() declared in assert.h */

    // Exhibit_A(); you need not directly invoke a function to statically assert an assumption (compile time!)
    // Exhibit_B();
    // Exhibit_C();

    /* NOTE: not only does static_assert display a diagnostic, but also terminates compilation if the predicate is false */
    /* static assertions have no impact on the efficiency of the program*/
}

#if defined(EXHIBIT_A)
void Exhibit_A(void)
{
    struct packed {
        unsigned int i;
        char *p;
    };

    static_assert(
        sizeof(struct packed) == sizeof(unsigned int) + sizeof(char *),
        "struct packed must not have any padding"
    ); // the diagonstic message will be output at compile time if the predicate is false.
}
#elif defined(EXHIBIT_B)
#include <limits.h>
void Exhibit_B(void)
{
    void clear_stdin(void);
}
void clear_stdin(void)
{
    int c;

    do {
        c = getchar();
        static_assert(UCHAR_MAX < UINT_MAX, "FIO34-C violation"); // in case unsigned char and int have the same range
    } while(c != EOF);
}
#else
void Exhibit_C(void)
{
    static const char prefix[] = "Error No: ";
    #define ARRAYSIZE 14
    char str[ARRAYSIZE];

    // Ensure that str has sufficient space to store at least one additional
    // character for an error code
    static_assert(
        sizeof(str) > sizeof(prefix),
        "str must be larget than prefix"
    );
    strcpy(str, prefix);
}
#endif

