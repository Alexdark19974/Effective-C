#ifndef DEBUG_H
#define DEBUG_H

extern unsigned char debug;
#define PRINT_DBG_ERR(stream, fmt, args ...) do { if (debug) fprintf(stream, fmt, ##args); } while(0)
#define PRINT_DBG(fmt, args ...) do { if (debug) printf(fmt, ##args); } while(0)

#endif /* DEBUG_H */