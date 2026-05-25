//
// Created by ліна on 21.05.2026.
//
#include "input.h"
#include <stdio.h>

int main() {
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
    printf("You chose %d", command);
}