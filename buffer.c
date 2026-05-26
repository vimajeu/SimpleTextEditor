//
// Created by ліна on 25.05.2026.
//
#include "buffer.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char symbol;
    struct Node *next;
};

static struct Node* head = NULL;
static struct Node* tail = NULL;

void buffer_append(const char *input) {
    struct Node *previous = tail;
    struct Node *first_node = malloc(sizeof(struct Node));
    first_node->symbol = input[0];
    first_node->next = NULL;
    if (head == NULL && tail == NULL) {
        head = first_node;
        tail = first_node;
        previous = first_node;
    }
    else {
        previous->next = first_node;
        tail = first_node;
        previous = first_node;
    }

    for (int i = 1; input[i] != '\0'; i++) {
        struct Node *new_node = malloc(sizeof(struct Node));
        new_node->symbol = input[i];
        new_node->next = NULL;
        previous->next = new_node;
        previous = new_node;
    }

    tail = previous;
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
        printf("File not found.");
        return;
    }

    int ch;
    while ((ch = fgetc(file)) != EOF) {
        char text[2] = {(char)ch, '\0'};
        buffer_append(text);
    }

    fclose(file);
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

void insert_text(const char *text, int line, int index) {
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
}