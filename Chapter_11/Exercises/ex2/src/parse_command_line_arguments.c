#include "common.h"
#include "debug.h"

int parse_command_line_arguments(char **argv, int argc, bool *redir_sym, int *args_num) {

    int i = 0, arg_num = 0;

    DEBUG_PRINT(stdout, "program : [%s", argv[0]);
    for (i = 1; i < argc; i++) {
        DEBUG_PRINT(stdout, " %s", argv[i]);
        if (argv[i][0] == '>' || argv[i][0] == '<' || argv[i][0] == '|')
            *redir_sym = true;
        DEBUG_PRINT(stdout, "%s", "\n");
        arg_num++;
    }
    DEBUG_PRINT(stdout, "%s\n", " ]");

    *args_num = arg_num;

    return arg_num != 0;
}
