#include "hash_code.h"
#include "item.h" // for Key type and equal() macro
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    // Integer hash example
    int i = 123;
    printf("hashInt(%d) = %d\n", i, hashCodeInt(i));

    // Double hash example
    double d = 123.456;
    printf("hashDouble(%f) = %d\n", d, hashCodeDouble(d));

    // Boolean hash example
    bool b = true;
    printf("hashBool(%s) = %d\n", b ? "true" : "false", hashCodeBool(b));

    b = false;
    printf("hashBool(%s) = %d\n", b ? "true" : "false", hashCodeBool(b));

    // String hash example using Key type
    Key key1 = "hello";
    Key key2 = "call";
    Key key3 = "hello"; // Same content as key1

    printf("hashString(\"%s\") = %d\n", key1, hashCodeString(key1));
    printf("hashString(\"%s\") = %d\n", key2, hashCodeString(key2));
    printf("hashString(\"%s\") = %d\n", key3, hashCodeString(key3));

    // Compare keys using macro from item.h
    printf("equal(\"%s\", \"%s\") = %s\n", key1, key3, equal(key1, key3) ? "true" : "false");
    printf("equal(\"%s\", \"%s\") = %s\n", key1, key2, equal(key1, key2) ? "true" : "false");

    printf("hashEqual(\"%s\", \"%s\") = %s\n", key1, key3,
           hashEqual(hashCodeString(key1), hashCodeString(key3)) ? "true" : "false");
    printf("hashEqual(\"%s\", \"%s\") = %s\n", key2, key2,
           hashEqual(hashCodeString(key2), hashCodeString(key3)) ? "true" : "false");

    int value = INT_MIN;
    printf("abs(INT_MIN): %d\n", abs(value)); // This will likely print INT_MIN due to overflow

    return 0;
}
