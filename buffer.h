//
// Created by ліна on 25.05.2026.
//

#ifndef SIMPLETEXTEDITOR_BUFFER_H
#define SIMPLETEXTEDITOR_BUFFER_H

struct Node {
    char symbol;
    struct Node *next;
};
static char* copied_text;
int copied_text_length;
char* get_text(int line, int index, int amount);
int current_line();
int current_index();
void buffer_append(const char *input);
void new_line();
void save_to_file(const char *filename);
void load_from_file(const char *filename);
void print_current();
void find_string(const char *text);
void insert_text(char *text, int line, int index);
void replace_text(const char *text, int length, int line, int index);
void delete(int line, int index, int amOfSymbols);
void copy(int line, int index, int amount);
void paste(int line, int index);
void cut(int line, int index, int amount);

#endif //SIMPLETEXTEDITOR_BUFFER_H
