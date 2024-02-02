#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>

/*
    Chapter 7: Character And Strings
        Subchapter: Characters;
            1) ASCII;
            2) Unicode;
            3) Source and Execution Character Sets;
    Pages: 119 - 122
*/

void characters(void);
void ASCII(void);
void Unicode(void);

int main(void)
{
    characters();
    ASCII();
    Unicode();
    return EXIT_SUCCESS;
}

void characters(void)
{
    /* Characters that people use to communicated has to be represented 
     * In sets of bits in order for machines to understand them. */

    /* To distinguish between characters and to designate characters, 
     * Machines use character encodings that assign unique code points (integer values) */

    /* There are multiple ways to encode the same character into the machine-readable code point
     * Standards that implement this are:
     * 1) ASCII;
     * 2) Extended-ASCII;
     * 2) Unicode;
     * 3) ISO 8859-1;
     * 4) Shift-JIS;
     * 5) EBCDIC; */

    /* Code unit - a set of bits to represent a character in character encoding: 7/8/16/32 bit units
     * 7 bits for US-ASCII;
     * 8 bits for UTF-8;
     * 16 bits for UTF-16;
     * 32 bits for UTF-32;
    */

    /* Code point - a sequence of code units to represent it depending on the encoding for mapping.
     * UTF-8: code points map to a sequence of one, two, three or four code units;
     * UTF-16: code points map to a sequence of one or 2 code units;
     * UTF-32: code points map to a single code unit;
     *  Char             UCP            Glyph
     * Latin A -------- U+0041 ---------- A
     * Latin C -------- U+0043 ---------- /
     * */

    /* Code space - the range of numerical values in a given coded character set 
     * the total range for valid code points is U+0000 to U+10FFFF divided in 17 planes (0 to 16) 
     * Plane 0 is Basic Multilingual Plane (BMP) which contains most commonly-used characters.
     * Its range is 0x0000 to 0xFFFF */

    /* Character set - a collection of elements used to represent text (alphabets, etc.)
     * Coded character set / code page - a set of characters  mapped to unique numbers
     * In Unix systems, the preferred term is charset or charmap
     * */
}

void ASCII(void)
{
    /* ASCII - The 7-bit American Standard Code for Information Exchange */
    /* There is a set of 128 characters and their code representation */
    /*
     * 1) 0x0 - 0x1f (31): control characters such as null, backspace, tab, etc.
     * 2) 0x20(32) - 0x7e (126): printable characters such as letters, digits, and symbols;
     * */

    /* Extended ASCII is the 8-bit character encoding, and adds up a range
     * Of 0x80 (128) - 0xFF (255)
     * What is represented in this range depends on the code page */
#ifndef WCHAR
    printf("%c\n", 0xFE); // will not be displayed. Extended ASCII is platform-dependant
#endif
    /* Most modern terminal emulators use UTF-8 Encoding, ranging from 0x0 to 0x07F (ASCII), 
     * And if it's more than that, it requires more than 1 byte (wide chars) for proper encoding, otherwise
     * A special replacement character is displayed */
}

void Unicode(void)
{
    /* Unicode is the de-facto encoding standard in computer processing */
    /* An individuial unicode value is expressed as U+ followed by four or 4> hex digits */

    /* The Unicode characters U+0000 to U+007F are indentical to those in ASCII */
    /* The range U+0000 to U+00FF is identical to ISO 8859-1 (Latin-1) */

    /* Keep in mind, that in order to properly represent characters starting from U+0080,
     * You need a wider char (wchar_t), and a specific character set that is supported by your system */
#ifdef WCHAR
    setlocale(LC_ALL, "");
    wprintf(L"%lc %u\n", 0x00A9,0x00A9 );
#else
    printf("%c\n", 0x92); // will print garbage value
#endif

    /*There are also 3 UTFs (Unicode Transformation Formats):
     * 1) UTF-8; // adopted by POSIX systems
     * 2) UTF-16; // adopted by Windows
     * 3) UTF-32; 
     * UTF-8 and UTF-16 are variable-length encodings
     * */
}
