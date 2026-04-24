#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../hash_table.h"

void test_HashTablePutGet() {
    // ToDo 
}

void test_HashTableOverwriteValue() {
    // ToDo
}

void test_HashTableManyKeys() {
    // ToDo
}

void test_HashTableCaseSensitivity() {
    // ToDo
}

void test_HashTableStressMemory() {
    // ToDo
}

void run_all_tests() {
    printf("Running tests...\n");

    // Test inserting and retrieving a single key-value pair
    test_HashTablePutGet();

    // Test inserting the same key twice with different values (should overwrite)
    test_HashTableOverwriteValue();

    // Test inserting many different keys and retrieving them
    test_HashTableManyKeys();

    // Test how the table handles case differences in keys
    test_HashTableCaseSensitivity();

    // Stress test: insert many entries and check memory and correctness
    test_HashTableStressMemory();

    printf("All tests passed!\n");
}

int main(int , char *[]) {
    run_all_tests();
    return 0;
}
