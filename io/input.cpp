#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>

#include "../tree_struct.h"
#include "../tree/tree.h"
#include "input.h"

Tnode *tree_fill (Tree *tree, Tnode *node, FILE *file, char *buf, int *buf_pos)
{
    const int MAX_STR_LEN = 100;

    char str[MAX_STR_LEN] = {};
    char str_case[MAX_STR_LEN] = {};
    int temp = 0;

    fscanf (file, "%s", str);

    if (*str == '{')
    {
        fscanf (file, "%[^\"]", str_case);                  ///reads spaces before first "
        fgetc (file);                                       ///reads first "
        fscanf (file, "%[^\"]%n", buf + *buf_pos, &temp);   ///reads case (without "") in buffer
        fgetc (file);                                       ///reads second "

        node->node_case = (const char *)(buf + *buf_pos);

        *buf_pos += temp;
        *(buf + *buf_pos) = '\0';
        (*buf_pos)++;

        fscanf (file, "%s", str);
    }

    if (*str == '{')
    {
        ungetc (*str, file);

        add_node (tree, node, nullptr, nullptr);

        if (tree_fill (tree, node->left,  file, buf, buf_pos) == nullptr ||
            tree_fill (tree, node->right, file, buf, buf_pos) == nullptr)
        {
            return nullptr;
        }

        fscanf (file, "%s", str);
    }

    if (*str != '}')
    {
        fprintf (stderr, "ERROR: syntax error");

        return nullptr;
    }

    return node;
}

