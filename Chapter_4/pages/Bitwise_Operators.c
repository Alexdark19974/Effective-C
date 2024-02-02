#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/*
    Chapter 4: Expressions and Operators
        Subchapter: Bitwise Operators
    Page: 69
*/

void show_complement(void);
void left_right_shift(void);
void additive_expression(void);
void bitwiseAND();
void bitwiseOR();
void bitwiseXOR();

int main(void)
{
    show_complement();
    left_right_shift();
    additive_expression();
    bitwiseAND();
    bitwiseOR();
    bitwiseXOR();

    return EXIT_SUCCESS;
}

void show_complement(void)
{
    /* uc is promoted to signed int -> 0x000000FF*/
    /* take complement of uc produces 0xFFFFFF00 */

    unsigned char uc = UCHAR_MAX; // 0xFF
    int i = ~uc;

    puts("---------- show_complement ------------");

    printf("i is %d\n", i); // -256

    /* when maniputing bits, resort to unsigned types */
    uc = ~uc; // 0
    printf("uc is %u\n", uc);

    puts("---------- show_complement ------------\n");
}

void additive_expression(void)
{
    unsigned int f = 0x000000FF;
    int n = 31;

    puts("---------- additive_expression ------------");

    /* Using negative value or value equal to or greater than the type of value is UB */
    // f= f << -1;  // UB
    // f = f << 32; // UB
    f = f << n; // works fine

    printf("shift by %u of f is %u\n", n, f);

    puts("---------- additive_expression ------------\n");
}

void left_right_shift(void)
{
    unsigned int ui = 0x01;
    int i = 0x01;
    int n = 0x05;

    puts("---------- left_right_shift ------------");
    puts("1) unsigned integers:");

    /* vacated bits for left and right shifts of unsigned value are filled with 0s*/
    ui = ui >> n; // 0b00000001 -> 0b00000000

    printf("right shift by %d of unsigned ui is %u\n", n, ui);

    ui = 0x01;
    n = 0x1F;

    ui = ui << n;
    printf("left shift by %d of unsigned ui is %u\n", n, ui); // the most-significant bit set to 1, the rest to 0, which gives us 2147483648
    ui = ui << 1; // another shift by 1 bit will lead to wraparound to 0
    printf("left shift by %d of unsigned ui is %u\n", n, ui);

    puts("2) signed integers:");

    i = -0x01;

    i = i >> n; // right-shift -1 (11111111)  to 5 bits

    /* The signed bit is set to 1, so the new bits will be 1's too (according to my compiler) */
    /* Yours might actually add 0 */

    printf(" - right shift by %d of signed i is %d\n", n, i); // produces the same result (-0x01)

    /* left shift of signed negative values is undefined behavior */
    /* Avoid at all costs */
    i = i << n;
    printf(" - left shift by %d of signed i is %d (UB)\n", n, i); // produces -32 on my machine


    /* left shift of signed positive values that is more than the 2 ^N -1, is undefined behavior */
    /* Avoid at all costs */
    i = INT_MAX;

    printf("prev value of val = %i (INT_MAX)\n", i);

    i = i << 1;

    printf("left shift by 1 of signed i (INT_MAX) is %d (UB)\n", i);

    /* Conclusion:
     * 1) Right shift of unsinged variable may either be quotient of (E1 / 2^E2) or 0
     * 2) Right shift of signed non-negative value may produce zero or value of (E1 / 2^E2)
     * 3) Left shift of unsigned variable may produce either value of (E1 x 2^E2) or reduced modulo one more than the maximum representable type (wraparound - defined behavior)
     * 4) Left shift of signed varialbe may produce either value of (E1 x 2^E2) if it fits the width of the type, otherwise UB;
     * 5) Left shift of signed negative value is UB by default
     * */

    puts("---------- left_right_shift ------------\n");
}

void bitwiseAND(void)
{
    /* 0 & 1 -> 0 */
    /* 1 & 0 -> 0 */
    /* 1 & 1 -> 0 */
    /* 0 & 0 -> 0 */
    puts("---------- bitwiseAND ------------\n");

    unsigned int ui = 0x1; // 0b00000001
    unsigned int ub = 0x2; // 0b00000010
    unsigned ret = 0;

    ret = ui & ub;

    printf("ret = %u\n", ret); // 0b00000000

    puts("---------- bitwiseAND ------------\n");
}

void bitwiseOR(void)
{
    /* 0 | 1 -> 1 */
    /* 1 | 0 -> 1 */
    /* 1 | 1 -> 1 */
    /* 0 | 0 -> 0 */

    puts("---------- bitwiseOR ------------\n");

    unsigned int ui = 0x1; // 0b00000001
    unsigned int ub = 0x2; // 0b00000010
    unsigned ret = 0;

    ret = ui | ub;

    printf("ret = %u\n", ret); // 0b00000011

    puts("---------- bitwiseOR ------------\n");
}

void bitwiseXOR(void)
{
    /* 0 ^ 1 -> 1 */
    /* 1 ^ 0 -> 1 */
    /* 1 ^ 1 -> 0 */
    /* 0 ^ 0 -> 0 */

    puts("---------- bitwiseXOR ------------\n");

    unsigned int ui = 0x1; // 0b00000001
    unsigned int ub = 0x3; // 0b00000011
    unsigned ret = 0;

    ret = ui ^ ub;

    printf("ret = %u\n", ret); // 0b00000010

    puts("---------- bitwiseXOR ------------\n");
}
