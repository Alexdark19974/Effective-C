#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <unistd.h>

/* Chapter 8: INPUT/OUTPUT
    Subchapter: Standard I/O Streams;
        1) Stream Buffering;
        2) Predefined Streams;
        3) Stream Orientation;
        4) Text and Binary Streams;
   Pages: 147 - 151 */


void streams(void);
void showcase_stdout(void);
void showcase_stdin(void);
void showcase_stderr(void);
void stream_orientation(void);
void text_binary_streams(void);

int main(void)
{
    streams();
}

void streams(void)
{
    /* A stream - is an abstraction for communicating with files, devices
       That consume or produce sequential data such as socket, keyboards, USB ports, and printers. */

    /* C standard libriaries provide API that allow users use streams to their liking.
       It also has opaque 'FILE' data type to represent streams.
       FILE data type is a structure that contains the following information:
            1) buffering information;
            2) a file descriptor;
            3) internal stream statte information;
            4) file position indicator;
            5) error and EOF indicators; */

    /* All C standard functions that deal with streams operate with FILE * object (pointer to FILE)
       As this API needs to be able to operate with a wide variety of FS and devices, they are very abstract.
       They do not handle file premissions, modes, lockings and such. */

    /* You need not allocate memory for 'FILE' object - it is done internally. */

    /* This is a crude example of what FILE struct might look like (taken from K&R book) */
    typedef struct _iobuf {
        int  cnt;       /* characters left */
        char *ptr;      /* next character position */
        char *base;     /* location of buffer */
        struct {
            uint READ:  1;
            uint WRITE: 1;
            uint UNBUF: 1;
            uint _EOF:  1;
            uint _ERR:  1;
        };
        int flag;       /* mode of file access */
        int fd;         /* file descriptor */

    } _FILE;

    /* There are 3 kinds of streams:
        1) buffered;
        2) line-buffered (usually for interactive devices);
        3) unbuffered (usually for error reporting or logging); */

     /* By default, most streams  are fully buffered.
        Whem they're fully buffered, the data will not be written to a device or file
        Until the internal buffer is full. When you open a file with fopen() 2 buffers are generally allocated:
            1) for reading;
            2) for writing;
        Until the buffer is full, the data is stored there and then written in 1 system call, saving CPU time and improving throughput
        When the stream is line-buffered, the data is stored until '\n' is met, then the data is flushed to the device or file.
        When the stream is unbuffered, the data is written to the device or file as soon as possible. */

     /* There are 3 predefined streams that are always opened when a program starts running:
       1) stdin;
       2) stdout;
       3) stderr; */

    extern FILE * stdin;    // standard input stream;
    extern FILE * stdout;   // standard output stream;
    extern FILE * stderr;   // standard error stream

    /* Generally, stdin and stdout, in their default state, are lined-buffered because
       They're attached to interactive devices (keyboard and display), otherwise they're fully buffered.
       Stderr is by default unbuffered, though. */

    showcase_stdout();
    showcase_stdin();
    showcase_stderr();
    stream_orientation();
    text_binary_streams();
}

void showcase_stdout(void)
{
#ifndef NEW_LINE
    fprintf(stdout, "Hello, World"); // it won't be immediately outout as stdin is line-buffered (there's no '\n');
    /* When the program terminates, all file descriptors are closed and buffers are flushed
       Resulting in "Hello, World" without '\n' appearing on the display. */

    /* It's worth noting that stream bufferes get flushed. kernel space buffers are a thing too.
       And fflush() doesn't always result in writing data to the device or the file (see sync()) */
#else
    fprintf(stdout, "Hello, World\n"); // will be printed before sleep() because '\n' forces the buffer to be flushed
#endif
    sleep(5);

    /* You can use redirection to make the data be output to a file or another stream
       Using left arrow (>) */

    /* echo fred > tempfile */
    /* default: echo fred > /dev/stdout */
    /* redirection to stderr: echo fred > dev/stderr */

    /* To achieve the same result using C language, explore the family of dup() functions */
}

void showcase_stdin(void)
{
    char buf[124] = {0};
    char *status = NULL;

    /* Line-buffered stdin will block until '\n' is entered */
    putchar('\n');
    status = fgets(buf, sizeof(buf), stdin);
    if (status == NULL) {
        perror("fgets");
        abort();
    }

    /* stdin may also be redirected using the right arrow '<' */

    /* echo "Hello, World" > tempfile && wc < tempfile */

    /* If the device is not interactive, stding is fully buffered
       To change the parameters of buffers, explore setbuf() */
}

void showcase_stderr(void)
{
    /* stderr is not buffered by default */
    fprintf(stderr, "This message will be printed immediately."); // write to stderr ASAP
    sleep(5);
}

void stream_orientation(void)
{
    /* There are 3 states of streams (including stdin, stdout, stderr):
       1) unoriented (when opened without I/O);
       2) byte-oriented (narrow characters);
       3) wide-oriented;(wide characters) */

    /* If no operation with the opened stream is peformed, the stream has no orientation */
    /* Narrow I/O functions and using them makes a stream byte-oriented
       Wide I/O functions and using them makes a stream wide-oridented */

    /* NEVER use wide functions for narrow character data, and vice versa.
       Doing so is undefined behavior */
    /* In general, NEVER mix wide chars with narrow chars, both in terms of object and function handling */
    /* Stream orientation can be reset by using fwide() or by reopening the file */
#ifdef WCHAR
    // wchar_t wstr[] = "Hello, World!"; // NO
    wchar_t wstr[] = L"Hello, World!"; // YES
#else
    char nstr[] = "Hello, World";
#endif
#ifdef WCHAR
    // wprintf(L"%ls\n", nstr); // NO
    // printf("%s\n", wstr); // NO
    wprintf(L"%ls\n", wstr); // YES
#else
    printf("%s\n", nstr); // YES
#endif
}

void text_binary_streams(void)
{
    /* As of now, there is really no difference between text and binary streams on Unix and POSIX-compatible systems
       As well as other systems */
    /* Conceptually, binary stream presents data as is, without conerning over such things as the conversion of newline characters ('\n' > '\r''\n' and vice versa) */
    /* For more info, explore https://www.gnu.org/software/libc/manual/html_node/Binary-Streams.html */
}

