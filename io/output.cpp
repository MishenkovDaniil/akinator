#include <stdio.h>
#include <assert.h>

#include "../tree/tree.h"
#include "output.h"

void tree_print (Tree *tree, const Node *node, const char *file)
{
    static int tab_num = 1;                         ///number of tabs to put before case

    FILE *tree_info = nullptr;

    if (node == tree->root)
    {
        tree_info = fopen (file, "w");
    }
    else
    {
        tree_info = fopen (file, "a");
    }
    assert (tree_info);

    if (tree_info == nullptr)
    {
        fprintf (stderr, "fopen failed\n function: %s\nfile: %s", __PRETTY_FUNCTION__, __FILE__);
    }

    fprintf (tree_info, "{ \"%s\"", node->data);

    if (node->left != nullptr && node->right != nullptr)
    {
        fprintf (tree_info, "\n");

        for (int i = 0; tab_num - i > 0; i++)
        {
            fprintf (tree_info, "\t");
        }

        int cur_tab_num = tab_num++;

        fclose (tree_info);

        tree_print (tree, node->left, file);

        tree_info = fopen (file, "a");

        for (int i = 0; cur_tab_num - i > 0; i++)
        {
            fprintf (tree_info, "\t");
        }

        fclose (tree_info);

        tree_print (tree, node->right, file);
        tab_num--;

        tree_info = fopen (file, "a");

        for (int i = 1; tab_num - i > 0; i++)
        {
            fprintf (tree_info, "\t");
        }

        fprintf (tree_info, "}\n");

        fclose (tree_info);
    }
    else
    {
        fprintf (tree_info, " }\n");

        fclose (tree_info);
    }
}
