//
// Created by ліна on 10.06.2026.
//

#ifndef SIMPLETEXTEDITOR_INPUT_H
#define SIMPLETEXTEDITOR_INPUT_H

struct ReadInput {
    char *text;
    int length;
};

struct ReadInput* read_input();
void free_input(struct ReadInput* input);

#endif //SIMPLETEXTEDITOR_INPUT_H
