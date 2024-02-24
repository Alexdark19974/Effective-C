#include <stdio.h>
#include <limits.h>
#include <unistd.h>

/* Chapter 3: Arithmetiic Types
    Subchapter: Integers
        1) Padding and Precision;
        2) The <limits.h> Header File;
        3) Declaring Integers (a separate file "Integer_declaration");
        4) Unsigned Integers;
        5) Representation;
        6) Wraparound;
   Pages: 36 - 40 */

void unsigned_integers(void);
void forever_loop(void);
void wraparound(void);
void too_big(void);

int main(void)
{
    unsigned_integers();
    wraparound();

    return 0;
}

void too_big(void)
{
    printf("The value is too big!\n");
}

void negative(void)
{
    printf("The value is negative\n");
}

void wraparound(void)
{
    /* Wraparound occurs when performing arithmetic operations
       That result in values that are less than 0 or more than 2^N -1
       The result of such overlow is that the value wraps around:
       To the largest value of unsigned type if less than 0 or
       To the smallest value of unsgined type if more than U_MAX */

    unsigned int ui = UINT_MAX; // 4.294.967.295 on x86
    /* Wraparound is a well-defined behavior, but more often than not,
       It is likely to be an error in your program */
    ui++; // wraps around to 0
    printf("ui = %u\n", ui); // ui is 0
    ui--; // wraps around to UINT_MAX
    printf("ui = %u\n", ui); // ui is 4.294.967.295

    forever_loop();

    /* Positive wraparound: buggy summation */
    unsigned int sum = 1;
#if 0
    if (sum + ui > UINT_MAX) // wraparound so this condition is faulty
#else
    if (ui > UINT_MAX - sum) // will never wrap around
        too_big();
#endif
    else
        sum = sum + ui; // will always be executed if condition is buggy

    /* Negative wraparound: buggy subtraction */
    unsigned int i = 0, j = 1;
#if 0
    if (i - j < 0) // cannot happen; will wraparound to UINT_MAX
#else
    if (j > i) // correct
#endif
        negative();
    else
        i = i - j;

    /* When working with unsigned integers, keeps in mind possible wraparound and bound checking */

}

void unsigned_integers(void)
{
    /* Unsigned integers contain non-negative values including zero */
    /* Their upper bound is larger than their signed counterparts */

    /* Representation */
    /* Unsigned integer types apply pure binary system:
       the LSB has the weight 2^0, then next bit is 2^1, etc.
       The value of the binary number is the sum of all the weights for the set bits */
    printf("0x%1X 0x%1X 0x%1X 0x%1X\n",
            0x0,
            0x1,    // 2^0 = 1
            0x11,   // 2^0 + 2^4 = 17
            0xFF);  // 2^0 + 2^1 + 2^2 + 2^3 + 2^4 + 2^5 + 2^6 + 2^7 == 255

    /* Unsigned integers don't have the sign bit so the precision of the value is 1 bit greater */
    /* The range of unsigned integers depends on their width which is
       2^N -1, where N - width
       For example, UINT_MAX for x86 architecture is 2^32 - 1
       The width of unsinged int is from 0 to 2^32 - 1 */
}

void forever_loop(void)
{
    unsigned int i = 10;

    /* the solution is to drop "unsigned" specifier! or add another boundary checking */
    printf("this will loop until the end of times...\n");
    /* this will loop forever because counter >= 0 is always true due to wraparound: 0 ... UINT_MAX */
    for (unsigned int counter = 10; counter >= 0 ; counter-- /* will never decrement to -1 */) {
        printf("%u...\n", counter);
        sleep(1);
    }
}

