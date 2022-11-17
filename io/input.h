#ifndef INPUT_H
#define INPUT_H

#include "../tree/tree.h"

// tree_load --> tree.h
// tree_save --> tree.h
Node *tree_load (Tree *tree, FILE *from);
Node *tree_save (Tree *tree, FILE *to);

Node *tree_fill (Tree *tree, Node *node, FILE *file, char *buf, int *buf_pos);
int system_voice (char *cdm, int num,...);

#endif /* INPUT_H */
