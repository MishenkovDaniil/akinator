#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

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

    char definition[200] = {};

    int status = 0;
    find_character (tree, tree->root, character, definition, &status);

    if (status)
    {
        printf ("status is %d\n", status);
        printf ("%s\n", definition);
    }
    else
    {
        printf ("no such character :(\n");
    }
}

int find_character (Tree *tree, Tnode *node, const char *character, char *definition, int *mask)
{
    static int number = 0;
    static int mask_shift = 0;

    int temp = 0;

    if (stricmp (node->node_case, character) == 0)
    {
        *(definition + number - 2) = '\0';
        number = 0;

        return *mask;
    }
    else if (node->left != nullptr && node->right != nullptr)
    {
        temp = sprintf (definition + number, "%s, ", node->node_case);
        number += temp;

        *mask |= 0x1 << mask_shift;
        printf ("bleft %d\t",*mask);
        mask_shift++;

        if (find_character (tree, node->left, character, definition, mask) > 0)
        {
            *(definition + number - 2) = '\0';
            number = 0;

            mask_shift = 0;
            return *mask;
        }

        mask_shift--;

        number -= temp;

        temp = sprintf (definition + number, "doesn't %s, ", node->node_case);
        number += temp;

        *mask &= ~(0x1 << mask_shift);
        printf ("bright %d\t", *mask);

        mask_shift++;

        if (find_character (tree, node->right, character, definition, mask) > 0)
        {
            *(definition + number - 2) = '\0';
            number = 0;

            mask_shift = 0;
            return *mask;
        }

        number -= temp;
    }

    return 0;
}

void compare (Tree *tree)
{
    printf ("enter first character to compare\n");
    char first_character[21] = {};
    scanf ("%s", first_character);

    printf ("enter second character to compare\n");
    char second_character[21] = {};
    scanf ("%s", second_character);

    char definition_1[200] = {};
    char definition_2[200] = {};

    int status_1 = 0;
    find_character (tree, tree->root, first_character, definition_1, &status_1);
    int status_2 = 0;
    find_character (tree, tree->root, second_character, definition_2, &status_2);

    if (status_1 && status_2)
    {
        printf ("%s %s, but %s ", first_character, definition_1, second_character);

        char word_1[100] = {};
        char word_2[100] = {};

        getword (definition_1, word_1);
        getword (definition_2, word_2);

        //printf ("word1 is [%s]\n", word_1);
        //printf ("word2 is [%s]\n", word_2);

        int change = 0;

        while (strcmp (word_1, word_2) == 0)
        {
            change += strlen (word_1);

            //printf ("[%d]\n", change);

            getword (definition_1 + change, word_1);
            //printf ("word1 is [%s]\n", word_1);
            getword (definition_2 + change, word_2);
            //printf ("word2 is [%s]\n", word_2);
        }

        printf ("%s\n", definition_2 + change);
    }
    else
    {
        printf ("incorrect character name(s)\n");
    }
}

char *getword (char *buf, char *word)
{
    int i = 0;

    while (isspace (*(buf + i)))
    {
        i++;
    }

    while (!(isspace (*(buf + i))))
    {
        i++;
    }
    int space_elem = *(buf + i);
    *(buf + i) = '\0';


    strcpy (word, buf);

    *(buf + i) = space_elem;

    return word;
}
