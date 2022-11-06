#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "../tree_struct.h"
#include "../tree/tree.h"
#include "akinator.h"
#include "../io/output.h"

void aki_play (Tree *tree, Tnode *node, FILE *file, char *buf, int *buf_pos)
{
    assert (tree && node);
    assert (file);
    assert (buf && buf_pos);

    printf ("Is your character %s ?\n", node->node_case);

    char answer [4] = {};
    scanf ("%s", answer);

    if (stricmp (answer, "yes") == 0 ||
        stricmp (answer, "y")   == 0 ||
        stricmp (answer, "да")  == 0)
    {
        if (node->left)
        {
            aki_play (tree, node->left, file, buf, buf_pos);
        }
        else
        {
            printf ("so easy..\nlet's try something more harder\n");
        }
    }
    else if (stricmp (answer, "no")  == 0 ||
             stricmp (answer, "n")   == 0 ||
             stricmp (answer, "нет") == 0)
    {
        if (node->right)
        {
            aki_play (tree, node->right, file, buf, buf_pos);
        }
        else
        {
            printf ("hmm, you win, let's add this character to aki!\n");
            add_character (tree, node, file, buf, buf_pos);
            aki_play (tree, tree->root, file, buf, buf_pos);
        }
    }
    else
    {
        printf ("incorrect answer\n");
        aki_play (tree, node, file, buf, buf_pos);
    }
}

void add_character (Tree *tree, Tnode *node, FILE *info_file, char *buf, int *buf_pos)
{
    assert (tree && node);
    assert (info_file);
    assert (buf && buf_pos);

    int temp = 0;

    printf ("enter the name of character\n");

    scanf ("%s%n", buf + *buf_pos, &temp);

    *(buf + *buf_pos + temp) = '\0';

    add_node (tree, node, buf + *buf_pos, node->node_case);
    printf ("by what does %s differ from %s\n", buf + *buf_pos, node->node_case);//fgets

    *buf_pos += temp + 1;

    temp = 0;

    scanf ("%s%n", buf + *buf_pos, &temp);//fgets

    *(buf + *buf_pos + temp) = '\0';

    node->node_case = buf + *buf_pos;

    *buf_pos += temp + 1;

    printf ("do you want to save changes?");

    char answer[5] = {};
    scanf ("%s", answer);

    if (stricmp (answer, "yes") == 0 || stricmp (answer, "y") == 0)
    {
        tree_print (tree, tree->root, "tree_info.txt"); //передавать const char to add character and aki_play
    }
}

void give_definition (Tree *tree)
{
    assert (tree);

    printf ("enter character name\n");

    char character[21] = {};
    scanf ("%s", character);//fgets

    char definition[1000] = {};

    int status = find_character (tree, tree->root, character, definition);

    if (status)
    {
        printf ("%s\n", definition);
    }
    else
    {
        printf ("no such character :(\n");
    }
}

int find_character (Tree *tree, Tnode *node, const char *character, char *definition)
{
    static int number = 0;
    int temp = 0;

    if (stricmp (node->node_case, character) == 0)
    {
        *(definition + number - 2) = '\0';
        number = 0;

        return 1;
    }
    else if (node->left != nullptr && node->right != nullptr)
    {
        temp = sprintf (definition + number, "%s, ", node->node_case);
        number += temp;

        if (find_character (tree, node->left, character, definition) == 1)
        {
            *(definition + number - 2) = '\0';
            number = 0;

            return 1;
        }

        number -= temp;

        temp = sprintf (definition + number, "not %s, ", node->node_case);
        number += temp;

        if (find_character (tree, node->right, character, definition) == 1)
        {
            *(definition + number - 2) = '\0';
            number = 0;

            return 1;
        }

        number -= temp;
    }

    return 0;
}
