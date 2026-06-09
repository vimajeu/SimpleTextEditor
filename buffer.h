//
// Created by ліна on 25.05.2026.
//

#ifndef SIMPLETEXTEDITOR_BUFFER_H
#define SIMPLETEXTEDITOR_BUFFER_H

void buffer_append(const char *input);
void new_line();
void save_to_file(const char *filename);
void load_from_file(const char *filename);
void print_current();
void find_string(const char *text);
void insert_text(const char *text, int line, int index);
void replace_text(const char *text, int length, int line, int index);
void delete(int line, int index, int amOfSymbols);
void copy(int line, int index, int amount);
void paste(int line, int index);

#endif //SIMPLETEXTEDITOR_BUFFER_H
