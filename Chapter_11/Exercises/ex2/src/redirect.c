#include "common.h"
#include "./include/redirect_internals.h"
#include <string.h>

int redirect(char **argv)
{
    char cmd[BUFSIZ/2] = {0};
    char readBuf[BUFSIZ] = {0};
    char **temp_argv = argv, *cmd_p = cmd + 1;
    FILE *fp1 = NULL, *fp2 = NULL;
    size_t nbytes = BUFSIZ;
    int status = EXIT_SUCCESS;
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
            nbytes -= (size_t) (cmd_p - cmd - 1);
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
            if (nbytes == 0) {
                PRINT_ERR(fread, "%s", "failed to read data from fp2\n");
                break;
            }
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
