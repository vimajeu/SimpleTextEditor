//
// Created by ліна on 10.06.2026.
//

#include "input.h"

#include <stdio.h>
#include <stdlib.h>

struct ReadInput* read_input() {
    while (1) {
        int ch;
        int size = 16;
        int length = 0;
        char *buffer = malloc(size);
        while ((ch = getchar()) != '\n' && ch != EOF) {
            buffer[length++] = ch;
            if (length == size - 1) {
                size *= 2;
                char *temp = realloc(buffer, size);
                if (temp == NULL) {
                    free(buffer);
                    return NULL;
                }
                buffer = temp;
            }
        }
        if (length == 0) {
            size = 16;
            free(buffer);
            printf("String cannot be empty. Try again: ");
            continue;
        }

        buffer[length] = '\0';

        struct ReadInput* result = malloc(sizeof(struct ReadInput));
        if (result == NULL) {
            free(buffer);
            return NULL;
        }
        result->length = length;
        result->text = buffer;
        return result;
    }
}

void free_input(struct ReadInput* input) {
    if (input != NULL) {
        free(input->text);
        free(input);
    }
}
