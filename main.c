#include <stdio.h>
#include <string.h>

int main() {
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
                char input[150];

                printf("Enter text to append (max. 150 characters): ");
                fgets(input, sizeof(input), stdin);
                input[strcspn(input, "\n")] = '\0';

                //логіка передачі цього інпуту у файл буфер

                break;

            case 2:
                
                break;

            case 3:
                break;

            case 4:
                break;

            case 5:
                break;

            case 6:
                break;

            case 7:
                break;
        }
    }
}