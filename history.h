//
// Created by ліна on 09.06.2026.
//

#ifndef SIMPLETEXTEDITOR_HISTORY_H
#define SIMPLETEXTEDITOR_HISTORY_H
#include <stdbool.h>

typedef enum {
    delete_chars,
    append_chars,
    both
} CommandType;

typedef struct Command {
    CommandType type;
    char *text;
    int length;
    int line;
    int index;
    struct Command* previous;
} Command;

void undo_command(CommandType type, char* text, int length, int line_position, int index_position);
void undo();
void redo();
#endif //SIMPLETEXTEDITOR_HISTORY_H
