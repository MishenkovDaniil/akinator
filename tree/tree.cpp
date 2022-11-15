#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "tree.h"

#define print(fmt, ...) printf ("%s: %d: " fmt "\n", __FUNCTION__, __LINE__, __VA_ARGS__) ////

Node *tree_create_node (const char *data)
{
    Node *node = (Node *)calloc (1, sizeof (Node));
    assert (node);

    if (node == nullptr)
    {
        return printf ("calloc failed"), nullptr;
    }

    node->data = data;

    return node;
}

void tree_ctor (Tree *tree, unsigned int *err)
{
    assert (tree);

    if (tree == nullptr)
    {
        printf ("wrong tree pointer");
        return;
    }

    tree->root = tree_create_node ();
    assert (tree->root);
}

void add_node (Tree *tree, Node *parent_node, const char *left_case, const char *right_case, unsigned int *err)
{
    assert (tree);
    assert (parent_node);

    if (parent_node == nullptr)
    {
        printf ("TREE_ERROR: incorrect pointer to parent node.\n");

        return;
    }
    if (tree_check (tree, err))
    {
        return;
    }

    Node *new_node_left = tree_create_node (left_case);
    Node *new_node_right = tree_create_node (right_case);

    if (new_node_left == nullptr || new_node_right == nullptr)
    {
        return;
    }

    parent_node->left = new_node_left;
    parent_node->right = new_node_right;

    new_node_left->parent = parent_node;
    new_node_right->parent = parent_node;

    tree_check (tree, err);
}

void tree_dtor (Tree *tree, unsigned int *err)
{
    assert (tree && tree->root);

    if (tree && tree->root)
    {
        tree_free (tree->root);
    }
    else
    {
        printf ("nothing to dtor");
    }
}

void tree_free (Node *node)
{
    if (node->left)
    {
        node->left->data = nullptr;
        tree_free(node->left);
    }
    if (node->right)
    {
        node->right->data = nullptr;
        tree_free(node->right);
    }

    free (node);
    node = nullptr;
}


unsigned int tree_check (Tree *tree, unsigned int *err)
{
    if (*err)
    {
        tree_dump (tree, err);

        return *err;
    }

    return 0;
}

void tree_dump (Tree *tree, unsigned int *err)
{
    tree_graph (tree);
}

void tree_graph (Tree *tree)
{
    static int PNG_FILE_NUMBER = 0;

    FILE *tgraph_file = fopen ("tree_graph", "w");
    FILE *tree_log  = nullptr;

    if (!(PNG_FILE_NUMBER))
    {
        tree_log  = fopen ("tree_dump.html", "w");
    }
    else
    {
        tree_log  = fopen ("tree_dump.html", "a");
    }

    fprintf (tgraph_file, "digraph\n{\n\t");

    make_graph_nodes (tree->root, tgraph_file);

    fprintf (tgraph_file, "}");
    fclose (tgraph_file);

    const int CMD_LEN = 100;
    char cmd[CMD_LEN] = "";

    sprintf (cmd, "Dot tree_graph -T png -o tree_dots/tree_dot%d.png", PNG_FILE_NUMBER);

    printf ("%s", cmd);

    system ((const char *)cmd);

    fprintf (tree_log, "<pre>\n<img src = tree_dots/tree_dot%d.png>\n", PNG_FILE_NUMBER++);

    fclose (tree_log);
}

int make_graph_nodes (Node *node, FILE *tgraph_file)
{
    static int graph_num = 0;

    int node_num = graph_num;

    if (node == nullptr)
    {
        fprintf (tgraph_file, "node_%d [style = \"filled\", fillcolor = \"lightblue\", label = \"nullptr\"];\n\t", graph_num++);
    }
    else if (node->data == nullptr)
    {
        fprintf (tgraph_file, "node_%d [style = \"filled\", fillcolor = \"lightblue\", label = \"nullptr\"];\n\t", graph_num++);
    }
    else
    {
        fprintf (tgraph_file, "node_%d [style = \"filled\", fillcolor = \"lightblue\", label = \"%s\"];\n\t", graph_num++, node->data);
    }

    if (node->left != nullptr && node->right != nullptr)
    {
        int left = make_graph_nodes (node->left, tgraph_file);
        int right = make_graph_nodes (node->right, tgraph_file);

        fprintf (tgraph_file, "node_%d->node_%d;\n\t", node_num, left);
        fprintf (tgraph_file, "node_%d->node_%d;\n\t", node_num, right);
    }

    return node_num;
}
