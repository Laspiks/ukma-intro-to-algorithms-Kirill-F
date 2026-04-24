#ifndef HASH_CODE_H
#define HASH_CODE_H

#include <stdbool.h>
#include <stdint.h>

typedef int32_t hash_t;

// Hash function for integers
hash_t hashCodeInt(hash_t value);

// Hash function for doubles (IEEE 754)
hash_t hashCodeDouble(double value);

// Hash function for booleans
hash_t hashCodeBool(bool value);

// Hash function for null-terminated strings (like Java's String.hashCode)
hash_t hashCodeString(const char *str);

// Function to compare two hash values
bool hashEqual(hash_t hash1, hash_t hash2);

#endif // HASH_CODE_H
