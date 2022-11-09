#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "tree.h"
#include "../tree_struct.h"

Tnode *talloc (void)
{
    Tnode *node = (Tnode *)calloc (1, sizeof (Tnode));
    return node;
}

void tree_ctor (Tree *tree, unsigned int *err)
{
    assert (tree);

    do
    {
        if (tree == nullptr)
        {
            printf ("wrong tree pointer");
            break;
        }

        tree->root = talloc ();
        assert (tree->root);

        if (!(tree->root))
        {
            printf ("talloc failed");
            break;
        }

    }while (0);
}

Tnode *add_left_node  (Tree *tree, Tnode *add_node, const char *left_case, unsigned int *err)
{
    assert (tree);
    assert (add_node);

    if (add_node == nullptr)
    {
        printf ("TREE_ERROR: incorrect pointer to add node");

        return nullptr;
    }
    if (left_case == nullptr)
    {
        fprintf (stderr, "TREE_ERROR: incorrect pointer to const char or nothing to add");

        return nullptr;
    }
    if (tree_check (tree, err))
    {
        printf ("ERROR");

        return nullptr;
    }

    Tnode *new_node_left = talloc ();

    if (new_node_left == nullptr)
    {
        printf ("talloc failed, line %d", __LINE__); //must be line at main

        return nullptr;
    }

    add_node->left = new_node_left;

    new_node_left->node_case = left_case;

    tree_check (tree, err);

    return new_node_left;
}

Tnode *add_right_node (Tree *tree, Tnode *add_node, const char *right_case, unsigned int *err)
{
    assert (tree);
    assert (add_node);

    if (!(add_node))
    {
        printf ("TREE_ERROR: incorrect pointer to add_place");

        return nullptr;
    }
    if (right_case == nullptr)
    {
        fprintf (stderr, "TREE_ERROR: incorrect pointer to const char or nothing to add");

        return nullptr;
    }
    if (tree_check (tree, err))
    {
        printf ("ERROR");

        return nullptr;
    }

    Tnode *new_node_right = talloc ();

    if (new_node_right == nullptr)
    {
        printf ("talloc failed, line %d", __LINE__);

        return nullptr;
    }

    add_node->right = new_node_right;

    new_node_right->node_case = right_case;

    tree_check (tree, err);

    return new_node_right;
}

Tnode *add_node (Tree *tree, Tnode *add_node, const char *left_case, const char *right_case, unsigned int *err)
{
    if (add_left_node (tree, add_node, left_case, err) == nullptr)
    {
        return nullptr;
    }

    return add_right_node(tree, add_node, right_case, err);
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

void tree_free (Tnode *node)
{
    if (node->left)
    {
        tree_free(node->left);
    }
    if (node->right)
    {
        tree_free(node->right);
    }

    free (node);
}


unsigned int tree_check (Tree *tree, unsigned int *err)
{
    if (*err) tree_dump (tree, err);

    return *err;
}

void tree_dump (Tree *tree, unsigned int *err)
{
    tree_graph (tree);
}

void tree_graph (Tree *tree)
{
    static int PNG_FILE_NUMBER = 0;

    FILE *tgraph_file = fopen ("tree_graph", "w");
    static FILE *tree_log  = fopen ("tree_dump.html", "w");

    fprintf (tgraph_file, "digraph\n{\n\t");

    make_graph_nodes (tree->root, tgraph_file);

    fprintf (tgraph_file, "}");
    fclose (tgraph_file);

    char cmd[100] = {};
    sprintf (cmd, "Dot tree_graph -T png -o tree_dots/tree_dot%d.png", PNG_FILE_NUMBER);

    //printf ("%s", cmd);

    system ((const char *)cmd);

    fprintf (tree_log, "<pre>\n<img src = tree_dots/tree_dot%d.png>\n", PNG_FILE_NUMBER++);

}

int make_graph_nodes (Tnode *node, FILE *tgraph_file)
{
    static int graph_num = 0;

    int node_num = graph_num;
    //printf ("%d", node_num);

    if (node == nullptr)
    {
        fprintf (tgraph_file, "node_%d [style = \"filled\", fillcolor = \"lightblue\", label = \"nullptr\"];\n\t", graph_num++);
    }
    else if (node->node_case == nullptr)
    {
        fprintf (tgraph_file, "node_%d [style = \"filled\", fillcolor = \"lightblue\", label = \"nullptr\"];\n\t", graph_num++);
    }
    else
    {
      //  printf ("\n\ncase is %s\n\n", node->node_case);
        fprintf (tgraph_file, "node_%d [style = \"filled\", fillcolor = \"lightblue\", label = \"%s\"];\n\t", graph_num++, node->node_case);
    }

    if (node != nullptr)
    {
        int left = make_graph_nodes (node->left, tgraph_file);
        int right = make_graph_nodes (node->right, tgraph_file);

        fprintf (tgraph_file, "node_%d->node_%d;\n\t", node_num, left);
        fprintf (tgraph_file, "node_%d->node_%d;\n\t", node_num, right);
    }

    return node_num;
}
