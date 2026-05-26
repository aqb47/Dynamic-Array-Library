// Test harness
#include <stdio.h>
#include <stdlib.h>
#include "dynarray.h"

int main(void) {
    // Initialize
    DynArray test_array = da_create(10);

    int random_num = 67;
    int* random_num_ptr = &random_num;

    int second_random_num = 76;
    int* second_random_num_ptr = &second_random_num;

    for (int i = 0; i < test_array.capacity; i++) {
        int* number_ptr = malloc(sizeof(int));
        *number_ptr = i;
        
        da_push(&test_array, number_ptr);
    }

    // Use dynamic array functions
    da_insert(&test_array, 5, random_num_ptr);
    da_delete(&test_array, 1);
    da_pop(&test_array);
    da_overwrite(&test_array, 6, second_random_num_ptr);

    // Print elements
    print_da(&test_array, &print_int);
    printf("\n");

    // Free (since malloc was used)
    for (int i = 0; i < da_size(&test_array); i++) {
        free(test_array.data[i]);
    }
    da_free(&test_array);

    return 0;
}