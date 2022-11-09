#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

#include "../tree_struct.h"
#include "../tree/tree.h"
#include "akinator.h"
#include "../io/output.h"

static const int MAX_DEF_LEN = 200;
static const int MAX_NAME_LEN = 21;

void aki_play (Tree *tree, Tnode *node, FILE *file, char *buf, int *buf_pos, const char *tree_info_file)
{
    assert (tree && node);
    assert (file);
    assert (buf && buf_pos);

    printf ("Is your character %s?\n", node->node_case);

    const int MAX_ANSWER_SIZE = 5;

    char answer [MAX_ANSWER_SIZE] = {};
    scanf ("%s", answer);

    if (stricmp (answer, "yes") == 0 ||
        stricmp (answer, "y")   == 0 ||
        stricmp (answer, "да")  == 0)
    {
        if (node->left)
        {
            aki_play (tree, node->left, file, buf, buf_pos, tree_info_file);
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
            aki_play (tree, node->right, file, buf, buf_pos, tree_info_file);
        }
        else
        {
            printf ("hmm, you win, let's add this character to aki!\n");

            add_character (tree, node, file, buf, buf_pos, tree_info_file);

            aki_play (tree, tree->root, file, buf, buf_pos, tree_info_file);
        }
    }
    else
    {
        printf ("incorrect answer\n");

        aki_play (tree, node, file, buf, buf_pos, tree_info_file);
    }
}

void add_character (Tree *tree, Tnode *node, FILE *info_file, char *buf, int *buf_pos, const char *tree_info_file)
{
    assert (tree && node);
    assert (info_file);
    assert (buf && buf_pos);

    int temp = 0;

    printf ("enter character name\n");

    fgetc (stdin);
    scanf ("%[^\n]%n", buf + *buf_pos, &temp);

    *(buf + *buf_pos + temp) = '\0';

    add_node (tree, node, buf + *buf_pos, node->node_case);


    printf ("by what does %s differ from %s\n", buf + *buf_pos, node->node_case);//fgets

    *buf_pos += temp + 1;

    temp = 0;

    fgetc (stdin);
    scanf ("%[^\n]%n", buf + *buf_pos, &temp);//fgets

    *(buf + *buf_pos + temp) = '\0';

    node->node_case = buf + *buf_pos;

    *buf_pos += temp + 1;

    printf ("do you want to save changes?");

    char answer[5] = {};
    scanf ("%s", answer);

    if (stricmp (answer, "yes") == 0 || stricmp (answer, "y") == 0)
    {
        tree_print (tree, tree->root, tree_info_file); //пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ const char to add character and aki_play
    }
}

void give_definition (Tree *tree)
{
    assert (tree);


    printf ("enter character name\n");

    char character[MAX_NAME_LEN] = {};
    scanf ("%s", character);//fgets

    char definition[MAX_DEF_LEN] = {};

    int status = 0;
    find_character (tree, tree->root, character, definition, &status);

    if (status)
    {
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
    char first_character[MAX_NAME_LEN] = {};
    scanf ("%s", first_character);

    printf ("enter second character to compare\n");
    char second_character[MAX_NAME_LEN] = {};
    scanf ("%s", second_character);

    char definition_1[MAX_DEF_LEN] = {};
    char definition_2[MAX_DEF_LEN] = {};

    int status_1 = 0;
    find_character (tree, tree->root, first_character, definition_1, &status_1);
    int status_2 = 0;
    find_character (tree, tree->root, second_character, definition_2, &status_2);

    int differ_mask = 0;
    int similar_mask = 0;
    int mask_shift = 0;

    Tnode *node = tree->root;

    if (status_1 > 0 && status_2 > 0)
    {
        int search = (status_1 > status_2) ? status_1 : status_2;

        printf ("%s and %s are both ", first_character, second_character);

        while (search > 0 && node != nullptr)
        {
            if ((status_1 & (0x1 << mask_shift)) == (status_2 & (0x1 << mask_shift)))
            {
                if ((status_1 & (0x1 << mask_shift)) == 1)
                {
                    printf ("%s, ", node->node_case);

                    node = node->left;
                }
                else
                {
                    printf ("doesn't %s, ", node->node_case);

                    node = node->right;
                }

                similar_mask |= 0x1 << mask_shift;
            }

            search /= 2;
            mask_shift++;
        }

        printf ("\nbut %s ", first_character);
        tree_print_mask (tree, similar_mask, status_1);

        printf ("\nand %s ", second_character);
        tree_print_mask (tree, similar_mask, status_2);
        printf ("\n");
    }
    else
    {
        printf ("incorrect character name(s)\n");
    }
}
