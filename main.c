#include <stdio.h>
#include <string.h>
#include "buffer.h"

int main() {
    char input[150];
    char filename[100];
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

        switch (command) {
            case 1:
                printf("Enter text to append (max. 150 characters): ");
                fgets(input, sizeof(input), stdin);
                input[strcspn(input, "\n")] = '\0';
                buffer_append(input);
                printf("Appended successfully!");
                break;

            case 2:
                new_line();
                printf("New line started successfully!");
                break;

            case 3:
                printf("Enter the file name for saving (max. 100 characters): ");
                scanf("%99s", &filename);
                save_to_file(filename);
                printf("Saved successfully!");
                break;

            case 4:
                printf("Enter the file name for loading (max. 100 characters): ");
                scanf("%99s", &filename);
                load_from_file(filename);
                printf("Loaded successfully!");
                break;

            case 5:
                print_current();
                break;

            case 6:
                printf("Enter text to insert (max. 150 characters): ");
                fgets(input, sizeof(input), stdin);
                input[strcspn(input, "\n")] = '\0';

                printf("Enter line number: ");
                scanf("%d", &line);
                printf("Enter index: ");
                scanf("%d", &index);

                insert_text(input, line, index);
                printf("Inserted successfully!");
                break;

            case 7:
                printf("Enter string to find (max. 150 characters): ");
                fgets(input, sizeof(input), stdin);
                input[strcspn(input, "\n")] = '\0';
                find_string(input);
                break;
        }
    }
}