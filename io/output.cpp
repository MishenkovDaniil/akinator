#include <stdio.h>
#include <assert.h>

#include "../tree_struct.h"
#include "../tree/tree.h"

void tree_print (Tree *tree, const Tnode *node, const char *file)
{
    static int tab_num = 1;

    FILE *tree_info = nullptr;

    if (node == tree->root)
    {
        tree_info = fopen (file, "w");
    }
    else
    {
        tree_info = fopen (file, "a");
    }

    fprintf (tree_info, "{ \"%s\"", node->node_case);

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
