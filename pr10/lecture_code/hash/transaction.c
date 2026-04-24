#include "transaction.h"
#include "hash_code.h" // for hashString(), hashDouble()

// Calculate hash code for Transaction
hash_t hashTransaction(Transaction *t) {
    hash_t hash = 17;                        // Non-zero constant
    hash = 31 * hash + hashCodeString(t->who);    // Hash the 'who' string
    hash = 31 * hash + (hash_t)t->when;      // Hash the 'when' date (cast to hash_t)
    hash = 31 * hash + hashCodeDouble(t->amount); // Hash the 'amount' double
    return hash;
}

// Check equality between two Transactions
bool equalsTransaction(Transaction *t1, Transaction *t2) {
    if (t1 == NULL || t2 == NULL)
        return false;
    return (equal(t1->who, t2->who) && (t1->when == t2->when) && (t1->amount == t2->amount));
}

// Compare two Transactions (for sorting or Comparable-like behavior)
int compareTransaction(Transaction *t1, Transaction *t2) {
    if (t1 == NULL || t2 == NULL)
        return 0;

    int cmpWho = strcmp(t1->who, t2->who);
    if (cmpWho != 0)
        return cmpWho;

    if (t1->when < t2->when)
        return -1;
    if (t1->when > t2->when)
        return 1;

    if (t1->amount < t2->amount)
        return -1;
    if (t1->amount > t2->amount)
        return 1;

    return 0; // All fields are equal
}
