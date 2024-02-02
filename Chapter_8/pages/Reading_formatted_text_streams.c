#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
    Chapter 8: INPUT/OUTPUT
        Subchapter: Reading Formatted Text Streams;
    Pages: 162 - 165
*/

int _fscanf(void);

int main(void)
{
    if ( _fscanf() == EXIT_FAILURE) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int _fscanf(void)
{
    int status = EXIT_SUCCESS;
    FILE *in;

    /* Declaring and defining struct sigrecord, one variable sigrec */
    struct sigrecord {
        int signum;
        char signame[10];
        char sigdesc[100];
    } sigrec;

    if ((in = fopen("signals.txt", "r")) == NULL) {
        fputs("Cannot open signals.txt file\n", stderr);
        return EXIT_FAILURE;
    }

    /* Write from stream in to 3 objects 
     * %d - convert into decimal number;
     * %9s - convert into string with the length of 9 
     * %*[ \t] - supress blanks and tabs, don't store; 
     * %99[^\n] - convert into string of length 99 up to, but not including, newline character */
    do {
        int n = fscanf(in, "%d%9s%*[ \t]%99[^\n]",
            &sigrec.signum, sigrec.signame, sigrec.sigdesc
        );
        if (n == 3) { // if 3 variables have been processed, success
            printf(
                "Signal\n number = %d\n name = %s\n description = %s\n\n",
                sigrec.signum, sigrec.signame, sigrec.sigdesc
            );
        }
        else if (n != EOF) { // otherwise, failure
            fputs("Failed to match signum, signame or sigdesc\n", stderr);
            status = EXIT_FAILURE;
            break;
        }
        else { // if EOF, then stop
            break;
        }
    } while(1); // loop until the end of times

    if (fclose(in) == EOF) { // if failed to close the file, return failure
        fputs("Failed to close file\n", stderr);
        status = EXIT_FAILURE;
    }
    return status;
}
