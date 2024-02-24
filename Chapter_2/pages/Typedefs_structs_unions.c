#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <stddef.h>
#include <assert.h>

/* Chapter 2: Object, Functions, and Types
    Subchapter:
        1) Type Definitions;
        2) Struct;
        3) Union;
   Pages: 28 - 30 */

typedef unsigned int uint;
typedef union sigs sigs_u; // sigs_u is an alias for union sigs

struct sigrecord {
    int signum;
    char signame[20];
    char sigdesc[100];
    void (*sig_handler)(int);
} /* sigrecord --> declaring a gloabl struct sigrecord varialbe */;

union sigs {
    struct sigrecord sigrecord;
};

static sigs_u signals[10];

void signal_handler(int sig)
{
    printf("Caught signal %d: ", sig);

    switch (sig)
    {
        case SIGINT:
            printf("SIGINT\n");
            break;
        case SIGQUIT:
            printf("SIGQUIT\n");
            break;
        case SIGCONT:
            printf("SIGCONT\n");
            return;
        default:
            break;
    }
    exit(EXIT_SUCCESS);
}

void signal_handler_quit(int sig)
{
    printf("Signal handler quit Caught signal %d: SIGQUIT\n", sig);
    exit(EXIT_SUCCESS);
}

void signal_handler_cont(int sig)
{
    printf("Signal handler quit Caught signal %d: SIGCONT\n", sig);
    exit(EXIT_SUCCESS);
}

void init_signals(void)
{
    size_t offset = 0;
    __sighandler_t ptr = NULL;

    {
        signals[0].sigrecord.signum = SIGINT;
        signals[0].sigrecord.sig_handler = signal_handler;
        strcpy(signals[0].sigrecord.signame, "SIGINT");
        strcpy(signals[0].sigrecord.sigdesc, "Interrupt from keyboard");
        ptr = signal(signals[0].sigrecord.signum, SIG_IGN/*signals[0].sigrecord.sig_handler*/);
        if (ptr == SIG_ERR)
            fprintf(stderr, "[%s:%s:%d] failed to retrieve previous signal_handler()\n", __FILE__, __FUNCTION__, __LINE__);
        else
            printf("return prev sig_handler from signal() = %p\n", ptr);
    }

    {
        signals[1].sigrecord.signum = SIGQUIT;
        signals[1].sigrecord.sig_handler = signal_handler_quit;
        strcpy(signals[1].sigrecord.signame, "SIGQUIT");
        strcpy(signals[1].sigrecord.sigdesc, "Quit the process and dump core");
        ptr = signal(signals[1].sigrecord.signum, signals[1].sigrecord.sig_handler);
        if (ptr == SIG_ERR)
            fprintf(stderr, "[%s:%s:%d] failed to retrieve previous signal_handler()\n", __FILE__, __FUNCTION__, __LINE__);
        else
            printf("return prev sig_handler from signal() = %p\n", ptr);
    }

    {
        signals[2].sigrecord.signum = SIGCONT;
        signals[2].sigrecord.sig_handler = signal_handler_cont;
        strcpy(signals[2].sigrecord.signame, "SIGCONT");
        strcpy(signals[2].sigrecord.sigdesc, "Continue the process");
        ptr = signal(signals[2].sigrecord.signum, signals[2].sigrecord.sig_handler);
        if (ptr == SIG_ERR)
            fprintf(stderr, "[%s:%s:%d] failed to retrieve previous signal_handler()\n", __FILE__, __FUNCTION__, __LINE__);
        else
            printf("return prev sig_handler from signal() = %p\n", ptr);
    }

    offset = offsetof(struct sigrecord, signame);
    printf("offset of member signame in struct sigrecord is %lu\n", offset);
}

int main(void) {

    init_signals();

    printf("sizeof signals[0] is %lu\n", sizeof(signals[0]));

    while(1) {
        puts("running...");
        sleep(2);
    }


    return EXIT_SUCCESS;
}

