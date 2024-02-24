#include "common.h"
#include "redirect.h"
#include "parse.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "debug.h"

/* Exercise 1:
  1) Analyze the program using static and dynamic analSyses;
  2) Provide Unit testing;
  3) Debug by using different compile flags and gdb untility.
  4) Break the program down into several components,
     implementing public and private interfaces if possible

    (Write a program that can take redirect an arbitary number of
    '|' terminated by '<' or '>' or using predefined streams ".
    Support redirection of standard input/output (< and > ) operations too
    Example: echo "Hello Robert" | sed "s/Hello/Hi/" | sed "s/Robert/robot/" ) */

int main(int argc, char **argv)
{
    int wstatus = 0, status = EXIT_SUCCESS, args_num = 0;
    pid_t pid = 0;
    bool redir_sym = false;

    if (parse_command_line_arguments(argv, argc, &redir_sym, &args_num) == 0) {
        PRINT_ERR(
            parse_command_line_arguments,
            "Failed to process command line arguments. arg_num = %d\n",
            args_num
        );
        status = EXIT_FAILURE;
        goto fail;
    }
    if (redir_sym && args_num > 2)
        status = redirect(argv + 1);
    else {
        if ((pid = fork()) == -1) {
            PRINT_ERR(fork, "%s\n", "Failed to fork the process");
            status = EXIT_FAILURE;
        } else if (0 == pid) {
            if (execvp(argv[1], &argv[1]) == -1) {
                PRINT_ERR(
                    execvp,
                    "(this should never be output) Failed to launch %s\n",
                    argv[1]
                );
                status = EXIT_FAILURE;
            }
        } else {
            DEBUG_PRINT(
                "%s\n",
                "Parent is waiting for the child to return\n"
            );
            if (wait(&wstatus) == -1) {
                PRINT_ERR(
                    wait, "%s\n",
                    "Failed to wait for the child"
                );
                status = EXIT_FAILURE;
            } else
                DEBUG_PRINT(
                    "%s\n",
                    "Child returned"
                );
        }
    }
fail:
    return status;
}

