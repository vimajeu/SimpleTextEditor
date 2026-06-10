//
// Created by ліна on 25.05.2026.
//
#include "buffer.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static struct Node* head = NULL;
static struct Node* tail = NULL;

static char* copied_text = NULL;
int copied_text_length = 0;

int current_line() {
    int counter = 0;
    struct Node* current = head;
    if (head == NULL && tail == NULL) {
        return 0;
    }
    while (current != tail) {
        if (current->symbol == '\n') {
            counter++;
        }
        current = current->next;
    }
    return counter;
}

int current_index() {
    int counter = 0;
    struct Node* current = head;
    while (current != tail) {
        if (current->symbol == '\n') {
            counter = 0;
            current = current->next;
            continue;
        }
        current = current->next;
        counter++;
    }
    return counter;
}

char* get_text(int line, int index, int amount) {
    int current_line_index = 0;
    int current_index = 0;
    struct Node *current = head;

    while (current != NULL) {
        if (current_line_index == line && current_index == index) {
            break;
        }

        if (current->symbol == '\n') {
            current_line_index++;
            current_index = 0;
            if (index == 0 && current_line_index == line) {
                break;
            }
        }
        else {
            current_index++;
        }
        current = current->next;
    }

    if (current == NULL) {
        printf("Error: Position out of bounds.\n");
        return NULL;
    }

    if (copied_text != NULL) {
        free(copied_text);
    }
    char* result = malloc(amount + 1);
    int counter = 0;
    for (int i = 0; i < amount; i++) {
        if (current == NULL) {
            break;
        }
        result[i] = current->symbol;
        current = current->next;
        counter++;
    }
    result[counter] = '\0';
    return result;
}

void buffer_append(const char *input) {
    struct Node *first_node = malloc(sizeof(struct Node));
    first_node->symbol = input[0];
    first_node->next = NULL;

    if (head == NULL) {
        head = first_node;
        tail = first_node;
    } else {
        tail->next = first_node;
        tail = first_node;
    }

    for (int i = 1; input[i] != '\0'; i++) {
        struct Node *new_node = malloc(sizeof(struct Node));
        new_node->symbol = input[i];
        new_node->next = NULL;
        tail->next = new_node;
        tail = new_node;
    }
}

void new_line() {
    buffer_append("\n");
}

void save_to_file(const char *filename) {
    FILE *file = fopen(filename, "w");
    struct Node *current = head;
    while (current != NULL) {
        fputc(current->symbol, file);
        current = current->next;
    }
    fclose(file);
}

void load_from_file(const char *filename) {
    struct Node *current = head;
    while (current != NULL) {
        struct Node *next = current->next;
        free(current);
        current = next;
    }
    head = NULL;
    tail = NULL;

    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        printf("File not found.\n");
        return;
    }

    int ch;
    while ((ch = fgetc(file)) != EOF) {
        char text[2] = {(char)ch, '\0'};
        buffer_append(text);
    }

    fclose(file);
    printf("Loaded successfully!\n");
}

void print_current() {
    struct Node *current = head;
    while (current != NULL) {
        printf("%c", current->symbol);
        current = current->next;
    }
    printf("\n");
}

void find_string(const char *text) {
    int matches_lines[50];
    int matches_lines_index = 0;
    int matches[50];
    int matches_index = 0;

    int line_index = 0;
    int index = 0;

    char first_char = text[0];
    struct Node *current = head;
    while (current != NULL) {
        if (current->symbol == '\n') {
            line_index++;
            index = 0;
            current = current->next;
            continue;
        }
        if (first_char == current->symbol) {
            struct Node *temp = current->next;
            int is_match = 1;
            for (int i = 1; i < strlen(text); i++) {
                if (temp == NULL || temp->symbol != text[i]) {
                    is_match = 0;
                    break;
                }
                temp = temp->next;
            }

            if (is_match == 1) {
                matches_lines[matches_lines_index] = line_index;
                matches_lines_index++;
                matches[matches_index] = index;
                matches_index++;
            }
        }
        current = current->next;
        index++;
    }

    if (matches_lines_index != 0) {
        printf("Result found on ");
        for (int i = 0; i < matches_index; i++) {
            printf("(%d, %d) ", matches_lines[i], matches[i]);
        }
    }
    else {
        printf("No result found.");
    }
    printf("\n");
}

void insert_text(char *text, int line, int index) {
    if (index == 0) {
        if (line == 0) {
            struct Node* current_head = head;
            struct Node* current_tail = tail;
            head = NULL;
            tail = NULL;
            buffer_append(text);
            tail->next = current_head;
            tail = current_tail;
            return;
        }
    }

    int current_line_index = 0;
    int current_index = 0;
    struct Node *current = head;

    while (current != NULL) {
        if (current_line_index == line && current_index == index - 1) {
            break;
        }

        if (current->symbol == '\n') {
            current_line_index++;
            if (index == 0 && current_line_index == line) {
                break;
            }
            current_index = 0;
        }
        else {
            current_index++;
        }
        current = current->next;
    }

    if (current == NULL) {
        printf("Error: Position out of bounds.\n");
        return;
    }

    struct Node *next_nodes = current->next;
    struct Node *original_tail = tail;
    tail = current;
    buffer_append(text);
    tail->next = next_nodes;
    if (next_nodes != NULL) {
        tail = original_tail;
    }
    printf("Inserted successfully!\n");
}

void delete(int line, int index, int amOfSymbols){
    bool is_first = false;
    int current_line_index = 0;
    int current_index = 0;
    struct Node *current = head;

    if (index == 0 && line == 0) {
        is_first = true;
    }
    else {
        while (current != NULL) {
            if (current_line_index == line && current_index == index - 1) {
                break;
            }

            if (current->symbol == '\n') {
                current_line_index++;
                current_index = 0;
                if (index == 0 && current_line_index == line) {
                    break;
                }
            }
            else {
                current_index++;
            }
            current = current->next;
        }
    }

    struct Node *end = current;
    if (end->symbol == '\n') {
        end = end->next;
    }
    while (end != NULL) {
        if (current_index == index + amOfSymbols) {
            break;
        }

        if (end->symbol == '\n') {
            break;
        }
        current_index++;
        end = end->next;
    }

    if (!is_first) {
        if (current == NULL) {
            printf("Error: Position out of bounds.\n");
            return;
        }

        current->next = end;
        if (end == NULL) {
            tail = current;
        }
        printf("Deleted successfully!\n");
    }
    else {
        head = end;
        if (end == NULL) {
            tail = NULL;
        }
        printf("Deleted successfully!\n");
    }
}

void replace_text(const char *text, int length, int line, int index) {
    delete(line, index, length);
    insert_text(text, line, index);
    printf("Repaced successfully!\n");
}

void copy(int line, int index, int amount) {
    int current_line_index = 0;
    int current_index = 0;
    struct Node *current = head;

    while (current != NULL) {
        if (current_line_index == line && current_index == index) {
            break;
        }

        if (current->symbol == '\n') {
            current_line_index++;
            current_index = 0;
            if (index == 0 && current_line_index == line) {
                break;
            }
        }
        else {
            current_index++;
        }
        current = current->next;
    }

    if (current == NULL) {
        printf("Error: Position out of bounds.\n");
        return;
    }

    if (copied_text != NULL) {
        free(copied_text);
    }
    copied_text = malloc(amount + 1);
    copied_text_length = 0;
    for (int i = 0; i < amount; i++) {
        if (current == NULL) {
            break;
        }
        copied_text[i] = current->symbol;
        current = current->next;
        copied_text_length++;
    }
    copied_text[copied_text_length] = '\0';

    printf("Copied successfully!\n");
}

void paste(int line, int index) {
    if (copied_text == NULL) {
        printf("There's no copied text to paste.\n");
        return;
    }
    insert_text(copied_text, line, index);
}

void cut(int line, int index, int amount) {
    copy(line, index, amount);
    delete(line, index, amount);
}