#include <stdio.h>
#include <stdlib.h>

/* Chapter 11: Debugging, Testing, and Analysis
    Subchapter: Static Analyis, Dynamic Analysis
        1) Pros and Cons of static analysis;
        2) Pros and Cons of dynamic analysis;
        3) Address Sanitizer;
    Pages: 214 - 221 */

void static_analysis(void);
void dynamic_analysis(void);

int main(void) {
    static_anlysis();
    dynamic_analysis();

    return EXIT_SUCCESS;
}

void static_analysis(void) {
    /* Static analysis implies the process of
        assessing code without executing it */

    /* Typically, we all perform static analysis when writing code
        But it can be tedious and the eye is not always capable of
        spotting inconsistencies and bugs; */

    /* That's why we use static analysis tools to spot
        potential bugs. */

    /* Unfortunately, static analysis cannot 100% determine the control
        Flow of the program, thus generating false reports or reports
        Where flaws don't exist. */

    /* 1) A false negative is a failure to report a flaw while it does exist.
        False negatives give you a false sense of security */
    /* 2) A false positive is a result that states the presence of flaws
        While they don't exist; */

    /* Static analysis tools err on the side of caution, resulting in
        reporting many false positives */

    /* When compiling your code, enable as many warnings as possible,
        And remedy the parts of your code that trigger them (warnings)

        Do not ignore them as, in doing so, you may shoot yourself in the
        Foot later on. Also, don't suppress them by typecasting or making
        some obscure changes (at least think about what triggers such
        Warnings.) */

    /* One of the best free static analyzers is cppcheck
        Also use static_assert() to diagnose statements. */
}

void dynamic_analysis(void)
{
    /* Dynamic analysis or runtime analysis is the process of
        Assessing the code during execution. */

    /* Dynamic analysis yields low a false positive rate so chances are
        You need to remedy the parts of your code marked by
        Dynamic analyzers as such. */

    /* Dynamic analysis takes place during runtime execution by injecting
        Extra instructions into the code (thus instrumenting the code) and
        Running the instrumented executable */

    /* Here are the following popular flags to enable dynamic analysis:
        -fsanitizer=address (and many more options)
        -DFORTIFY_SOURCE=2 */

    /* Here are some popular utilities to perform dynamic analysis:
        1) dmalloc (both library and utility);
        2) valgrind;
        3) Asan (address sanitizer) */

    /* As is the case with static analysis, dynamic one comes with flaws:
        1) performance overhead;
        2) bloated executables;
        3) Full code coverage is required (the-not-executed path is ignored) */
}

