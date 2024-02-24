#ifndef DEBUG_H
#define DEBUG_H

#if defined(DEBUG)
#define PRINT_DBG_ERR(fmt, args...) do { fprintf(stderr, fmt, ##args); } while(0)
#define PRINT_DBG(fmt, args ...) do { if (debug) printf(fmt, ##args); } while(0)
#else
#define PRINT_DBG_ERR(fmt, args...) ((void)0)
#define PRINT_DBG(fmt, args...) ((void)0)
#endif

#endif /* DEBUG_H */

