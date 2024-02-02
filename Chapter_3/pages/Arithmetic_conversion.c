#include <stdio.h>
#include <limits.h>
#include <math.h>
#include <float.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include <wchar.h>

/*  
    Chapter 3: Arithmetiic Types
        Subchapter:
            1) Integer Conversion Rank;
            2) Integer Promotions;
            3) Usual Arithmetic Conversions;
            4) An example of Implicit Conversion
            5) Safe Conversions;
            6) Integer Conversions;
            7) Integer to Floating-Point Converions;
            8) Floating-Point to Integer Converions;
            9) Floating-Point Demotions;

    pages: 49 - 49
*/

/*errnot_t is an extension of C11 standard */
/*errno_t*/int do_stuff(signed long value)
{
    signed char sc = 0;

    if ((value < SCHAR_MIN) || (value > SCHAR_MAX)) {
        printf("error: signed long value (%ld) cannot"
                "be assigned to signed char c (out of range)\n", value);
        return ERANGE;
    }

    sc = (signed char) value;
    printf("sc is %d\n", sc);
    return 0;
}

void example_4(void)
{
    puts("--------------------------------------");
    printf("safe conversion example 4\n");

    if (ERANGE == do_stuff(123L))
            return;

    puts("--------------------------------------");

}

void example_5(void)
{
    signed char sc = 0;
    signed int si = 257; // 257 is 1 0 0 0 0 0 0 | (trimmed because cannot hold more than CHAR_MAX) --> 0 0 0 0 0 0 0 0 1
    float fl = 0.0f;
    double dbl = DBL_MAX;
    unsigned long long ull = ULLONG_MAX;
    puts("--------------------------------------");
    printf("implicit unsafe type demotion example 5\n");

    sc = si;
    printf("sc = %d\n", sc);

    fl = dbl;

    printf("fl = %f\n", fl);

    fl = ull;
    
    printf("ull = %llu\n", ull);
    printf("fl = %f\n", fl);

    puts("--------------------------------------");

}

void integer_conversion_rank(void)
{
    puts("\n----- integer conversion rank -----");

    // 1) No 2 signed integer types have the same rank, even if they have the same representation
    {
        long l = 15; // 8 bytes
        long long ll = 15; // 8 bytes but long long has higher rank
        printf("size of long is %zu, size of long long is %zu\n", sizeof l, sizeof ll);
    }
    // 2) The rank of a signed integer type is greater than
    //    The rank of any signed integer type with less precision
    {
        signed char c = 1;
        signed short s = 2; // rank higher than signed char
        signed int i = 3; // rank higher than short and char
    }
    /* 3) The rank of long long int is greater than the rank of long int, etc. */
    // signed char < signed short < signed int < signed long < signed long long

    // 4) The rank of any unsigned integer type equals 
    //    The rank of the corresponding singed integer type, if any
    {
        signed char c = 1;
        unsigned char uc = 1;
        /* Equal rank but the left operand will be converted to unsgined char (see conversion arithmetic) */
        printf("res = %u\n", c + uc);
    }

    // 5) the rank of char equals the rank of signed char and unsigned char
    {
        char jc = 1;
        signed char c = 1;
        unsigned char uc = 1;
    }

    // 6) The rank of _Bool is the smallest rank 
    {
        _Bool b = 1;
        char c = 5;
    }

    // 7) The rank of any enumerated type == the compatible integer type (char, signed integer or unsigned integer
    {
        enum { Mon = 1, Tue, Wed, Thu, Fri, Sat, Sun};
        char c = Mon;
        unsigned int ui = Tue;
        int i = Wed;
    }

    // 8) The rank of any extended signed integer type relative to another with the same precision
    //    Is implementation-defined.but still follow the other integer conversion rank rules.
    {
        wchar_t wc = 2;
        wint_t uwi = 2;
    }

    puts("----- integer conversion rank -----");
}

void integer_promotions(void)
{
    /* A small type is an integer with a lower conversion rank than int or unsigned int (bool, char, short) */
    /* Integer promotion is the conversion of smaller types to int or unsigned int (depending on the sign)  */

    {
        signed char cresult, c1, c2, c3;
        c1 = 100; c2 = 3; c3 = 4;
        /* By converting each char to signed int, we avoid intermediary overflow */
        cresult = c1 * c2 / c3; // the intermediate result is 300, which exceeds the precision of signed char
        printf("cresult is =%u\n", cresult);
        /* If unsigned value can be represented in a signed int, it will be converted to int 
         * Otherwise, to unsigned int (value preserving approach and part of the C standard */
        {
            signed char c4 = -6;
            unsigned char c5 = 5;
            c5 =  c4 + c5;
            printf("cresult is %u\n", c5);
        }
    }
}

void arithmetic_conversions(void)
{
    /* Arithmetic conversion are used for yelding a common type by balancing
     * Both operands of a binary operator to a common type */

    /* Conditional (?:) operator also uses arithmetic conversion to balance out 2nd and 3rd arguments */

    /* Balancing operands in terms of a common type is useful for:
     * 1) Perfomance reasons;
     * 2) Avoiding overflows; */

    /* If one of the operands is a floating-point type, then */
        /* 1) If one type of either operand is long double, the other operand is converted to long double;
         * 2) If neigther operand is long double, but either operand is double, the other is converted to double 
         * 3) If neighter operand is long double or double, but either operand is float, the other operand is cconverted to float;
         * 4) If either operand's type long / int / short / char / , but the other is of type double, the other is converted to double;
         * 5) If either operand is float, but the other is double, the other is converted to double
         * */

    /* If neither of the opernds is a floating point type, then integer promotions are performed, and then
     * 1) If both operands have the same type, no conversion is performed;
     * 2) If both operands have signed/unsigned integer type, the operand with the lesser integer conversion
     *    Rank is converted to the type of the operand with greater rank;
     * 3) If the operand that has the unsigned integer type has a rank greater than or equal to the rank of the other operand's type, the operator with the signed integer type is converted to the unsigned integer type;
     * 4) If the operator with the signed integer type can represent all of the values of the type of the operand
     * with the unsigned integer type, the latter will be converted to the signed integer type
     * 5) If none of the above applies, both operands are converted to the unsigned integer type
     * */

}

void implicit_conversion(void)
{
    puts("\n----- implicit conversion ----");

    int si = 5;
    short ss = 8;
    long sl = si; // value of si (int) is converted to the type of sl (long int) 
    unsigned short us = ss + sl; // ss is converted to long int, then the result is converted to unsigned short
    
    /* Implicit conversion (coercion) occurs in the absence of explicit type-casting */
    /* Implicit conversion follows the 3 concepts:
     * 1) integer conversion rank;
     * 2) integer promotions;
     * 3) arithmetic conversions; */

    integer_conversion_rank();
    integer_promotions();
    arithmetic_conversions();

    puts("----- implicit conversion ----");
}

void explicit_conversion(void)
{
    puts("\n----- explicit conversion ----");
    /* To preform an explicit conversion, use cast operator (*type*) */
    int si = 5;
    short ss = 8;
    long sl = (long) si; // safe since the smaller
                         // type (of the same signdness) can always be represented in the larger type
    /* the result of ss _ sl is cast to unsigned short */
    /* Keep in mind, that casting larger types to smaller types may lead to a different value */
    unsigned short us = (unsigned short) (ss + sl);

    /* Consider this example: */
    sl = USHRT_MAX; // long int can hold unsigned short precision and width
    us = (unsigned short) (sl + ss);
    /* As the resulting value cannot be represented in unsigned short, we wrap around */
    /* Keep in mind that explicit type-casting supresses compiler warnings */
    puts("----- explicit conversion ----");
}


void arithmetic_conversion(void)
{
    /* If you want a value represented in one type to be represented in another 
     * There are 2 ways to do it: 
     * 1) explicit conversion;
     * 2) implicit conversion */

    explicit_conversion();
    implicit_conversion();
}

int main(void)
{
    arithmetic_conversion();
    //example_1();

   // example_2();

   // example_3();

    //example_4();

    //example_5();

    return EXIT_SUCCESS;

}
