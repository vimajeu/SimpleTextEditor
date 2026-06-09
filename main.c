#include <stdio.h>
#include <stdlib.h>
#include "buffer.h"

struct ReadInput {
    char *text;
    int length;
};

struct ReadInput* read_input() {
    int size = 16;
    int length = 0;
    char *buffer = malloc(size);

    while (1) {
        int ch;
        length = 0;
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
            printf("String cannot be empty. Try again: ");
            continue;
        }
        break;
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

void free_input(struct ReadInput* input) {
    if (input != NULL) {
        free(input->text);
        free(input);
    }
}

int main() {
    int line;
    int index;

    while (1) {
        int command;
        printf("Hello! It's Simple Text Editor!\n");
        printf("1. Append text symbols to the end\n");
        printf("2. Start the new line\n");
        printf("3. Save information to the file\n");
        printf("4. Load information from the file\n");
        printf("5. Print the current text to console\n");
        printf("6. Insert the text by line and symbol index\n");
        printf("7. Search for words/characters\n");
        printf("Choose a command: ");

        scanf("%d", &command);

        while (getchar() != '\n');

        switch (command) {
            case 1:
                printf("Enter text to append: ");
                struct ReadInput* input = read_input();
                buffer_append(input->text);
                free_input(input);
                printf("Appended successfully!\n");
                break;

            case 2:
                new_line();
                printf("New line started successfully!\n");
                break;

            case 3:
                printf("Enter the file name for saving: ");
                struct ReadInput* filename = read_input();
                save_to_file(filename->text);
                free_input(filename);
                printf("Saved successfully!\n");
                break;

            case 4:
                printf("Enter the file name for loading: ");
                struct ReadInput* filename2 = read_input();
                load_from_file(filename2->text);
                free_input(filename2);
                break;

            case 5:
                print_current();
                break;

            case 6:
                printf("Enter text to insert: ");
                struct ReadInput* insert = read_input();

                printf("Enter line number: ");
                scanf("%d", &line);
                printf("Enter index: ");
                scanf("%d", &index);

                while (getchar() != '\n');

                insert_text(insert->text, line, index);
                free_input(insert);
                break;

            case 7:
                printf("Enter string to find: ");
                struct ReadInput* search = read_input();
                find_string(search->text);
                free_input(search);
                break;

            case 14:
                printf("Enter text to replace: ");
                struct ReadInput* replace = read_input();

                printf("Enter line number: ");
                scanf("%d", &line);
                printf("Enter index: ");
                scanf("%d", &index);

                while (getchar() != '\n');

                replace_text(replace->text, replace->length, line, index);
                free_input(replace);
                break;


            default:
                printf("Unknown command!\n");
                break;
        }
    }
}