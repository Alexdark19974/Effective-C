#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <uchar.h>

/* Chapter 7: Character And Strings
    Subchapter: Strings;
        1) String Literals;
   Pages: 131 - 134
   Useful sources:
        1) https://unicode.org/faq/utf_bom.html */

void strings(void);
void narrow_strings(void);
void wide_strings(void);

int main(void)
{
    strings();

    return EXIT_SUCCESS;
}

void strings(void)
{
    /* strings are represented as character arrays
       They are a contiguous sequence of bytes including a terminating null character */

    /* There are 2 types of strings: narrow and wide */
#ifndef WCHAR
    narrow_strings();
#else
    wide_strings();
#endif
}

void narrow_strings()
{
    /* narrow strings have type char */
    char str[7] = "Hello"; // narrow string literal
    char *str_p = str /* &str[0] */; // points to the 1st element of string
    size_t size = sizeof(str); // size is the total numer of allocated bytes
    size_t len = strlen(str); // length is the number of characters until null is met

    printf("str = %s, size = %zu, len = %zu\n", str, size, len);

    /* Access beyond the last element of an array is foridden */
    /* Reading an unintialized array is a dumb idea */
    char *str_end_p = str + len + 1;
    printf("[ ");
    for (; str_p < str_end_p; str_p++) {
        printf("%#x ", *str_p);
    }
    puts(" ]");

    /* Never modify a string literal unless the memory is statically or dynamically allocated for it */
    char *string_literal_p = "Hello, World!"; // points to string allocated somewhere in memory, but not accessible to us
   // *string_literal_p = 'A'; // surefire way to segfault

    /* String literals are also used to initialize arrays */
    {
        /* String literals are also used to initialize arrays */
        #define INIT_STRING "INIT"
        /* Do NOT mess with the size of string literal - let the compiler calculate the size for you */
        char str2[] = INIT_STRING; // the size of the string will be defined at compile time.
        // char str3[4] = INIT_STRING; // unsafe since the string is not null-terminated
    }

    /* String literals can also be declared using prefixes that denote type of char */
    {
        char str[] = "string1"; // no prefix means an array of type char
        wchar_t str2[] = L"string2"; // L prefix denotes wide char
        char16_t str3[] = u"string3"; // u prefix for char16_t (C11)
        char32_t str4[] = U"string4"; // u prefix for char16_t (C11)
        char str5[] = u8"encoded"; // u8 for UTF-8 (C11)
    }
}

void wide_strings(void)
{
    /* narrow strings have type char */
    wchar_t str[7] = L"Hello"; // L denotes wide string literal
    wchar_t *str_p = str /* &str[0] */; // points to the 1st element of string
    size_t size = sizeof(str); // size is the total numer of allocated bytes
    size_t len = wcslen(str); // length is the number of characters until null is met

    /* 28 bytes in my implementation */
    wprintf(L"str = %ls, size = %zu, len = %zu\n", str, size, len);

    /* Access beyond the last element of an array is foridden */
    /* Reading an unintialized array is a dumb idea */
    wchar_t *str_end_p = str + len + 1;
    wprintf(L"[ ");
    for (; str_p < str_end_p; str_p++) {
        wprintf(L"%#x ", *str_p);
    }
    wprintf(L" ]");

}

