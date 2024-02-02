#ifndef COLLECTION_H
#define COLLECTION_H
#include "common.h"
typedef struct collection_type collection_type;
// function declarations

/* we must use pointer to typedef due to contrains of incomplete types in C (same goes for regular struct declarations)
    Directly referencing incomplete type is forbidden in C */
extern void start_collection(void);
extern int create_collection(collection_type **result);
extern void destroy_collection(collection_type *col);
extern void add_to_collection(collection_type *col, const void *data, size_t byteCount);
extern int remove_from_collection(collection_type *col, const void *data, size_t byteCount);
extern int find_in_collection(const collection_type *col, const void *data, size_t byteCount);
#endif /* COLLECTION_H */
