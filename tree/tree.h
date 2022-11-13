#ifndef TREE_H
#define TREE_H

struct Node
{
    const char *data = nullptr;
    Node *left  = nullptr;
    Node *right = nullptr;
};

struct Tree
{
    Node *root = nullptr;//add debug info
};

static unsigned int ERRNO = 0;

Node *tree_create_node (const char *data = nullptr);

void tree_ctor (Tree *tree, unsigned int *err = &ERRNO);
void add_node (Tree *tree, Node *parent_node, const char *left_case, const char *right_case, unsigned int *err = &ERRNO);
void tree_dtor (Tree *tree, unsigned int *err = &ERRNO);
void tree_free (Node *node);

unsigned int tree_check (Tree *tree, unsigned int *err);
void tree_dump (Tree *tree, unsigned int *err);
void tree_graph (Tree *tree);
int make_graph_nodes (Node *node, FILE *tgraph_file);

#endif /* AKINATOR_H */
