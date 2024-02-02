#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
    Chapter 8: INPUT/OUTPUT    
        Subchapter: Reading to and Writing from Binary Streams;
    Pages: 165 - 167
*/

int _fwrite(void);
int _fread(void);
void show_case(void);

typedef struct sigrecord {
    int signum;
    char signame[10];
    char sigdesc[100];
} sigrecord;

int main(void)
{
    if (_fwrite() == EOF || _fread() == EOF) {
        return EXIT_FAILURE;
    }

    /* here's an example of how the confusion of size and nmemb could result in unexpected results */
    show_case();
    return EXIT_SUCCESS;
}

int _fwrite(void)
{
    /*fwrite( const void * restrict ptr, size_t size, size_t nmemb) 
      This Function works with binary/text streams
      It Writes nmemb of a particular size each pointed by ptr to the stream 
      Ptr is converted to an array of unsigned char */

    /* fwrite() does what fputc() does using a loop */

    int status = EXIT_SUCCESS;
    FILE *fp;
    sigrecord sigrec;

    /* Open binary stream for writing, create if necessary and truncate */
    if ((fp = fopen("signals.txt", "w")) == NULL) {
        fputs("Cannot open signals.txt file\n", stderr);
        return EXIT_FAILURE;
    }

    /* All forms of intializng struct fields are valid, the last one being an obsolete form */
    sigrecord sigrec30 = { 30, "USR1", "user-defined signal 1"};
    sigrecord sigrec31 = { 
        .signum = 31, .signame = "USR2", .sigdesc = "user-defined signal 2"
    };
    sigrecord sigrec32 = { signum: 32, signame: "FAKE", sigdesc: "fake signal" }; // valid, but produces a warning

    size_t size = sizeof(sigrecord);

    /* write 1 nmbem of size pointed by &sigrec30 to fp, return the number of nmbem written or failure */
    if (fwrite(&sigrec30, size, 1, fp) != 1) {
        fputs("Cannot write sigrec30 to signals.txt file\n", stderr);
        status = EXIT_FAILURE;
        goto close_files;
    }

    if (fwrite(&sigrec31, size, 1, fp) != 1) {
        fputs("Cannot write sigrec31 to signals.txt file\n", stderr);
        status = EXIT_FAILURE;
        goto close_files;
    }

    if (fwrite(&sigrec32, size, 1, fp) != 1) {
        fputs("Cannot write sigrec32 to signals.txt file\n", stderr);
        status = EXIT_FAILURE;
        goto close_files;
    }

close_files:
    if (fclose(fp) == EOF) { // all data written to buffer shall be flushed
        fputs("Failed to close file.\n", stderr);
        status = EXIT_FAILURE;
    }

    return status;
}

int _fread(void)
{
    FILE *fp;
    sigrecord sigrec;
    size_t size = sizeof(sigrecord);
    int status = EXIT_SUCCESS;

    /* Open binary stream for reading, fail otherwise */
    if ((fp = fopen("signals.txt", "r")) == NULL) {
        fputs("Cannot open signals.txt file\n", stderr);
        return EXIT_FAILURE;
    }

    // read the third signal
    if ((fseek(fp, size + size, SEEK_SET) != 0)) { // move to size + size bytes at the SEEK_SET offset
        fputs("fseek in signals.txt failed!\n", stderr);
        status = EXIT_FAILURE;
        goto close_files;
    }

    /* Read 1 nmemb of size to &sigrec from fp */
    if (fread(&sigrec, size, 1, fp) != 1) {
        fputs("Cannot read from signals.txt file\n", stderr);
        status = EXIT_FAILURE;
        goto close_files;
    }

    printf(
            " Pos = %ld\n Signal\n number = %d\n name = %s\n description = %s\n\n",
            ftell(fp), sigrec.signum, sigrec.signame, sigrec.sigdesc
    );

close_files:

    if (fclose(fp) == EOF) {
        fputs("Failed to close signals.txt\n", stderr);
        status = EXIT_FAILURE;
    }

    return status;
}

void show_case(void)
{
    char buf[BUFSIZ] = {0};
    FILE *fp = NULL;
    size_t nbytes = 0;

    fp = fopen("signals.txt", "rb");
    if (fp == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    /* Now let's read 1 element of size BUFSIZ */
    nbytes = fread(buf, sizeof(buf), 1, fp);

    printf("nbytes = %zu\n %s\n", nbytes, buf);

    /* 0 bytes read, nothing in the buffer, and we know for sure that the position of the indicator is at the beginning */
    /* But why 0 bytes? */
    /* Well, that's why you misunderstand the relationship of sizeand nmbem arguments */

    /* You need to decide what you want to read: 
     * BUFSIZE as 1 chunk or char as BUFISIZ chunks ?
     * In other words, 8192 as 1 chunk or 1 of 8192 small chunks
     * The latter will return the number of bytes read, the latter only if the whole chunk is present
     * see fread() manpage to get a better grasp of it.
     * */

    /* Second attempt */
    rewind(fp);

    nbytes = fread(buf, sizeof(*buf), sizeof(buf), fp);

    /* Now we have read 348 bytes but buf displays nothing. Why? */
    printf("nbytes = %zu\n buf = %s\n", nbytes, buf);

    /* Because, previously, you working with structures that have their own quirks such as padding, etc.
     * Moreover, the structures contained integers, which, in the text file, are just a number of bytes */
    /* So the data will not be fully in text-like format because it's raw data.*/

    /* By the way, endianess here matters too:
     * Imagine another machine with different endianess reading your raw file and
     * Trying to store it in the same structure...*/

    /*Let's actually read a part of buf char after char and display them */
    for (int i = 0; i < 15; i++) {
        putchar(buf[i]);
    }

    /* 
     * You should be able to see some data that is human-readable 
     * This is your char data, not paddings or the integers or anything else.
     * */

    /* By the way, the data from the 1st attempt actually was written to buf 
     * The funcitons just failed to read the whole chunk of BUFSIZ in 1 go. */
    memset(buf, 0, sizeof(buf));
    rewind(fp);

    /* read the CHUNK the size of BUFSIZ as 1 element */
    nbytes = fread(buf, sizeof(buf), 1, fp);

    printf("\nnbytes = %zu\n %s\n", nbytes, buf);

    for (int i = 0; i < 15; i++) {
        putchar(buf[i]);
    }

    /* You see? So your main fuckup was the confusion of size and nmbem in fread()/fwrite() 
     * And the attempt to store and display data saved as struct previously as an array of chars */


    /* Third attempt (the last one) */
    sigrecord sigrec;

    rewind(fp);

    if ((nbytes = fread(&sigrec, sizeof(sigrec), 1, fp)) != 1) {
        fputs("Cannot read from signals.txt file\n", stderr);
        goto close_files;
    }

    printf(
            " Pos = %ld\n nbytes = %zu\n Signal\n number = %d\n name = %s\n description = %s\n\n",
            ftell(fp), nbytes, sigrec.signum, sigrec.signame, sigrec.sigdesc
    ); // one element of sizeof(sigrec) has been successfully read and stored in sigrec
       
    /* nmbemb != size (if it's true, then we deal with bytes) */

    /* The key takeaway: think what you do, and before that, read documentation and then think again.
     * It's C language, nobody is going to come to your rescue. */

close_files:

    if (fclose(fp) == EOF) {
        perror("fclose");
        exit(EXIT_FAILURE);
    }
}
