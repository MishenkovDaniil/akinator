#ifndef AKINATOR_H
#define AKINATOR_H

#include "../tree_struct.h"
#include "../tree/tree.h"

void aki_play (Tree *tree, Tnode *node, FILE *file, char *buf, int *buf_pos);
void add_character (Tree *tree, Tnode *node, FILE *info_file, char *buf, int *buf_pos);
void give_definition (Tree *tree);
int find_character (Tree *tree, Tnode *node, const char *character, char *definition, int *mask);
void compare (Tree *tree);
char *getword (char *buf, char *word);

#endif /* AKINATOR_H */
