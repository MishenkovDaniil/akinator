#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "../tree_struct.h"
#include "../tree/tree.h"
#include "akinator.h"

void aki_play (Tnode *node, FILE *file)
{
    printf ("Is your character %s ?\n", node->node_case);

    char answer [4] = {};
    scanf ("%s", answer);

    if (stricmp (answer, "yes") == 0 ||
        stricmp (answer, "y")   == 0 ||
        stricmp (answer, "да")  == 0)
    {
        if (node->left)
        {
            aki_play (node->left);
        }
        else
        {
            printf ("so easy..\nlet's try something more harder");
        }
    }
    else if (stricmp (answer, "no")  == 0 ||
             stricmp (answer, "n")   == 0 ||
             stricmp (answer, "нет") == 0)
    {
        if (node->right)
        {
            aki_play (node->right);
        }
        else
        {
            printf ("hmm, you win, let's add this character to aki!");
            add_character (node);
        }
    }
    else
    {
        printf ("incorrect answer\n");
        aki_play (node);
    }
}

void add_character (Tnode *node, FILE *info_file)
{
    printf ("enter the name of character (max 20 symbols)");

}
