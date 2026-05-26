#include <stdio.h>
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

// Free dynamic array. However it is up to user to free individual data of the dynamic array before using this function
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
        if (da_resize(dynarray) != 0) {
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
    if (dynarray->size < 1) return NULL;
    
    dynarray->size -= 1;

    return dynarray->data[dynarray->size];
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

// Replace element at index with item
int da_insert(DynArray* dynarray, int index, void* item) {
    int initial_size = dynarray->size;
    int initial_capacity = dynarray->capacity;

    // Check for correct usage of index
    if (index < 0 || index > initial_size) {
        return 1;
    }

    // Check if array is full
    if (initial_size == initial_capacity) {
        // If so attempt resize
        if (da_resize(dynarray) != 0) {
            return 1;
        }
    }

    // Shift items after index to right
    for (int i = initial_size; i > index; i--) {
        dynarray->data[i] = dynarray->data[i - 1];
    }

    // Add itme to index
    dynarray->data[index] = item;

    // Increment size
    dynarray->size += 1;

    return 0;
}

// Remove element at index
int da_delete(DynArray* dynarray, int index) {
    int initial_size = dynarray->size;
    
    // Check for correct usage of index
    if (index > initial_size - 1 || index < 0) {
        return 1;
    }

    // Shift items after index to left
    for (int i = index; i < initial_size - 1; i++) {
        dynarray->data[i] = dynarray->data[i + 1];
    }

    // Decrement size
    dynarray->size -= 1;

    return 0;
}

// Return size of a dynamic array
int da_size(DynArray *dynarray) {
    return dynarray->size;
}

// Print a dynamic array. Function pointer will depend on data type (i.e. print_int() for integers)
void print_da(DynArray* dynarray, void (*print_fn) (void*)) {
    int size = dynarray->size;

    for (int i = 0; i < size; i++) {
        print_fn(dynarray->data[i]);
    }
}

void print_int(void* int_ptr) {
    printf("%i ", *(int *)int_ptr);
}

void print_char(void* char_ptr) {
    printf("%c ", *(char *)char_ptr);
}

void print_float(void* float_ptr) {
    printf("%f ", *(float *)float_ptr);
}

void print_string(void* string_ptr) {
    printf("%s ", (char *)string_ptr);
}