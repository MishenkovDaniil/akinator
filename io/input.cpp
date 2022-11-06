#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>

#include "../tree_struct.h"
#include "../tree/tree.h"
#include "input.h"

Tnode *tree_fill (Tree *tree, Tnode *node, FILE *file, char *buf)
{
    char symbol = 0;
    char str[100] = {};
    char str_case[100] = {};
    int temp = 0;
    static int number = 0;

    fscanf (file, "%s", str);
    //printf ("{ is [%c]\n", *str);

    if (*str == '{')
    {
        fscanf (file, "%[^\"]", str_case);
        fgetc (file);
        fscanf (file, "%[^\"]%n", buf + number, &temp);
        //printf ("temp is %d\n", temp);
        fgetc (file);

        node->node_case = (const char *)(buf + number);

        number += temp;
        *(buf + number) = '\0';
        number++;
        temp = 0;
        //printf ("number is %d\n", number);

        //printf ("str is [%s]\n", node->node_case);

        fscanf (file, "%s", str);

        //printf ("next is [%c]\n", *str);
    }

    if (*str == '}')
    {
        return node;
    }
    else if (*str == '{')
    {
        ungetc (*str, file);

        add_node (tree, node, nullptr, nullptr);

        tree_fill (tree, node->left, file, buf);
        tree_fill (tree, node->right, file, buf);

        fscanf (file, "%s", str);

        return node;
    }
    else
    {
        fprintf (stderr, "ERROR: syntax error");
    }

    return node;
}

