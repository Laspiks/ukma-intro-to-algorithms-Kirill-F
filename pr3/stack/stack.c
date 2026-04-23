#include "stack_item.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 100  // Maximum word length

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    char word[MAX_STR_LEN];
    StackInit();
    printf("Stack capacity is %d\n", StackCapacity());

    while (fscanf(file, "%99s", word) == 1) {  // Read words from file
        if (strcmp(word, "-") == 0) {  // If word is "-", pop from stack
            if (!StackEmpty()) {
                char *poppedWord = StackPop();
                printf("%s ", poppedWord);
                free(poppedWord);  // Free allocated memory
            }
        } else {  // Otherwise, push the word onto the stack
            char *storedWord = strdup(word);  // Allocate memory for the word
            if (!storedWord) {
                perror("Memory allocation failed");
                fclose(file);
                return 1;
            }
            StackPush(storedWord);
        }
    }

    while(!StackEmpty()) {
        free(StackPop());
    }

    printf("\n");
    fclose(file);
    return 0;
}
