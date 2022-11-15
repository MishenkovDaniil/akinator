#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>

#include "../tree/tree.h"
#include "input.h"

Node *tree_fill (Tree *tree, Node *node, FILE *file, char *buf, int *buf_pos)
{
    const int MAX_STR_LEN = 2;

    char bracket[MAX_STR_LEN] = "";
    int temp = 0;

    fscanf (file, "%s", bracket);

    if (*bracket == '{')
    {
        int status = fscanf (file, " \"%[^\"]%n\"", buf + *buf_pos, &temp);    ///reads case

        if (!(status))
        {
            printf ("ERROR: using names not in quotes\n");

            return nullptr;
        }

        node->data = (const char *)(buf + *buf_pos);

        *buf_pos += --temp;
        *(buf + *buf_pos) = '\0';
        (*buf_pos)++;

        fscanf (file, "%s", bracket);
    }

    if (*bracket == '{')
    {
        ungetc (*bracket, file);

        add_node (tree, node, nullptr, nullptr);

        if (tree_fill (tree, node->left,  file, buf, buf_pos) == nullptr ||
            tree_fill (tree, node->right, file, buf, buf_pos) == nullptr)
        {
            return nullptr;
        }

        fscanf (file, "%s", bracket);
    }

    if (*bracket != '}')
    {
        fprintf (stderr, "ERROR: syntax error");

        return nullptr;
    }

    return node;
}

