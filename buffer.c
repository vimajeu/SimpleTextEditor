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

void print_current() {
    struct Node *current = head;
    while (current != NULL) {
        printf("%c", current->symbol);
        current = current->next;
    }
}