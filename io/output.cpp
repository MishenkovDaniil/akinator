#include <stdio.h>
#include <assert.h>

#include "../tree_struct.h"
#include "../tree/tree.h"

void tree_print (Tree *tree, const Tnode *node, const char *file)
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

void tree_print_mask (Tree *tree, int similar_mask, int mask)
{
    Tnode *node = tree->root;

    int mask_shift = 0;

    while (node->right != nullptr || node->left != nullptr)
    {
        if ((similar_mask & (0x1 << mask_shift)) == 0)
        {
            if ((mask & (0x1 << mask_shift)) == 0)
            {
                printf ("doesn't ");
            }

            printf ("%s, ", node->node_case);
        }

        if (mask & (0x1 << mask_shift))
        {
            node = node->left;
        }
        else
        {
            node = node->right;
        }

        mask_shift++;
    }
}
