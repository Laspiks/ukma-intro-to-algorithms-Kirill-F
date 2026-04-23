#include "queue_v2.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
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
    QueuePtr q = QueueInit();
    while (fscanf(file, "%99s", word) == 1) {  // Read words from file
        if (strcmp(word, "-") == 0) {  // If word is "-", dequeue
            if (!QueueEmpty(q)) {
                char *poppedWord = dequeue(q);
                printf("%s ", poppedWord);
                free(poppedWord);  // Free allocated memory
            }
        } else {  // Otherwise, enqueue the word
            char *storedWord = strdup(word);  // Allocate memory for the word
            if (!storedWord) {
                perror("Memory allocation failed");
                fclose(file);
                return 1;
            }
            enqueue(q, storedWord);
        }
    }

    while(!QueueEmpty(q)) {
        free(dequeue(q));
    }
    QueueDestroy(q);
    printf("\n");
    
    QueuePtr q_char = QueueInit();
    char input;
    rewind(file); // Move the file pointer to the beginning
    while ((input = fgetc(file)) != EOF) {
        if (input == '-') {
            if (!QueueEmpty(q_char)) {
                printf("%c ", (char)(intptr_t)dequeue(q_char));
            }
        } else if (input != ' ' && input != '\n') {
            enqueue(q_char, (void *)(intptr_t)input);
        }
    }
    QueueDestroy(q_char);

    printf("\n");

    QueuePtr q_int = QueueInit();
    for (int i = 0; i < 5; ++i){
        enqueue(q_int, (void *)(intptr_t)i);
    }
    while(!QueueEmpty(q_int)) {
        printf("%d, ", (int)(intptr_t)dequeue(q_int));
    }
    QueueDestroy(q_int);


    printf("\n");
    fclose(file);
    return 0;
}
