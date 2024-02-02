#ifndef INTERNAL_COLLECTION_H
#define INTERNAL_COLLECTION_H

struct node_type {
    void *data;
    size_t size;
    struct node_type *next;
};

struct list {
    size_t num_elements;
    struct node_type *head;
};

struct collection_type {
    void (*add_to_collection)(collection_type *col, const void *data, size_t byteCount);
    int (*remove_from_collection)(collection_type *col, const void *data, size_t byteCount);
    int (*find_in_collection)(const collection_type *col, const void *data, size_t byteCount);
    void (*destroy_collection)(collection_type *col);
    struct list *listp;
};
#endif /* INTERINAL_COLLECTION_H */
