#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

/* Write a program that emulates typical shell redirection commands: < > and | */

/*Example: ./bin/prog Hello, World \> tempfile */

int redirect(int argc, char **argv, unsigned char redir_sym);
int redir_pipe(char *prog1m, char *prog2);

int main(int argc, char **argv)
{
    unsigned char redir_sym = 0;
    printf("program : [%s", argv[0]);
    for (int i = 1; i < argc; i++) {
        printf(" %s", argv[i]);
        if (argv[i][0] == '>' || argv[i][0] == '<' || argv[i][0] == '|')
            redir_sym = argv[i][0];
    }
    puts(" ]");
    if (redir_sym)
        redirect(argc -1, argv + 1, redir_sym);
    return EXIT_SUCCESS;
}

int redirect(int argc, char **argv, unsigned char redir_sym)
{
    char buf[BUFSIZ] = {0};
    char **argv_p =  argv, *dest = NULL, *buf_p = buf;
    FILE *fp = NULL;
    size_t nbytes = BUFSIZ - (buf_p- buf);
    int fd = 0;

    if (argc < 3) {
        fprintf(stderr, "too few arguments. Must be 3\n");
        return -1;
    }
    printf("nbytes =%zu\n", nbytes);

    while ((unsigned char) **argv_p != redir_sym) {
        buf_p = memccpy(buf_p, *argv_p, '\0', nbytes);
        if (buf_p == NULL) {
            perror("memccpy");
            return -1;
        }
        *(buf_p - 1) = ' ';
        nbytes-= (buf_p - buf);
        argv_p++;
        printf("buf = %s, nbytes =%zu\n", buf, nbytes);
    }
    ++argv_p;

    if (*argv_p != NULL) {
        dest = strdup(*argv_p);
        if (dest == NULL) {
           perror("strdup");
           return -1;
        }
    } else {
        fprintf(stderr, "target file or second program for pipe is not found.\n");
        return -1;
    }
    printf("buf = %s, dest = %s\n", buf, dest);

    if (redir_sym == '|') {
        if (redir_pipe(buf, dest) == -1)
            goto fail;
        goto ok;
    }

    fd = open(dest, redir_sym == '>' ? (O_CREAT | O_WRONLY | O_TRUNC) : O_RDONLY, S_IRWXU);
    if (fd == -1) {
        perror("open");
        return -1;
    }

    if (-1 == dup2(fd, redir_sym == '>' ? STDOUT_FILENO: STDIN_FILENO)) { // duplicate fd, but close newfd first: fd 1 and fd 3 are the same file descriptors
        perror("dup2");
        return -1;
    }

    fp = fdopen(fd, redir_sym == '>' ? "w" : "r"); // after creating FILE * object, don't mess with fd anymore (this is undefined behavior)
    if (fp == NULL) {
        perror("fdopen");
        return -1;
    }

    if (redir_sym == '>') {
        fputs(buf, fp);
        fputc('\n', fp);
    } else if (redir_sym == '<') {
        if (fread(buf, sizeof(*buf), sizeof(buf), fp) == 0) { // read sizeof(buf) bytes of size *buf to buf from fp
            fprintf(stderr, "read 0 bytes from %s\n", dest);
            goto fail;
        }
        if (ferror(fp)) {
            perror("fread");
            goto fail;
        }
        fputs(buf, stdout);
        if (buf[strlen(buf) - 1] != '\n')
            fputc('\n', stdout);
    }
ok:
    if (fp != NULL)
        fclose(fp);

    if (dest != NULL)
        free(dest);

    return 0;

fail:
    fclose(fp);

    if (dest != NULL)
        free(dest);
    return -1;
}

int redir_pipe(char *prog1, char *prog2)
{
    FILE *fp1 = NULL, *fp2  = NULL;
    char buf[BUFSIZ] = {0};
    int ret = 0, i = 0;

    fp1 = popen(prog1, "r"); // pipe() -> fork() -> exec()
    if (fp1 == NULL) {
        perror("popen");
        return -1;
    }

    do {
        buf[i++] = fgetc(fp1);
        if (ferror(fp1)) {
            perror("fgetc");
            goto fail1;
        } else if (feof(fp1)) {
            buf[--i] = '\0';
            break;
        }
    } while (1);

    printf("buf = %s\n", buf);

    fp2 = popen(prog2, "w");
    if (fp2 == NULL) {
        perror("popen");
        ret = -1;
        goto fail1;
    }

    fputs(buf, fp2);

    pclose(fp2);
fail1:
    pclose(fp1);
    printf("Pipe operation DONE.\n");
    return ret;
}
