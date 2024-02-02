#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    FILE *readFp = NULL, *writeFp = NULL;
    char buf[BUFSIZ] = {0};
    int wstatus = 0;
    readFp = popen("echo \"Hello, World!\" | sed \"s/Hello/Hi/\"", "r");

    fread(buf, 1, sizeof(buf), readFp);
    printf("buf = %s\n", buf);

    pclose(readFp);

    writeFp = fopen("result.txt", "w");
    int prev_fd = stdout->_fileno;
    int fd = fileno(writeFp);
    if ((fd = dup2(fd, STDOUT_FILENO)) == -1) {
            perror("dup2");
            return EXIT_FAILURE;
    }
    stdout->_fileno = fd;

    if (fputs(buf, writeFp) == -1) {
        perror("fputs");
        return EXIT_FAILURE;
    }

    readFp = freopen("result.txt", "r+", writeFp);

    fd = fileno(readFp);
    if ((fd = dup2(fd, STDIN_FILENO)) == -1) {
            perror("dup2");
            return EXIT_FAILURE;
    }
    stdin->_fileno = fd;
    stdout->_fileno = prev_fd;

    memset(buf, 0, sizeof(buf));
    readFp = popen("wc", "r");
    fread(buf, 1, sizeof(buf), readFp);
    fprintf(stdout, "buf = %s\n", buf);
    pclose(readFp);

    return EXIT_SUCCESS;
}
