#ifndef INPUT_H
#define INPUT_H

#include "../tree_struct.h"
#include "../tree/tree.h"

Tnode *tree_fill (Tree *tree, Tnode *node, FILE *file, char *buf, int *buf_pos);

#endif /* INPUT_H */
