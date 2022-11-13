#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

#include "../tree/tree.h"
#include "akinator.h"
#include "../io/output.h"

#include "../../Stack/stack/stack.h"

int find_character (Tree *tree, Node *node, const char *character, char *definition, Stack *stack);

static const int MAX_DEF_LEN = 200;
static const int MAX_NAME_LEN = 21;
static const int MAX_ANSWER_LEN = 5;

int is_yes_answer (const char *answer)
{
    return stricmp (answer, "yes") == 0 ||
           stricmp (answer, "y")   == 0;
}
int is_no_answer (const char *answer)
{
    return stricmp (answer, "no") == 0 ||
           stricmp (answer, "n")  == 0;
}

int is_continue (char *input)
{
    printf ("incorrect input, continue? (y/n)");

    scanf ("%s", input);

    if (is_yes_answer (input))
    {
        return true;
    }
    else if (is_no_answer (input))
    {
        return false;
    }
    else
    {
        return is_continue (input);
    }
}


void aki_play (Tree *tree, Node *node, FILE *file, char *buf, int *buf_pos, const char *tree_info_file)
{
    assert (tree && node);
    assert (file);
    assert (buf && buf_pos);

    char answer [MAX_ANSWER_LEN] = "";

    while (node != nullptr)
    {
        printf ("Is your character %s?\n", node->data);
        scanf ("%s", answer);

        if (is_yes_answer (answer))
        {
            if (node->left)
            {
                node = node->left;
            }
            else
            {
                printf ("so easy..\nlet's try something more harder\n");
                return;
            }
        }
        else if (is_no_answer (answer))
        {
            if (node->right)
            {
                node = node->right;
            }
            else
            {
                printf ("hmm, you win, let's add this character to aki!\n");

                add_character (tree, node, file, buf, buf_pos, tree_info_file);

                return;
            }
        }
        else
        {
            if (is_continue (answer))
            {
                continue;
            }

            return;
        }
    }
}
/*
struct BigArray
{
    char *data;
    size_t size;
    size_t capacity;
}

// [1024 ptr00] [1024] [1024]
// realloc
array_write(size)
array_read(size)
*/
/*
Node *add_character (Tree *tree, Node *node)
{

.....
    node->left = tree_create_node(tree, answer);
    if (node->left == nullptr)
        return print ("omgasdfasf"), nullptr;

    node->right = tree_create_node(tree, node->data);
    node->data = question;
...
}*/

void add_character (Tree *tree, Node *node, FILE *info_file, char *buf, int *buf_pos, const char *tree_info_file)
{
    assert (tree && node);
    assert (info_file);
    assert (buf && buf_pos);

    int temp = 0;

    printf ("enter character name\n");

    scanf ("\n%[^\n]%n", buf + *buf_pos, &temp);

    *(buf + *buf_pos + temp) = '\0';

    add_node (tree, node, buf + *buf_pos, node->data);


    printf ("by what does %s differ from %s\n", buf + *buf_pos, node->data);

    *buf_pos += temp + 1;

    temp = 0;

    scanf ("\n%[^\n]%n", buf + *buf_pos, &temp);

    *(buf + *buf_pos + temp) = '\0';

    node->data = buf + *buf_pos;

    *buf_pos += temp + 1;

    printf ("do you want to save changes?");

    char answer[MAX_ANSWER_LEN] = "";
    scanf ("%s", answer);

    if (stricmp (answer, "yes") == 0 || stricmp (answer, "y") == 0)
    {
        tree_print (tree, tree->root, tree_info_file);
    }
}

void give_definition (Tree *tree)
{
    assert (tree);

    printf ("enter character name: ");

    char character[MAX_NAME_LEN] = "";
    scanf (" %[^\n]", character);//fgets

    char definition[MAX_DEF_LEN] = "";

    Stack stk = {};
    stack_init (&stk, 10);

    find_character (tree, tree->root, character, definition, &stk);

    if (stk.size)
    {
        printf ("%s\n", definition);
    }
    else
    {
        printf ("no such character :(\n");
    }

    stack_dtor (&stk);
}

int find_character (Tree *tree, Node *node, const char *character, char *definition, Stack *stack)
{
    static int number = 0;

    int num_now = number;
    int comma_size = 0;
    int temp = 0;

    if (stricmp (node->data, character) == 0)
    {
        *(definition + number) = '\0';
        number = 0;

        return true;
    }
    else if (node->left != nullptr && node->right != nullptr)
    {
        if (number)
        {
            sprintf (definition + number, ", ");
            comma_size = 2;
        }

        temp = sprintf (definition + comma_size + number, "%s", node->data);
        number += temp + comma_size;

        if (find_character (tree, node->left, character, definition, stack) > 0)
        {
            stack_push (stack, 1);

            *(definition + number - 2) = '\0';
            number = 0;

            return true;
        }

        temp = sprintf (definition + comma_size + num_now, "doesn't %s", node->data);
        number = num_now + temp + comma_size;

        if (find_character (tree, node->right, character, definition, stack) > 0)
        {
            stack_push (stack, 0);

            *(definition + number - 2) = '\0';
            number = 0;

            return true;
        }

        number -= temp + comma_size;
    }

    return false;
}

void compare (Tree *tree)
{
    printf ("enter first character to compare: ");
    char first_character[MAX_NAME_LEN] = "";
    scanf (" %[^\n]", first_character);

    printf ("enter second character to compare: ");
    char second_character[MAX_NAME_LEN] = "";
    scanf (" %[^\n]", second_character);

    char definitionn_1[MAX_DEF_LEN] = "";
    char definitionn_2[MAX_DEF_LEN] = "";

    char *definition_1 = definitionn_1;
    char *definition_2 = definitionn_2;

    Stack stk_1 = {};
    stack_init (&stk_1, 10);

    find_character (tree, tree->root, first_character, definition_1, &stk_1);

    Stack stk_2 = {};
    stack_init (&stk_2, 10);

    find_character (tree, tree->root, second_character, definition_2, &stk_2);

    Node *node = tree->root;

    if (!(stk_1.size && stk_2.size))
    {
        stack_dtor  (&stk_2);
        stack_dtor  (&stk_1);

        char answer [MAX_ANSWER_LEN] = "";

        if (is_continue (answer))
        {
            compare (tree);
        }

        return;
    }

    int is_true_data_1 = stack_pop (&stk_1);
    int is_true_data_2 = stack_pop (&stk_2);
    int is_start = 1;
    int comma_size = 0;

    printf ("%s and %s ", first_character, second_character);

    while (is_true_data_1 == is_true_data_2)
    {
        if (is_start)
        {
            comma_size = 0;
            printf ("are both ");
            is_start = 0;
        }
        else
        {
            comma_size = 2;
            printf (", ");
        }

        if (is_true_data_1)
        {
            printf ("%s", node->data);

            definition_1 += sizeof (node->data) + comma_size;
            definition_2 += sizeof (node->data) + comma_size;

            node = node->left;
        }
        else
        {
            printf ("doesn't %s", node->data);

            definition_1 += sizeof (node->data) + sizeof ("doesn't") + comma_size;
            definition_2 += sizeof (node->data) + sizeof ("doesn't") + comma_size;

            node = node->right;
        }

        if (stk_1.size && stk_2.size)
        {
            is_true_data_1 = stack_pop (&stk_1);
            is_true_data_2 = stack_pop (&stk_2);
        }
        else
        {
            break;
        }
    }

    if (is_start)
    {
        printf ("have nothing in similar");
    }
    printf ("\n");
    if (is_true_data_1 != is_true_data_2)
    {
        printf ("distinctive qualities of %s: %s\n", first_character, definition_1);
        printf ("distinctive qualities of %s: %s.\n", second_character, definition_2);
    }

    stack_dtor  (&stk_1);
    stack_dtor  (&stk_2);
}
