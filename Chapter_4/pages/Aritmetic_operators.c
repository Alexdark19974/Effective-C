#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/*
    Chapter 4: Expressions and Operators
        Subchapter: Arithmetic Operators
    Page: 67
    Useful sources:
        1) https://users.cs.utah.edu/~regehr/papers/overflow12.pdf
        2) https://www.scaler.com/topics/c/overflow-and-underflow-in-c/
*/

void is_overflow(int val1, int val2, int limit, char operator)
{
    if ((operator == '+') && (val2 > 0) && (val1 > limit - val2 )) {
        fprintf(stderr, "[%s:%s:%d] overflow detected in addition operation (val1 = %d, val2 = %d). Abort\n", __FILE__, __FUNCTION__, __LINE__, val1, val2);
        abort();
    } else if ((operator == '+') && (val2 < 0) && (val1 < limit - val2)) {
        fprintf(stderr, "[%s:%s:%d] underflow detected in addition operation (val1 = %d, val2 = %d). Abort\n", __FILE__, __FUNCTION__, __LINE__, val1, val2);
        abort();
    } else if ((operator == '-') && (val2 > 0) && (val1 < limit + val2)) {
        fprintf(stderr, "[%s:%s:%d] underflow detected in subtraction operation (val1 = %d, val2 = %d). Abort\n", __FILE__, __FUNCTION__, __LINE__, val1, val2);
        abort();
    } else if ((operator == '-') && (val2 < 0) && (val1 > limit + val2)) {
        fprintf(stderr, "[%s:%s:%d] overflow detected in subtraction operation (val1 = %d, val2 = %d). Abort\n", __FILE__, __FUNCTION__, __LINE__, val1, val2);
        abort();
    } else if ((operator == '*') && (val2 > 0)) {
            if ((val1 < 0) && (val1 < limit / val2)) {
                fprintf(stderr, "[%s:%s:%d] underflow detected in multiplication operation (val1 = %d, val2 = %d). Abort\n", __FILE__, __FUNCTION__, __LINE__, val1, val2);
                abort();
            } else if (val1 > limit / val2) {
                fprintf(stderr, "[%s:%s:%d] overflow detected in multiplication operation (val1 = %d, val2 = %d). Abort\n", __FILE__, __FUNCTION__, __LINE__, val1, val2);
                abort();
            }
    } else if ((operator == '*') && (val2 < 0)) {
        if ((val1 < 0) && (val1 < limit / val2)) {
            fprintf(stderr, "[%s:%s:%d] overflow detected in multiplication operation (val1 = %d, val2 = %d). Abort\n", __FILE__, __FUNCTION__, __LINE__, val1, val2);
            abort();
        } else if ((val1 > 0) && (val1 > limit / val2)) {
            fprintf(stderr, "[%s:%s:%d] underflow detected in multiplication operation (val1 = %d, val2 = %d). Abort\n", __FILE__, __FUNCTION__, __LINE__, val1, val2);
            abort();
        }
    } else if ((operator == '/') && (val2 < 0)) {
        if (val1 < 0 && val1 == limit && val2 == -1) {
            fprintf(stderr, "[%s:%s:%d] overflow detected in division operation (val1 = %d, val2 = %d). Abort\n", __FILE__, __FUNCTION__, __LINE__, val1, val2);
            abort();
        }
    } else if ((operator == '/' || operator == '%') && (val2 == 0)) {
        fprintf(stderr, "[%s:%s:%d] Division by zero is undefined behavior (val1 = %d, val2 = %d). Abort\n", __FILE__, __FUNCTION__, __LINE__, val1, val2);
        abort();
    }
}

int Add(int val1, int val2);
int Sub(int val1, int val2);
int Mul(int val1, int val2);
int Div(int val1, int val2);
int Rem(int val1, int val2);

int main(int argc, char **argv)
{
    /*
     * binary aritmetic operators:
     * 1) addition 2 + 1;
     * 2) subtraction 2 - 1;
     * 3) multiplication: 2 * 1;
     * 4) division: 2 / 1;
     * 5) remainder: 2 % 1;
     *
     * unary arithmetic operators:
     * 1) +
     * 2) -
     * */
    char *endptr = NULL;
    int a = 0, b = 0, ret = 0, base = 0;

    if (argc < 3) {
        fprintf(stderr, "error: forgot to input 2 numbers for calculation.\n");
        exit(EXIT_FAILURE);
    }

    a = strtol(argv[1], &endptr, base);
    b = strtol(argv[2], &endptr, base);

    printf("ret after addition = %d\n", ret);

    ret = Sub(a, b);
    printf("ret after subtraction = %d\n", ret);

    ret = Mul(a, b);
    printf("ret after multiplication = %d\n", ret);

    ret = Div(a , b);
    printf("ret after division = %d\n", ret);

    ret = Rem(a, b);
    printf("ret after remainer = %d\n", ret);

    // a = -(INT_MIN); this will result in UB
    // printf("a = %d\n", a);

    a = +(INT_MIN); // safe
    printf("a = %d\n", a);

    return EXIT_SUCCESS;
}

int Add(int val1, int val2)
{
    /* check for possible integer overflow and undeflow */
    is_overflow(val1, val2, val2 > 0 ? INT_MAX : INT_MIN, '+'); 
    // obvious cases:
    // 1)  -1 + INT_MIN == undeflow; 2 negative values are summed retaining the sign -> -1 - 2147483648
    // 2) 1 + INT_MAX == overflow -> 1 + 2147483648
    return val1 + val2;
}

int Sub(int val1, int val2)
{
    /* check for possible integer overflow and underflow */
    is_overflow(val1, val2, val2 > 0 ? INT_MIN : INT_MAX, '-'); // -2 - INT_MAX == underflow; 1 - INT_MIN == overflow
    // obious cases:
    // 1) -2 - INT_MAX == underflow; -> 2 negative values are summed retaining the sign ->  -2 - 2147483647
    // 2) 1 - INT_MIN == overflow -> "- -"  generates '+' -> 1 + 2147483648
    return val1 - val2;
}

int Mul(int val1, int val2)
{

    /* check for possible integer overflow */
    is_overflow(val1, val2, val2 > 0 ? (val1 < 0 ? INT_MIN : INT_MAX) : (val1 < 0 ? INT_MAX : INT_MIN), '*'); // 2 * INT_MAX == overflow; -1  * INT_MIN == overflow
    // obious cases:
    // 1) 2 * INT_MAX == overflow
    // 2) -1 * INT_MIN == overflow
    // 3) 2 * INT_MIN == underflow
    // 4) INT_MAX * -2 = underflow
    return val1 * val2;
}

int Div(int val1, int val2)
{
    /* check for possible integer overflow */
    is_overflow(val1, val2, INT_MIN, '/');
    return val1 / val2;
}

int Rem(int val1, int val2)
{
    /* check for possible integer overflow */
    is_overflow(val1, val2, INT_MIN, '%');
    return val1 % val2;
}
