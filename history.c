//
// Created by ліна on 09.06.2026.
//
#include "buffer.h"
#include "history.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static Command *undo_stack = NULL;
static Command *redo_stack = NULL;

static void free_command(Command *com) {
    if (com) {
        free(com->text);
        free(com);
    }
}

static void free_stack(Command *stack) {
    Command *current = stack;
    while (current != NULL) {
        Command *previous = current->previous;
        free_command(current);
        current = previous;
    }
}

void undo_command(CommandType type, char* text, int length, int line_position, int index_position) {
    Command *com = malloc(sizeof(Command));
    com->type = type;
    com->text = text;
    com->length = length;
    com->line = line_position;
    com->index = index_position;
    com->previous = undo_stack;
    undo_stack = com;

    free_stack(redo_stack);
    redo_stack = NULL;
}

void undo() {
    if (undo_stack == NULL) {
        printf("No commands to undo.");
        return;
    }
    Command *current = undo_stack;
    undo_stack = undo_stack->previous;

    if (current->type == append_chars) {
        insert_text(current->text, current->line, current->index);
    }
    else {
        delete(current->line, current->index, current->length);
    }
    if (redo_stack == NULL) {
        redo_stack = current;
    }
    else {
        current->previous = redo_stack;
        redo_stack = current;
    }
}

void redo() {
    if (redo_stack == NULL) {
        printf("There's no commands to redo.");
        return;
    }
    Command *current = redo_stack;
    redo_stack = redo_stack->previous;

    if (current->type == append_chars) {
        delete(current->line, current->index, current->length);
    }
    else {
        insert_text(current->text, current->line, current->index);
    }
    if (undo_stack == NULL) {
        undo_stack = current;
    }
    else {
        current->previous = undo_stack;
        undo_stack = current;
    }
}

