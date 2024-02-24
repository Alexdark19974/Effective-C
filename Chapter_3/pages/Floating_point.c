#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <float.h>

/* Chapter 3: Arithmetiic Types
    Subchapter: Floating-point
        1) Floating-Point Types;
        2) Floating-Point Arithmetic;
        3) Floating-Point Values;
        4) Floating-Point Constants;
    Pages: 45 - 49 */

void floating_point_constants(void);
void test_for_subnormal(void);
void test_for_inf_nan_and_others(void);
void test_for_nan(void);
void test_for_infinity(void);
void test_float_precision_limits(void);
void floating_point_types(void);

int main(void)
{
    floating_point_types();
    floating_point_constants();

    return EXIT_SUCCESS;
}

void floating_point_constants(void)
{
    /* All floating points have a type. */
    /* If unsiffixed, the type is doubled (unless the value is assigned to variable of type float )
       Suffixes are:
       1) 10.0f/F; float
       2) 10.0l/ L; (long double)
       3) 10.0 double */
    puts("\n---------- test for  floating point_constants  ----------");

    float fl_val = 15.75f;
    printf("fl_val = %f\n", fl_val);

    fl_val = 1.575E1;
    printf("fl_val = %f\n", fl_val);

    fl_val = 1575e-2;
    printf("fl_val = %f\n", fl_val);

    fl_val = -2.5e-3;
    printf("fl_val = %f\n", fl_val);

    fl_val = 25E-4;
    printf("fl_val = %f\n", fl_val);

    puts("\n---------- test for  floating point_constants  ----------");

}

void test_for_subnormal(void)
{

    puts("\n---------- test for subnormal values ----------");
    switch(__fpclassify(0.11111111111111111111111111111111111110000000000000000000000000000000000000000000000001000000000000000000000000000000000000000000000001)) {
        case FP_INFINITE:
            printf("val is INFINITE\n");
            break;
        case FP_NAN:
            printf("val is NAN\n");
            break;
        case FP_NORMAL:
            printf("val is normal number\n");
            break;
        case FP_SUBNORMAL:
            printf("val is subnormal number\n");
            break;
        case FP_ZERO:
            printf("val is zero\n");
            break;
        default:
            printf("unknown value\n");
            break;
    }

    puts("---------- test for subnormal values ----------");
}

void test_float_precision_limits(void)
{
    float flt_val = FLT_MAX;
    printf("FLT_MAX = %f\n", flt_val);
    flt_val += 0.1; // more precision cannot be packed into the significand and exponent
    /* the result will be the same as flat_val depicted in the 1st printf due to the limit of precision */
    printf("FLT_MAX = %f\n", flt_val);
}

void test_for_infinity(void)
{
    float flt_val = FLT_MAX;
    double dbl_val = DBL_MAX;

    puts("\n---------- test for infinity ----------");

    printf("FLT_MAX = %f\n", flt_val);
    printf("DBL_MAX = %f\n", dbl_val);

    flt_val = dbl_val; // an overflow?

    printf("DBL_MAX assigned to float flat_val = %f\n", flt_val); // inf val

    flt_val = 123.456;

    printf(" flat_val divided by zero is %f\n", flt_val / 0.0);
    printf(" flat_val divided by negative zero is %f\n", flt_val / -0.0);

    {
        float flt_val = INFINITY;
        float flt_val2 = NAN;
        double dbl_val = HUGE_VAL;
        double dbl_val2 = -HUGE_VAL;

        printf("infinity= %f\n", flt_val);
        printf("NAN = %f\n", flt_val2);
        printf("POSITIVE HUGE_VAL(INFINITY)= %f\n", dbl_val);
        printf("NEGATIVE HUGE VAL(INFINITY) = %f\n", dbl_val2);
    }
    puts("---------- test for infinity ----------");
}

void test_for_nan(void)
{
    float flt_val = 0.0f;
    puts("\n---------- test for NaN ----------");

    printf("0.0 / 0.0 = %f\n", flt_val/0.0f);   // will produce -nan (division of floating numbers by zero) without a warning

    printf(" 0.0 / 0 = %f\n", flt_val/0);     // will produce -nan (division of zero floating numbers by zero) with a warning

    flt_val = 3.0f;
    printf(" 3.0 / 0.0 = %f\n", flt_val/0.0f);     // will produce inf (division of non-zero floating numbers by zero) with a warning

    flt_val = NAN;
    printf("flt_val is %f\n", flt_val);

    puts("---------- test for NaN ----------");
}


void test_for_inf_nan_and_others(void)
{
    float flt_val = INFINITY;
    float flt_val2 = NAN;
    double dbl_val = HUGE_VAL;
    double dbl_val2 = -HUGE_VAL;

    puts("---------- test for NaN, INFINITY, etc. ----------");

    /* __fpclassify tests for special floating-point cases */
    switch(__fpclassify(dbl_val)) {
        case FP_INFINITE:
            printf("val is INFINITE\n");
            break;
        case FP_NAN:
            printf("val is NAN\n");
            break;
        case FP_NORMAL:
            printf("val is normal number\n");
            break;
        case FP_SUBNORMAL:
            printf("val is subnormal number\n");
            break;
        case FP_ZERO:
            printf("val is zero\n");
            break;
        default:
            printf("unknown value\n");
            break;
    }

    puts("---------- test for NaN, INFINITY, etc. ----------");
}

void floating_point_types(void)
{
    /* C has 3 floating-point types: float, double, and long double */
    /* Floating-point representation is a technique used to
       To encode numbers with a base number and an exponent */

    /* 123.456 -> 1.23456 * 10^2 */

    /* float: single precision */
    /*    s       e        sig */
    /* |1 bit| |8 bits| |23 bits| */
    /* |        32 bits          |*/

    float fl = 123.456;

    /* double: double precision */
    /*    s       e        sig */
    /* |1 bit| |11 bits| |52 bits| */
    /* |        64 bits          |*/

    double dbl = 123456.7423191;

    /* The more precision is required, the more storage it takes */
    /* Float can be represented in double, double can be represented in long double */
    /* Not vice versa. */

    /* Floating-point types cannot represent all real numbers due to precision limitations */
    test_float_precision_limits();
    /* The signifcand part has to be normalized */
                /* normalized */
    /* 123.456 -> 1.23456 * 10^2 */

    /* Positive / negative Values that are close to 0 are considered subnormal
       The leading bit is 0 (for normalized numbers, 1 is the implicit leading bit of the significand */
    test_for_subnormal();

    /* floats can also represent such values as NaN (not a number), positive and negative infinity */
    test_float_precision_limits();
    test_for_infinity();
    test_for_nan();
    test_for_inf_nan_and_others();
}

