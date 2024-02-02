#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>
#include <uchar.h>

/*
    Chapter 7: Character And Strings
        Subchapter: Character Conversion;
            1) C Standard Library (separate file "C_standard_library");
            2) libiconv;
            3) Win32 Conversion APIs;
    Pages: 128 - 131
    Useful sources: 
       1) https://unicode.org/faq/utf_bom.html
*/

#if __STDC_UTF_16__ != 1
#error "__STDC_UTF_16__ not defined"
#endif

void utf8_to_utf16(void);
void utf8_to_utf32(void);

int main(void)
{
    setlocale(LC_ALL, "en_US.utf8"); // set all locales to UTF-8

    utf8_to_utf16();

    utf8_to_utf32();

    return EXIT_SUCCESS;
}

void utf8_to_utf16(void)
{
    /* Some major points of contention about wchar_t:
     * 1) Its size is implementation-dependant and system-dependant (8/16/32 bits);
     * 2) The range of sizes undermines compatibility (16 bit for windows and 32 bits for Unix systems)
     * 3) Conversion functions may lead to loss of data for the aforementioned reasons; */

    char input[] = u8"I ♥️  cakes!";
    const size_t input_size = sizeof(input);
    char16_t output[input_size]; // UTF-16 requires less code units than UTF-8
    char *p_input = input;
    char *p_end = input + input_size;
    char16_t *p_output = output;
    size_t code;
    mbstate_t state = {0};

    puts("\n\n############### UTF-8 to UTF-16 ####################3");
    printf("size of input string = %zu\n", input_size); // 17 bytes
    printf("UTF-8 code units of input string: ");
    for (size_t i = 0; i < input_size; i++) {
        printf("%#x ", input[i]);
    }
    puts("");

    puts(input);
    while ((code = mbrtoc16(p_output, p_input, p_end-p_input, &state))) {
        printf("code units = %zu\n", code);
        if (code == (size_t)-1)
            break; // -1 - invalide code unit sequence detected
        else if (code == (size_t)-2)
            break; // -2 - code unit sequence missing elements
        else if (code == (size_t)-3)
            p_output++; // -3 - high surrogate from a surrogate pair
        else {
            printf("p_output = %#x, code units per symbol = %lu\n", *p_output, code);
            p_output++; // one value was written out
            p_input += code; // code is the # of code units read by functon
        }
    }

    size_t output_size = p_output - output + 1;
    printf("Converted to %zu UTF-16 code units: [ ", output_size);
    for(size_t x = 0; x < output_size; ++x) printf("%#x ", output[x]);
    puts("]");
    
}

void utf8_to_utf32(void)
{
    /* Some major points of contention about wchar_t:
     * 1) Its size is implementation-dependant and system-dependant (8/16/32 bits);
     * 2) The range of sizes undermines compatibility (16 bit for windows and 32 bits for Unix systems)
     * 3) Conversion functions may lead to loss of data for the aforementioned reasons; */

    char input[] = u8"I ♥️  cakes!";
    const size_t input_size = sizeof(input);
    char32_t output[input_size]; // UTF-16 requires less code units than UTF-8
    char *p_input = input;
    char *p_end = input + input_size;
    char32_t *p_output = output;
    size_t code;
    mbstate_t state = {0};

    puts("\n\n############### UTF-8 to UTF-32 ####################3");
    printf("size of input string = %zu\n", input_size); // 17 bytes
    printf("UTF-8 code units of input string: ");
    for (size_t i = 0; i < input_size; i++) {
        printf("%#x ", input[i]);
    }
    puts("");

    puts(input);
    while ((code = mbrtoc32(p_output, p_input, p_end-p_input, &state))) {
        printf("code units = %zu\n", code);
        if (code == (size_t)-1)
            break; // -1 - invalide code unit sequence detected
        else if (code == (size_t)-2)
            break; // -2 - code unit sequence missing elements
        else if (code == (size_t)-3)
            p_output++; // -3 - high surrogate from a surrogate pair
        else {
            printf("p_output = %#x, code units per symbol = %lu\n", *p_output, code);
            p_output++; // one value was written out
            p_input += code; // code is the # of code units read by functon
        }
    }

    size_t output_size = p_output - output + 1;
    printf("Converted to %zu UTF-32 code units: [ ", output_size);
    for(size_t x = 0; x < output_size; ++x) printf("%#x ", output[x]);
    puts("]");
    
}
