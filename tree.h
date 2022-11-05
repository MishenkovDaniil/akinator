#ifndef A_H
#define A_H

struct Tnode
{
    const char *node_case = nullptr;
    Tnode *left  = nullptr;
    Tnode *right = nullptr;
};

struct Tree
{
    size_t size = 0;
    Tnode *root = nullptr;
};

#endif /*  A_H */
