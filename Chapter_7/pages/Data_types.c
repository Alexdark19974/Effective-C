#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>
#include <wchar.h>

/*
    Chapter 7: Character And Strings
        Subchapter: Data types;
            1) char;
            2) int;
            3) wchar_t;
            4) char16_t and char32_t;
            5) Character Constants;
            6) Escape Sequences;
            7) Linux;
            8) Windows;
            9) Narrow vs Wide Characters;
    Pages: 122 - 131
*/

void data_types(void);
void Char(void);
void Int(void);
void Wchar_t(void);

int main(void)
{
    data_types();

    return EXIT_SUCCESS;
}

void data_types(void)
{
    /* There are a few data types to represent character data:
     * 1) char for narrow characters (not more than 8 bits per char);
     * 2) wchar_t for wide characters; (implementation-defined: signed / unsigned 16 bits or 32 bits)
     * 3) int;
     * */

    Char();
    Int();
    Wchar_t();
}

void Char(void)
{
    /* Whether char is signed or unsigned is implementation-dependent */
    /* For your code to be portable, do not assume either */
    printf("CHAR MAX is %d, CHAR MIN is %d\n", CHAR_MAX, CHAR_MIN); // it is signed char

    /* Use char type for character data, NOT for integer data 
     * char type can safely represent 7-bit character encodings, such as US-ASCII */
    /* The high-order bits are always zero,
     * So no need to concern over sign extention when promoted to type signed int */

    char c = 'A';
    printf("char = %c digit = %d\n", /*(int)*/ c, c); // char is always implicitly promoted to int

    /* char type can also be used to represent 8-bit encodings such as Extended ASCII, UTF-8, etc.
     * The caveat is that char can be signed or unsigned depending on the implementation */
    printf("c = %c\n", 254); // Extended ASCII is not a thing in my system

    /* This will generate a multibyte warning and will not yield -1
     * Unless 'L' preifix is added */

    c = L'ÿ'; // extended character
    if (c == EOF) puts("End of file"); // char is promoted to int, making it -1 (EOF)

    if (isdigit((unsigned char) c)) { // will be zero-extended to signed int
        puts("c is a digit");
    }

    /* ALWAYS cast argument to unsgined char unless EOF (see manpage on isdigit() and locale)*/
    c = -2;
    if (isdigit((unsigned char) c)) { // will be zero-extended to signed int
        puts("c is a digit");
    } else {
        puts("c is not a digit");
    }
}

void Int(void)
{
    /* Use int type for data that can either be EOF
     * Or character data interpreted as unsigned char and then converted to int */

    /* Most functions from ctype.h accept int and return int as well as many other functions concerning I/O
     * : fgetc, getc, getchar, ungetc, etc. */

    char c = 'X';

    if (isalpha((unsigned char) c)) {
        puts("c is an alphabet letter");
    } else {
        puts("c is not an alphabet letter");
    }
}

void Wchar_t(void)
{
#ifdef WIDE_CHAR
    /* The wchar_t type is an integer type to represent and process the characters
     * Of a larger character set than their narrow counterparts. */

    /*It can still be signed or unsigned as well as 16-bit or 32-bit */

    /* Implementations that don't support different locales, may define wchar_t to be the width of char type */

    wchar_t c = L'ÿ'; // L prefix to designate a wide character
    wprintf(L"size of c = %zu c = %lc\n", sizeof c, c); // 32 bits on my platform
#endif
}

