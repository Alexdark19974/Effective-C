#include <stdio.h>

/* Chapter 9: Preprocessor
    Subchapter: Macro Definitions
        1) Macro Replacement; Generating errors (a separate file "generating errors.c");
        2) Type-Generic Macros (A separate file "type_generic_and_variadic_macros.c");
        3) Predefined Macros;
        4) Variadic Macros; (A separate file "type_generic_and_variadic_macros.c");
    Pages: 175 - 183 */

void macro_replacement(void);

int main(void)
{
    /* Macro definitions are used to define constant values or generic function-line constructs */
    /* #define directive is used to define a macro */

    /* When a macro is expanded, it is replaced by a replacement list, teminated by a newline character */
    /* Replacement list is a code pattern (or none of it) that is is inserted into the translation unit */

     /* Here's the syntax for object-like macros:
        #define identifier replacement-list */
#define ARRAY_SIZE 100 // replacement list is 100
    int array[ARRAY_SIZE];

    /* if no replacement list is specified, the preprocessor will remove the macro name (?) */
#define NOTHING

    /*Note to self: it isn't always true: it may lack replacement list, but it is still defined */
#if defined(NOTHING)
    printf("NOTHING is defined.\n");
#endif

    printf("size of array = %zu, ARRAY_SIZE = %d\n", sizeof array, ARRAY_SIZE);

    /* It is also possible to define a macro using the command line option -DARRAY_SIZE=100 */
    /* If no value is specified, 1 will be assigned: -DARRAY_SIZE=1 == #define ARRAY_SIZE = 100 */

    /* The scope and lifetime of a macro is limited by #undef identifier or the end of translation unit */

    /* Function-like macros are parameterized, the opening parenthesis of which MUST follow the macro name
     * Arguments passed to macros are NOT evaluated */

    /* Object-like macrosa are identifiers to be replaced by a code fragment */

    /* object-like macros */
#define FOO (1 + 1)
    int i = FOO;

    /* function-like macro */
#define BAR(x) (1 + (x))
    int j = BAR(10); // (1 + (10)
    int k = BAR(2 + 2); // (1 + (2 + 2))

/* Voluminous replacement lists can be easier to read if source lines are joined by '\' character */
#define cbrt(X) _Generic((X), \
        long double: cbrtl(X), \
        default: cbrt(X), \
        float: cbrtf(X) \
)
    /* This way, function-like macros are more similar to functions */

    /* When defining macro names, stick to upper-case letters;
       Because variables and functions with the same macro identifier
       Will be expanded; */
#define foo (1 + 1) // bad
#undef foo
#define FOO (1 + 1) // good

/* If you want to redefine a macro, first you need to #undef it, thus removing the macro identifier */
    int f = FOO;
#undef FOO
#define FOO "FOO" // now it's a string literal
    char *str = FOO;
    /* By the way, it is common practice to #undef a macro before definining it
       Even if it's never been defined before */
#undef MACRO
#define MACRO

    macro_replacement();
    return 0;
}

void macro_replacement(void)
{
    /* Function-like macros are similar to functions, but they differ in severl ways:
       1) Replacement list during macro expansion, treament of side effects;
       2) Behavior relative to # and ## tokens;
       3) Termination of macro definition by '\n' or expanding it by using '\' character
       4) Redefinition of a macro
       5) Treatement of ',' in macros */

    {
        /* 1. When macro is expanded, a repeated parameter name in the replacement list
           Will be replaced multiple times by the argument given in the macro invocation.
           So NEVER pass arguments with side effects to the function-like macro
           Because side-effects will take place corresponding to however many parameters
           There are in the replacement list */

#define bad_abs(x) ((x) >= 0 ? (x) : -(x))
        int i = -5;
        int ret = bad_abs(i++);

        /* In the resulting translation unit, the code will look like this:
           int ret = ((i++) >= 0 ? (i++) : -(i++))
           Make sure all side effects are resolved before invoking a function-like macro */
    }

    {
        /* 2.Any parameter preceded by a # token is replaced by a string literal passed as an argument (stringizing)
           ## token is removed, concatenating paramters preceding ## token and with the following token (token pasting) */
#define STRINGIZE(x) #x
        char *str = STRINGIZE(12);

        printf("str = %s\n", str);

#define PASTE(x, y) x ## _ ## y
        int PASTE(foo,bar) = 12;
        /* 3. You can use the backslash '\' character allow your replacement list to be on several lines and ignore terminating '\n' */
#define PRINT_ERROR(error) do { \
                                printf("%s\n", #error); \
                            }while (0);
        PRINT_ERROR(Some random error);
        /* 4. If you want to redefine a macro, first #undef it and the #define it again */
#undef PASTE
#define PASTE(x) #x
        char *str2 = PASTE(x);

        /* 5. Comma is always treated like an argument separator
           So beware when you want to do something like this: */
#define ATOMIC_VAR_INIT(value) (value)
struct S {
    int x, y;
};
        struct S zero_val = {0,0};
        // struct S val = ATOMIC_VAR_INIT({0,0}); // this will not compile
        struct S val = ATOMIC_VAR_INIT(zero_val); // this will compile;
        val = zero_val; // this is okay too
    }
    /* This happends because the preprocessor takes {1 and 2} as
       2 syntactically incorrect arguments */
}

