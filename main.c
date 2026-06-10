#include <stdio.h>
#include <stdlib.h>
#include <_string.h>

#include "buffer.h"
#include "history.h"
#include "input.h"

int main() {
    int line;
    int index;
    int amount;

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
        printf("8. Delete characters\n");
        printf("9. Undo\n");
        printf("10. Redo\n");
        printf("11. Cut\n");
        printf("12. Paste\n");
        printf("13. Copy\n");
        printf("14. Insert with replacement\n");
        printf("Choose a command: ");

        scanf("%d", &command);

        while (getchar() != '\n');

        switch (command) {
            case 1:
                printf("Enter text to append: ");
                struct ReadInput* input = read_input();
                undo_command(delete_chars, strdup(input->text), input->length, current_line(), current_index());
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

                undo_command(delete_chars, strdup(insert->text), insert->length, line, index);

                insert_text(insert->text, line, index);
                free_input(insert);
                break;

            case 7:
                printf("Enter string to find: ");
                struct ReadInput* search = read_input();
                find_string(search->text);
                free_input(search);
                break;

            case 8:
                printf("Enter line number: ");
                scanf("%d", &line);
                printf("Enter index: ");
                scanf("%d", &index);
                printf("Enter amount of characters to delete: ");
                scanf("%d", &amount);

                while (getchar() != '\n');

                undo_command(append_chars, get_text(line, index, amount), amount, line, index);

                delete(line, index, amount);
                break;

            case 9:
                undo();
                break;

            case 10:
                redo();
                break;

            case 11:
                printf("Enter line number: ");
                scanf("%d", &line);
                printf("Enter index: ");
                scanf("%d", &index);
                printf("Enter amount of characters to cut: ");
                scanf("%d", &amount);

                while (getchar() != '\n');

                undo_command(append_chars, get_text(line, index, amount), amount, line, index);

                cut(line, index, amount);
                break;

            case 12:
                printf("Enter line number: ");
                scanf("%d", &line);
                printf("Enter index: ");
                scanf("%d", &index);

                while (getchar() != '\n');

                undo_command(delete_chars, strdup(copied_text), copied_text_length, line, index);

                paste(line, index);
                break;

            case 13:
                printf("Enter line number: ");
                scanf("%d", &line);
                printf("Enter index: ");
                scanf("%d", &index);
                printf("Enter amount of characters to copy: ");
                scanf("%d", &amount);

                while (getchar() != '\n');

                copy(line, index, amount);
                break;

            case 14:
                printf("Enter text to replace: ");
                struct ReadInput* replace = read_input();

                printf("Enter line number: ");
                scanf("%d", &line);
                printf("Enter index: ");
                scanf("%d", &index);

                while (getchar() != '\n');

                char* old_text = get_text(line, index, replace->length);
                int result_len = replace->length + strlen(old_text) + 2;
                char* result = malloc(result_len);
                strcpy(result, replace->text);
                strcat(result, "\n");
                strcat(result, old_text);
                free(old_text);

                undo_command(both, result, replace->length, line, index);

                replace_text(replace->text, replace->length, line, index);
                free_input(replace);
                break;

            default:
                printf("Unknown command!\n");
                break;
        }
    }
}