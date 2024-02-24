#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

/* Chapter 8: INPUT/OUTPUT
    Subchapter: Opening and Creating Files;
        1)  The fopen Function; Buffering;
        2) The POSIX open Function;
    Subchapter: Closing Files;
        1) The fclose Function;
        2) The POSIX close Function;
    Subchapter:
        1) Reading and Writing Characters and Lines;
        2) Stream Flushing;
    Pages: 151 - 158 */

void open_create_close_file(void);
void f_family_funcs(void);
void posix_family_funcs(void);

int main(void)
{
    open_create_close_file();

    /* After correctly leaving the main() function, all buffers will be flushed and streams closed */
    return EXIT_SUCCESS;
}

void open_create_close_file(void)
{
    /* When you open or create a file, it's associated with a stream
     * Remember, stream is just an abstraction.
     * It is represented by FILE in C Standard API
     * And a file descriptor for POSIX API */

    /* Their API, when it comes to I/O, is different */
    f_family_funcs();
    posix_family_funcs();
}

void f_family_funcs(void)
{
    /* C Standard Library functions are as follows:
     * fopen() - fclose();
     * fdopen();
     * fflush();
     * fread() - fwrite();
     * ftell() - fseek() - frewind;
     * fgetpos() - fsetpos();
     * fprintf() - fscanf();
     * fgetc() - getc() - getchar() ;
     * fputc() - putc() - putchar()
     * fputs() - puts()
     * fgets() - gets() (gets() is dangerous)
     * Just to name a few.

     * The main focus is on fopen() and fclose()
     * */

    /* Here, we denote the name of the file as well as its mode */
    FILE *tempFp = NULL;
    FILE *fp = NULL; 
    char buf[BUFSIZ] = {0};
    size_t nbytes = 0;
    puts("\n---------- C Standard Library -----------");
    // w creates a file or truncates the existing file to zero
    // + makes it available for reading as well
    // the stream is position of the beginning of the file
    fp = fopen("./some_file", "w+"); 
    if (fp == NULL) { // if failed to open, fopen() returns NULL
        fprintf(stderr, "Failed to open some file. Oh no!\n");
        exit(EXIT_FAILURE);
    }

    fprintf(fp, "Hello, World!\n");

    /* Every fopen() must be followed by fclose() when you're done I/O'ing */
    /* This is due to the fact that opening a file allocates resources to maintain the stream
     * Consider it as awful as forgetting to free() when you called malloc() */

    /* And unwritten buffered data will be written to the file */
    /* Any unread data will be discarded */
    fclose(fp);

    fp = fopen("./some_file", "r");
    // r stands for open for reading; NULL if can't open it or the file doesn't exist

    if (fp == NULL) { // if failed to open, fopen() returns NULL
        fprintf(stderr, "Failed to open some file. Oh no!\n");
        exit(EXIT_FAILURE);
    }

    if (fgets(buf, sizeof(buf), fp) == NULL) {
        fprintf(stderr, "Failed to read some file. Oh no!\n");
        exit(EXIT_FAILURE);
    }

    fprintf(stdout, "%s", buf); // write formatted string to stdout, using argument buf

    /* Even if fclose() fails to close FILE, do NOT attempt to close it again or work with the pointer the FILE */
    /* Usually, errors coming from fclose() are ignored */
    if (fclose(fp) == EOF) { // at this point, working with fp is undefined behavior
        fprintf(stderr, "Failed to close some file. Oh no!\n");
        abort(); // this function may not close all files properly
    }

    /* There are a few modes when you open a file */
    /* r - read the file; NULL if no file; */
    /* r+ - read from AND write to file, NULL if no file */
    /* rb - read binary stream; NULL if no file */
    /* rb+ read from and write to the binary stream; NULL if no file */
    /* w - open the file or create it if no file; write to the file, truncate to zero */
    /* w+ the same as 'w' mode, but also read it */
    /* wb - open the binary stream or create it if no file; write to it, truncate to zero */
    /* wb+ - the same as "w+" but only for binary streams; */
    /* a - open and append to the existing file, or create it, the positions is at the end of file */
    /* a+ - just like 'a', but also reading (may be at the beginning); */
    /* ab - the same as 'a' but for binary streams; */
    /* ab+ the same as 'ab' but also read from the binary stream */

    /* This may seem a very versatile mode set, but POSIX open() is much more flexible */

    fp = fopen("./some_file", "a+"); // 'a+' is implementation-dependant
    if (fp == NULL) { // if failed to open, fopen() returns NULL
        fprintf(stderr, "Failed to open some file. Oh no!\n");
        exit(EXIT_FAILURE);
    }

    fputs("I am groot.\n", fp);

    fflush(fp); // flush the stream's buffer to be written to the file
    rewind(fp); // set the position of fp at the beginning of the file\

    *buf = '\0';

    /* Read sizeof(buf) of nmemb of size 1 each, write to buf */
    nbytes = fread(buf, 1, sizeof(buf), fp); // careful when working with fread and fwrite() (read on the difference between nmemb and size;
    if (ferror(fp)) {
        perror("fread");
        exit(EXIT_FAILURE);
    } else if (feof(fp)) {
        fprintf(stderr, "Read %zu bytes from some file upon reaching the end of file.\n", nbytes);
    }
    fprintf(stdout, "nbytes = %zu\n", nbytes);
    fputs(buf, stdout);


    /* If you want to change the mode of the stream, use freopen() instead of fclose() and fopen() */
    tempFp = freopen("./some_file", "r", fp);
    if (tempFp == NULL) {
        fprintf(stderr, "Failed to reopen some file.\n");
    }
    fp = tempFp;

    /* or use NULL as the first arg to only change the mode of the stream without closing the stream first */
    if (freopen(NULL, "a+", fp) == NULL) {
        fprintf(stderr, "Failed to reopen some file.\n");
    }

    fputs("I am groot too.\n", fp);

    fclose(fp);

    /* Before diving into posix functions, remeber to read on f-family funcs in manpage
     * Because every function may have features and return values, that are unique to them */

    puts("\n---------- C Standard Library -----------");
}

void posix_family_funcs(void)
{
    /* POSIX API provides us with open() and close() functions */
    FILE *fp = NULL;
    int fd = 0;
    char buf[BUFSIZ] = {0};
    ssize_t nbytes = 0;

    puts("\n------------ POSIX API ----------");

    /* Instead of returning a pointer to FILE, open() returns a file descriptor
     * A file descriptor - is a small positive number that refers to the struct describing the file */

    /* open() allows you to do what you do when using fopen(), and some.
     * int open( const char *path, int oflag, ... */

    fd = open("./some_file", O_RDWR /*|*O_CREAT , S_IRUSR | S_IWUSR | S_IXUSR*/);

    /* The second argument is oflag that deals with access mode and file status
     * Some of the flags for access mode:
     * O_RDONLY - open for reading only
     * O_WRONLY - open for writing only
     * O_RDWR - open for reading and writing
     *
     * Only one of them can be specified
     *
     *Some of the flags for flie status:
       O_APPEND - set the file position of the end of file
       O_TRUNC - truncate the length to 0
       O_CREAT - create a file

       They can be combined with access mode flag to change the behavior of an opened file
     * */

    /* The thrid argument is file permission mode (it is needed only when creating a new file.
     * Using bitwise OR (|) to get the appropirate permissions:
     * S_IRUSR, S_IWUSR, S_IXUSR
     * S_IRGRP, S_IWGRP, S_IXGRP
     * S_IROTH, S_IWOTH, S_IXOTH
     *
     * To get more info on open() and how fopen() is mapped to open(), read manpage of open and fopen
     * */

    if (-1 == fd) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    nbytes = read(fd, buf, sizeof(buf) - 1); // read sizeof(buf) -1 of bytes and write to buf, return 0 if EOF is met or a number of bytes read
    if (nbytes == -1) {
        close(fd);
        perror("read");
        exit(EXIT_FAILURE);
    }
    fprintf(stdout, "%ld bytes are read;\n %s\n", nbytes, buf);

    /* Even if close() fails, the file descriptor is still invalid */
    close(fd); // close the file, the file descriptor is invalid now

    puts("------------ POSIX API ----------");
}

