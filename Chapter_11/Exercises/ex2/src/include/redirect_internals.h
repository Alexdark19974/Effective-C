#ifndef REDIRECT_INTERNALS_H

#define REDIRECT_INTERNALS_H
#define STDOUT_TO_FILE '>'
#define FILE_AS_STDIN '<'
#define PIPE '|'
#define IS_REDIRECT(x) ((x) == '>' || (x) == '<')
#define IS_FILE_AS_STDIN(x) ((x) == '<')
#define IS_FILE_AS_STDOUT(x) ((x) == '>')

#endif /* REDIRECT_INTERNALS_H */
