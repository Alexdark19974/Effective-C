#ifndef DEBUG_H

#define DEBUG_H

extern bool debug;

#ifdef DEBUG
#define DEBUG_PRINT(stream, fmt, args...) \
        do { if (debug) fprintf((stream), (fmt), ##args); } while(0)
#else
#define DEBUG_PRINT(stream, fmt, args...) ((void) 0)
#endif /* DEBUG */
#endif /* DEBUG_H */
