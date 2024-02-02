#include <stdio.h>
#include <stdlib.h>

/*
    Chapter 8: INPUT/OUTPUT
        Subchapter: Setting the Position in a File;
        Subchapter: Removing and Renaming Files;
        Subchapter: Using Temporary Files;
    Pages: 158 - 162
*/

void position_in_a_file(void);
void showcase_fseek_ftell(void);
void showcase_fgetpos_fsetpos(void);

int main(void) {
    position_in_a_file();
}

void position_in_a_file(void)
{
    /* C Standard libraries allow you to put the indicatior at any position in a file */
    /* To do so, and to there is a list of functions: 
     * fseek();
     * ftell();
     * rewind();
     * fgetpos();
     * fsetpos();
     * */

    /* We will deal with fseek() and ftell() first */
    showcase_fseek_ftell();
    showcase_fgetpos_fsetpos();
}

void showcase_fseek_ftell(void)
{
    puts("\n------------ fseek() ftell() -----------");
    FILE *fp = fopen("fred.txt", "w+"); // create, read and write, truncate
    long int fpos;
    if (fp == NULL) {
        perror("fopen");
        goto exit;
    }

    fputs("This is some text to showcase the capabilities of fseek() and ftell()\n", fp);

    fpos = ftell(fp); // fpos is 70
    if (fpos == -1L) {
        perror("ftell");
        goto exit;
    }
    printf("fpos = %ld\n", fpos);

    /* Now we're setting the indicator at the beginnig of the file */
    /*        FILE offset flag*/
    if (fseek(fp, 0, SEEK_SET) != 0) {
        perror("fseek");
        goto exit;
    }

    fpos = ftell(fp); // fpos is 0
    if (fpos == -1L) {
        perror("ftell");
        goto exit;
    }
    printf("fpos = %ld\n", fpos);

    /* ftell() and fseek() are limited by offset type (long int) 
     * Meaning that the offset cannot be more than LONG_MAX */

    /* Newer functions fgetpos and fsetpos remedy this */

exit:
    puts("------------ fseek() ftell() -----------");

    if (fp != NULL)
        fclose(fp);
}

void showcase_fgetpos_fsetpos(void)
{
    puts("\n------------ fetpos() fsetpos() -----------");

    FILE *fp = fopen("fred.txt", "w+");
    if (fp == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    fpos_t pos; // fpos_t is a struct

    /* fsetpos/fgetpos allow us to work with an arbitary offset of a file, with no constraints */

    /* some API never use a file position to move.
     * In this case, using offsets is the only option */

    if (fgetpos(fp, &pos) != 0) {
        perror("fgetpos");
        goto exit;
    }

    if (fputs("abcdefghijklmnopqrstuvwxyz", fp) == EOF) {
        fputs("Cannot write to fred.txt file\n", stderr);
    }

    if (fsetpos(fp, &pos) != 0) {
        perror("fsetpos");
        goto exit;
    }

    long int fpos = ftell(fp);
    if (fpos == -1L) {
        perror("ftell");
        goto exit;
    }

    printf("fpos = %ld\n", fpos);
    if (fputs("0123456789", fp) == EOF) {
        fputs("Cannot write to fred.txt file\n", stderr);
    }

    puts("------------ fetpos() fsetpos() -----------");
exit:
    if (fclose(fp) == EOF) {
        fputs("Failed to close fred.txt", stderr);
        puts("------------ fetpos() fsetpos() -----------");
        exit(EXIT_FAILURE);
    }
}
