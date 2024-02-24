#ifndef DEBUG_H
#define DEBUG_H

#ifdef DEBUG
#define DEBUG_PRINT(fmt, args...) do { fprintf(stderr, fmt , ##args); } while(0)
#define PRINT_ERR(err_func, fmt, args...) do { fprintf(stderr, (fmt), ##args); perror(#err_func); } while(0)
#else
#define DEBUG_PRINT(fmt, args...) ((void) 0)
#define PRINT_ERR(err_func, fmt, args...) ((void)0)
#endif /* DEBUG */
#endif /* DEBUG_H */

