#ifndef TREE_STRUCT_H
#define TREE_STRUCT_H

struct Tnode
{
    const char *node_case = nullptr;
    Tnode *left  = nullptr;
    Tnode *right = nullptr;
};

struct Tree
{
    Tnode *root = nullptr;//add debug info
};

#endif /* TREE_STRUCT_H */
