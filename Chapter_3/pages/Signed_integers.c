#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/*  
    Chapter 3: Arithmetiic Types
        Subchapter: Signed Integers
            1) Representation;
            2) Overflow;
            3) Integer Constants;
    pages: 40 - 45
*/

void signed_integers(void);
void integer_overflow(void);
void integer_constants(void);
void integer_suffix(void);

int abs(int i) {
    return (i >= 0) ? i : -(unsigned) i; // both operands of ?: operator will be converted to unsigned int
}

int main(void)
{
    signed_integers();
    integer_overflow();
    integer_constants();
    integer_suffix();

    return EXIT_SUCCESS;
}

void integer_suffix(void)
{
    /* Aditionally append a suffix to specify the type of a constant integer */
    /*
     * U - unsigned
     * L - signed long
     * LL - signed long long
     *
     * They can be used together too.
     * */

    /* if integer constant is suffix-appended and isn't of the required type, 
     * It may be implicitly promoted */
    unsigned int ui = 71U;
    signed long int sli = 9223372036854775807U;
    unsigned long long int ull = 18446744073709551615ULL;
}

void integer_constants(void)
{
    /* Integer constans or integer literals are constants we use
     * To introduce particular integer values into a program */

    /* Integer constans are just values in their raw form: 1, 0x25, 0777, etc. */

    /* There are 3 kinds of integer constans:
     * 1) decimal constants; (starts with a non-zero digit)
     * 2) octal constants; (starts with 0)
     * 3) hexidecimal constants  (starts with 0x/0X */

    /* Decimal constants */
    unsigned int ui = 71;
    int si;
    si = -12; // typical calculations

    /* Octal constants */
    int agent = 007;
    int permissions = 0777; // convenient for permissions

    /* Hexidecimal constants */
    int burger = 0xDEADBEEF; // convenient for hex dumps and addresses
}

void signed_integers(void)
{
    /* the MSB is reserved to represent a sign */
    /* The width of a signed type lacks 1 bit so the number of values is cut in half */
    /* Which allows us to represent negative values */

    /* The most popular way of representation of signed values is 2's complement. */
    /* To turn 127 into -127, do the following:
     * 1) Take One's complement (invert all bits);
     * 2) Add 1 to the result
     * 01111111 -> 10000000 + 1 -> 10000001
     * */
    int i = 127;
    i = ~i;
    i += 1;
    printf("i = %d\n", i); // -127

    i = 0;
    i = ~i;
    /* 00000000 -> 11111111 + 1 -> 00000000 */
    printf("i = %d\n", i + 1); // 0
    
    /* The range of signed integer types is from -2^(N -1) to 2^(N - 1) - 1 */
    printf("CHAR_MIN = %u, CHAR_MAX = %u\n", CHAR_MIN, CHAR_MAX); // 10000000 - 011111111
}

void integer_overflow(void)
{
    /* Signed integer overflow occurs when the resulting value cannot be represented by the signed type */
    /* This is undefined behavior, though modern compilers might wrap around or throw an exception */

    {
        // undefined or wrong for most negative value
        #define Abs(i) ((i) < 0 ? -(1) : (i))

        signed int si = -25; // try to pass INT_MIN and you get UB
        // the most negative number of signed type cannot be converted to a postive number
        signed int abs_si = Abs(si); // undefined behavior
        printf("%d\n", abs_si); 
    }

    {
        /* integer overflow checking */
        #define AbsM(i, flag) ((i) >= 0 ? (i) : ((i) == (flag) ? (flag) : -(i)))
        signed int si = -25;
        signed int abs_si = AbsM(si, INT_MIN);
        if (abs_si == INT_MIN)
            goto recover;
        else
            printf("%d\n", abs_si);
    }

    int i = INT_MIN;
    printf("res = %d\n", abs(i));

recover:
    return;
}
