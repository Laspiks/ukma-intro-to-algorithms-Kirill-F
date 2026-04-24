#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <stdbool.h>
#include <stdint.h>
#include <time.h> // for Date representation

// Transaction structure
typedef struct {
    char *who;     // Name of the person
    time_t when;   // Date/Time of the transaction (using time_t for simplicity)
    double amount; // Amount of the transaction
} Transaction;

// Hash function for Transaction
hash_t hashTransaction(Transaction *t);

// Equality function for Transaction
bool equalsTransaction(Transaction *t1, Transaction *t2);

// Comparison function for Transaction (for Comparable-like behavior)
int compareTransaction(Transaction *t1, Transaction *t2);

#endif // TRANSACTION_H
