//
// Created by ліна on 09.06.2026.
//
#include "buffer.h"
#include "history.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    else if (current->type == delete_chars){
        delete(current->line, current->index, current->length);
    }
    else {
        char* pointer = strchr(current->text, '\n');

        if (pointer != NULL) {
            *pointer = '\0';
        }

        char* old_text = (pointer != NULL) ? pointer + 1 : NULL;

        delete(current->line, current->index, current->length);
        if (old_text != NULL) {
            insert_text(old_text, current->line, current->index);
        }

        if (pointer != NULL) {
            *pointer = '\n';
        }
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
    else if (current->type == delete_chars) {
        insert_text(current->text, current->line, current->index);
    }
    else {
        char* pointer = strchr(current->text, '\n');

        if (pointer != NULL) {
            *pointer = '\0';
        }

        char* new_text = current->text;
        char* old_text = (pointer != NULL) ? pointer + 1 : NULL;
        int old_length = (old_text != NULL) ? strlen(old_text) : 0;

        delete(current->line, current->index, old_length);
        insert_text(new_text, current->line, current->index);

        if (pointer != NULL) {
            *pointer = '\n';
        }
    }

    if (undo_stack == NULL) {
        undo_stack = current;
    }
    else {
        current->previous = undo_stack;
        undo_stack = current;
    }
}

