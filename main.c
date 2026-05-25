// Test harness
#include <stdio.h>
#include <stdlib.h>
#include "dynarray.h"

int main(void) {
    // Initialize
    DynArray test_array = da_create(10);
    int random_num = 67;
    int* random_num_ptr = &random_num;

    for (int i = 0; i < 10; i++) {
        int* number_ptr = malloc(sizeof(int));
        *number_ptr = i;
        
        da_push(&test_array, number_ptr);
    }

    da_insert(&test_array, 5, random_num_ptr);
    da_delete(&test_array, 1);

    // Print elements
    for (int i = 0; i < test_array.size; i++) {
        int number = *(int *)da_get(&test_array, i);
        printf("%i\n", number);
    }

    // Free
    for (int i = 0; i < test_array.size; i++) {
        free(test_array.data[i]);
    }
    da_free(&test_array);
}