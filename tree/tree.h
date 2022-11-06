#ifndef TREE_H
#define TREE_H

#include "../tree_struct.h"

static unsigned int ERRNO = 0;

void tree_ctor (Tree *tree, unsigned int *err = &ERRNO);
static Tnode *talloc (void);
Tnode *add_left_node  (Tree *tree, Tnode *add_node, const char *left_case,  unsigned int *err = &ERRNO);
Tnode *add_right_node (Tree *tree, Tnode *add_node, const char *right_case, unsigned int *err = &ERRNO);
Tnode *add_node (Tree *tree, Tnode *add_node, const char *left_case, const char *right_case, unsigned int *err = &ERRNO);
void tree_dtor (Tree *tree, unsigned int *err = &ERRNO);
void tree_free (Tnode *node);
unsigned int tree_check (Tree *tree, unsigned int *err);
void tree_dump (Tree *tree, unsigned int *err);
void tree_graph (Tree *tree);
int make_graph_nodes (Tnode *node, FILE *tgraph_file);

#endif /* AKINATOR_H */
