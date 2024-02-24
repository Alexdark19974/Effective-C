#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>

void convert_narrow_string_to_wide_string(void);

int main(int argc, char **argv)
// int wmain(int argc, wchar_t **wargv) // this is MICROSOFT-specific
{
    setlocale(LC_ALL, "en_US.utf8"); // set all locales to UTF-8: mandatory for proper encoding

    for (int i = 1; i < argc; i++) {
        size_t size = strlen(argv[i]) + 1;
        wchar_t output[size + 1];
        mbstowcs(output, argv[i], sizeof(output) + 1);
        wprintf(L"warg%d = %ls\n", i, output);
    }

    convert_narrow_string_to_wide_string();

   return EXIT_SUCCESS;
}

void convert_narrow_string_to_wide_string(void)
{
    char input[] = "I ♥️  cakes!";
    size_t input_size = sizeof input, ret = 0;
    wchar_t output[input_size];
 //   fwide(stdout, 1);
   ret =  mbstowcs(output, input, sizeof(output));
   if (ret == (size_t) -1) {
       fputws(L"An invalid multibyte sequence has been encountered.", stdout);
   } else {
       /* One thing to remember:
          If the output is expected to be multibyte-oriented, all output functions must be wide */
      //  printf("%zu characters converted\n", ret); // NO, then the whole output will be byte-oriented
       wprintf(L"%zu characters converted\n", ret); // YES
   }

   wprintf(L"wchar_t string = %ls\n", output);


   {
       int bytes = 0;
       char *input_p = input;
       wchar_t *output_p = output;
       while ((bytes = mbtowc(output_p, input_p, sizeof(input)))) {
           if (bytes ==  -1) {
               wprintf(L"an error occurred during the conversion.\n");
               break;
           }
           wprintf(L"bytes = %d, wchar = %lc\n", bytes, *output_p);
           output_p++;
           input_p+=bytes;
       }

       wprintf(L"[ ");

       int output_size = output_p - output + 1;

       for (int i = 0; i < output_size; i++) {
           wprintf(L"%#x ", output[i]);
       }
       wprintf(L" ]\n");

   }

   char c = 'y';
   wchar_t wc = 0;

   mbtowc(&wc, &c, sizeof(wc));

   /* All wide characters and strings must have L prefix put before the object itself
      As well as functions that do output */

   wprintf(L"wc = %lc\n", wc);

   wprintf(L"BROADCAST_ADDR = \xFF\xFF\xFF\xFF\n, %u", L'ÿ');
}

