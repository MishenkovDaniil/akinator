#ifndef AKINATOR_H
#define AKINATOR_H

#include "../tree/tree.h"

int is_yes_answer (const char *answer);
int is_no_answer (const char *answer);
int is_continue (char *input);

void aki_play (Tree *tree, Node *node, FILE *file, char *buf, int *buf_pos, const char *tree_info_file);
void add_character (Tree *tree, Node *node, FILE *info_file, char *buf, int *buf_pos, const char *tree_info_file);
void give_definition (Tree *tree);
void compare (Tree *tree);

#endif /* AKINATOR_H */
