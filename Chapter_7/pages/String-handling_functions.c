#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

/*
    Chapter 7: Character And Strings
        Subchapter: String-Handling Functions;
            1) <string.h> and <wchar.h>;
            2) Size and Length;
            3) The strcpy Function;
            4) Argument Checking;
            5) The memcpy Function;
            6) The gets Function;
            7) Annex K Bounds-Checking Interfaces: gets_s, strcpy_s;
            8) Runtime Constraints;
    Pages: 141 - 143
*/

void string_handling_functions(void);
void Strlen(void);
void Strcpy(void);
void Strcat(void);
void Memcpy(void);
void *_memcpy(void * restrict, const void *restrict , size_t);
size_t _strlen(char *);
char * _strcpy(char *, char *);
char *_strcat(char *, char *);
size_t _wcslen(wchar_t *);

int main(void)
{
    string_handling_functions();

    return EXIT_SUCCESS;
}

void string_handling_functions(void)
{
    /* All string-handling functions are declared in <string.h> and <wchar.h> */
    /* These functions are disliked by many, but if you know what you're doing 
     * Especially, if you are making sure all array bounds and sizes are taken care of,
     * Terminating null characters are added, etc.
     *
     * When creating functions like those, either check everything before entering them,
     * Or inside them before they perform their task. But not BOTH.
     *
     * Other than those points, they are very fast. */

    /* The most C-like approach is to let the caller of a function perform all checks,
     * And the callee do its job. Preforming checks on both ends is redundant affects performance */

    /* The most space-efficient approach is to let the callee validate its arguments
     * And handle possible errors. This way, the aforementioned checks are peformed in 1 place
     * Moreover, we no longer care if arguments are valid or not
     * This approach is also less time-efficient, overloads the callee functions (a lot of checks) */

    Strlen();
    Strcpy();
    Memcpy();
    Strcat();
}

void Strcat(void)
{
    /* Most strings-handling functions return a pointer to the passed argument
     * Consequently, you can use this feature to nest string functions */
    char full[128] = {0}; // assuming 128 bytes are enough
    strcat(strcat(strcat(strcat(strcpy(full, "Alexander"), " "), "Alexandrovich"), " "), "Petrov");

    printf("(strcat) full = %s\n", full);

    /* The downside of strcat(), though, is that it begins scanning from the start, which makes multiple concatenations costly */

    /* memccpy() is created to remedy unnecessary scanning 
     * Scan src until c is found, or return NULL */
    /* Copy at most n bytes of src into dest 
     * Return pointer to the element after 'c' */
    memset(full, 0, sizeof(full));

    /* This is a carbon copy of the above example, Use intermediary pointer to correctly calculate the remaning free size of string full, though.
     * See example  https://developers.redhat.com/blog/2019/08/12/efficient-string-copying-and-concatenation-in-c#attempts_to_overcome_limitations */
    memccpy(((char *)memccpy(((char *)memccpy(full, "Alexander ", '\0', sizeof(full))) - 1 , "Alexandrovich ", '\0', sizeof(full))) - 1, "Petrov", '\0', sizeof(full));
    printf("(memccpy) full = %s\n", full);

    memset(full, 0, sizeof(full));
    char *p = memccpy(full,"Hello,_World!", '_', sizeof(full) - 1);
    if (p) {
        *p = '\0';
        printf("(memccpy) string = %s\n", full);
    }

}

void Memcpy(void)
{
    char str[100] = "Here comes the sun";
    size_t size = (strlen(str) + 1) * sizeof(*str); // actual size
    char *dest = (char *) malloc(size); // +1 to account for null character, thus yielding the size
    
    if (dest) { // checking for NULL pointer before entering strcpy()
        _memcpy(dest, str, size);
        printf("memcpy-ed dest = %s\n", dest);
    }
    else {
        /* handle error */
    }

}

/* memcpy copies raw, untyped data from src to dest, which may as well be of type char (or not) */
void *_memcpy(void * restrict dest, const void *restrict src, size_t size)
{
    void *save = dest;
    while ((* (char *) dest = * (char *) src) && --size) { // dest++ && src++ when the type is void is not allowed 
        dest = (char *) dest + 1;
        src = (char *) src + 1; 
    }
    return save;
}

void Strlen(void)
{
/* strlen and wcslen count a number of code units untill a null character is met */
#ifndef WCHAR
    printf("strlen = %zu, " 
            "my strlen = %zu\n", 
            strlen("Hello"), 
            _strlen("Hello"));
    char str1[100] = "Here comes the sun";
    char *str2 = (char *) malloc(strlen(str1) + 1); // +1 to account for null character, thus yielding the size
#else
    wprintf(L"strlen = %zu, " 
            "my strlen = %zu\n", 
            wcslen(L"Hello"), 
            _wcslen(L"Hello"));
    wchar_t str1[100] = L"Here comes the sun"; // wchar_t size is implementation-defined
    wchar_t *str2 = (wchar_t *) malloc((wcslen(str1) + 1) * sizeof(wchar_t)); // 18 code units (of a wide char type) + 1 wide null multiplied by the size of wchar_t
#endif
}

/* strcpy has no error-checking mechanisms
 * (NULL pointer, no NULL character, the size of destination object, etc.)
 * And it's not its responsibility */
void Strcpy(void)
{
    char str[100] = "Here comes the sun";
    size_t str_size = strlen(str) + 1; // actual size
    char *dest = (char *) malloc(str_size); // +1 to account for null character, thus yielding the size
    
    if (dest) { // checking for NULL pointer before entering strcpy()
        _strcpy(dest, str);
    }
    else {
        /* handle error */
    }
}

char *_strcpy(char *dest, char *src)
{
    char *save = dest;
    while ((*dest++ = *src++));
    return save;
}

/* strlen doesn't check if str is NULL, nor is it its responsibility to do so.
 * The burden of parameter checking falls on the shoulders of the caller */
size_t _strlen(char *str)
{
    const char *s;

    for (s = str; *s; s++) ;

    return s - str;
}

size_t _wcslen(wchar_t *str)
{
    const wchar_t *s;

    for (s = str; *s; s++) ;

    return s - str;
}
