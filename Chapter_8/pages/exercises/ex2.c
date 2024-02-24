#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#define STDOUT_TO_FILE '>'
#define FILE_AS_STDIN '<'
#define PIPE '|'
extern FILE *stdout;
extern FILE *stdin;
extern FILE *stderr;

#if defined DEBUG
static bool debug = true;
#else
static bool debug = false;
#endif

/* Exercise 2: Write a program that can take redirect an arbitary number of '|' terminated by '<' or '>' or using predefined streams ".
   Support redirection of standard input/output (< and > ) operations too
   Example: echo "Hello Robert" | sed "s/Hello/Hi/" | sed "s/Robert/robot/" */

#define IS_REDIRECT(x) ((x) == '>' || (x) == '<')
#define IS_FILE_AS_STDIN(x) ((x) == '<')
#define IS_FILE_AS_STDOUT(x) ((x) == '>')
#define DEBUG_PRINT(stream, fmt, args...) if (debug) fprintf((stream), (fmt), ##args)
#define PRINT_ERR(err_prog, fmt, args...) fprintf(stderr, (fmt), ##args); perror(#err_prog)
int redirect(char **argv);

int main(int argc, char **argv)
{
    int wstatus = 0, status = EXIT_SUCCESS;
    pid_t pid = 0;
    bool redir_sym = false;

    DEBUG_PRINT(stdout, "program : [%s", argv[0]);
    for (int i = 1; i < argc; i++) {
        printf(" %s", argv[i]);
        if (argv[i][0] == STDOUT_TO_FILE || argv[i][0] == FILE_AS_STDIN|| argv[i][0] == PIPE)
            redir_sym = true;
    }
    DEBUG_PRINT(stdout, " ]\n");
    if (redir_sym && argc > 2)
        status = redirect(argv + 1);
    else {
        if ((pid = fork()) == -1) {
            PRINT_ERR(fork, "Failed to fork the process\n");
            status = EXIT_FAILURE;
        } else if (0 == pid) {
            if (execvp(argv[1], &argv[1]) == -1) {
                PRINT_ERR(execvp, "(this should never be output) Failed to launch %s\n", argv[1]);
                status = EXIT_FAILURE;
            }
        } else {
            DEBUG_PRINT(stdout, "Parent is waiting for the child to return\n");
            if (wait(&wstatus) == -1) {
                PRINT_ERR(wait, "Failed to wait for the child\n");
                status = EXIT_FAILURE;
            } else
                DEBUG_PRINT(stdout, "Child returned.\n");
        }
    }
fail:
    return status;
}

int redirect(char **argv)
{
    char cmd[BUFSIZ/2] = {0};
    char readBuf[BUFSIZ] = {0};
    char **temp_argv = argv, *cmd_p = cmd + 1;
    FILE *fp1 = NULL, *fp2 = NULL;
    size_t nbytes = BUFSIZ;
    int i = 0, fd = 0, status = EXIT_SUCCESS;
    char stdinout_closed = 0;

    do {
        for (cmd_p = cmd + 1; *temp_argv && !IS_REDIRECT(**temp_argv); temp_argv++) {
            cmd_p = memccpy(cmd_p - 1, *temp_argv ,'\0', nbytes);
            if (cmd_p == NULL) {
                perror("memccpy");
                goto close_file_1;
            }
            *(cmd_p - 1) = ' ';
            cmd_p++;
            nbytes -= (cmd_p - cmd - 1);
        }
        *(cmd_p - 1) = '\0';
finally:
        if (*temp_argv == NULL || **temp_argv == '>') {

            if (fp1 == NULL && (fp1 = popen(cmd, stdinout_closed == true ? "w" : "r")) == NULL) {
                perror("popen");
                goto close_file_2;
            }
            fputs(cmd, stderr);

            if (!*readBuf) {
                size_t nbytes = fread(readBuf, 1, sizeof(readBuf), fp1);
                printf("nbytes =%zu!\n", nbytes);
            }

            if (*temp_argv == NULL) {

                fputs(cmd, stderr);
                fputs(readBuf, stdout);
                break;
            }

            temp_argv++;
            if (temp_argv == NULL) {
                fputs("missing an argument to the right of the redirection (>).\n"
                      "Dumping readBuf to stdout or to previous file if any:\n", stderr);
                fputs(readBuf, fp2 ? fp2 : stdout);
                fputs("\n", fp2 ? fp2 : stdout);
                break;
            }

            if (fp2 != NULL && fclose(fp2) == -1) {
                fp2 = NULL;
                perror("fclose");
                break;
            }
            fp2  = NULL;

            if ((fp2 = fopen(*temp_argv,"w")) == NULL) {
                fp2 = NULL;
                perror("fopen");
                fputs("Dumping to stdout.\n", stderr);
                fputs(readBuf, stdout);
                fputs("\n",  stdout);
                break;
            }

            temp_argv++;

            if (*temp_argv == NULL) {
                fputs(readBuf, fp2);
                break;
            }

        } else {
            if (fp1 == NULL  && (fp1 = popen(cmd, "w")) == NULL) {
                perror("popen");
                goto fail;
            }

            temp_argv++;

            if (*temp_argv == NULL) {
                fputs("missing an argument to the right of the redirection (<).\n" 
                        "Buffer contents will be written to the file previously opened or stdout\n", stderr);
                if (*readBuf)
                    fputs(readBuf, fp2);
                break;
            }

            if (fp2 != NULL && fclose(fp2) == -1) {
                fp2 = NULL;
                perror("fclose");
                goto close_file_1;
            }
            fp2 = NULL;
            memset(readBuf, 0, sizeof(readBuf));

            if ((fp2 = fopen(*temp_argv, "r")) == NULL) {
                perror("fopen");
                break;
            }

            size_t nbytes = fread(readBuf, 1, sizeof(readBuf), fp2);

            temp_argv++;

            if (*temp_argv == NULL) {
                fputs(readBuf, fp1);
                break;
            }

            if (**temp_argv++ == '>' && *temp_argv) {

                if (pclose(fp1) == -1) {
                    perror("pclose");
                    goto close_file_2;
                }
                fp1 = NULL;

                fprintf(stderr, "%s\n", *temp_argv);
                if (-1 == fclose(stdout)) {
                    perror("fclose");
                    break;
                }
                stdout = NULL;

                for (; *temp_argv && **temp_argv != '<' ; temp_argv++) {
                    if (fp2 != NULL && fclose(fp2) == -1) {
                        perror("fclose");
                        goto fail;
                    }

                    if ((fp2 = fopen(*temp_argv,"w")) == NULL) {
                        perror("fopen");
                        fputs("Dumping buffer contents to stderr.\n", stderr);
                        fputs(readBuf, stderr);
                        fputs("\n",  stderr);
                        goto fail;
                    }
                }
                stdout = fp2;
                stdinout_closed = true;

                if (*temp_argv) {
                    fputs("Discarding everything after \'<\'"
                            "because both stdin and stdout are busy\n",
                        stderr);
                    *temp_argv = NULL;
                }

                goto finally;
            } else {
                fputs("missing an argument to the right of the redirection (>).\n"
                        "Buffer contents will be written to stdout\n", stderr);
                fputs(readBuf, fp1);
                break;
            }
        } 
    } while(1);

close_file_1:
    if (fp1 != NULL) {
        if (-1 == pclose(fp1)) {
            perror("pclose");
        }
    }
close_file_2:
    if (fp2 != NULL) {
        if (-1 == fclose(fp2)) {
            perror("fclose");
        }
    }
fail:
    return status;
}

