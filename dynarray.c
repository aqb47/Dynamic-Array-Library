#include <stdlib.h>
#include "dynarray.h"

static int da_resize(DynArray* dynarray);

// Initialize dynamic array with initial capacity
DynArray da_create(int initial_capacity) {
    DynArray dynarray;
    
    // Check for correct capacity usage
    if (initial_capacity < 1) {
        initial_capacity = DEFAULT_CAPACITY;
    }

    // Allocate memory
    dynarray.data = malloc(initial_capacity * sizeof(void*));

    // If allocation goes wrong
    if (dynarray.data == NULL) {
        return ERROR_DYNARRAY;
    }

    // Initialize capacity and size
    dynarray.capacity = initial_capacity;
    dynarray.size = 0;

    return dynarray;
}

// Free dynamic array
void da_free(DynArray* dynarray) {
    free(dynarray->data);
    
    dynarray->data = NULL;
    dynarray->size = 0;
    dynarray->capacity = 0;
}

// Resize a dynamic array to twice its capacity
int da_resize(DynArray* dynarray) {
    // Temporary void pointer array that has resized memory equal to twice of previous capacity
    void** temp = realloc(dynarray->data, dynarray->capacity * 2 * sizeof(void *));

    // If allocation goes wrong we won't modify the dynamic array
    if (temp == NULL) {
        return 1;
    }
    
    // Modify the dynamic array if it goes as expected
    dynarray->data = temp;
    dynarray->capacity *= 2;

    return 0;
}

// Push item to end of dynamic array, resizing it if needed
int da_push(DynArray* dynarray, void* item) {
    int initial_size = dynarray->size;
    int initial_capacity = dynarray->capacity;

    // When array is full
    if (initial_size == initial_capacity) {
        // Attempt resize
        if (da_resize(&dynarray) != 0) {
            return 1;
        }
    }

    // Append data and increment size
    dynarray->data[initial_size] = item;
    dynarray->size += 1;

    return 0;
}

// Pop items from end of dynamic array
void* da_pop(DynArray* dynarray) {
    int initial_size = dynarray->size;

    // Decrease size by one
    if (initial_size >= 1) {
        dynarray->size -= 1;
    }
    else {
        return NULL;
    }

    // Return popped element
    return dynarray->data[initial_size - 1];
}

// Get item from dynamic array at specific index (0 - based)
void* da_get(DynArray* dynarray, int index) {
    int size = dynarray->size;

    // Check for correct usage of index
    if (index > size - 1 || index < 0) {
        return NULL;
    } 

    return dynarray->data[index];
}

// Overwrite item of dynamic array at a specific index with another item
int da_overwrite(DynArray* dynarray, int index, void* item) {
    int size = dynarray->size;

    // Check for correct usage of index
    if (index > size - 1 || index < 0) {
        return 1;
    }

    // Overwrite data at that index
    dynarray->data[index] = item;

    return 0;
}

// int da_insert(DynArray* dynarray, int index, void* item) {
//     if (index < 0 || index > dynarray->size - 1) {
//         return 1;
//     }
// }