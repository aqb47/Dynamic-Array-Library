// Test harness
#include <stdio.h>
#include "dynarray.h"

int main(void) {
    DynArray test_array = da_create(10);

    for (int i = 0; i < 10; i++) {
        int number = i;
        da_push(&test_array, &number);
    }

    for (int i = 0; i < 10; i++) {
        int number = *(int *)da_get(&test_array, i);
        printf("%i\n", number);
    }

    da_free(&test_array);
}