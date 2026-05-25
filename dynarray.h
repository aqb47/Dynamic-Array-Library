#ifndef DYNARRAY_H
#define DYNARRAY_H

#define DEFAULT_CAPACITY 1
#define ERROR_DYNARRAY (DynArray) {-1, -1, NULL}

// A pointer to a void pointer essentially implements an array of void pointers 
// size - current number of elements stored, capacity - total elements allocated
typedef struct {
    int size;
    int capacity;
    void **data;
} DynArray;

DynArray da_create(int initial_capacity);
void da_free(DynArray* dynarray);

int da_push(DynArray* dynarray, void* item);
void* da_pop(DynArray* dynarray);
void* da_get(DynArray* dynarray, int index);
int da_overwrite(DynArray* dynarray, int index, void* item);

int da_insert(DynArray* dynarray, int index, void* item);
int da_delete(DynArray* dynarray, int index);
int da_size(DynArray* dynarray);

void print_da(DynArray* dynarray, void (*print_fn) (void*));

#endif
