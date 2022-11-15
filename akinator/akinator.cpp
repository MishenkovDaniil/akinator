#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <string.h>

#include "../tree/tree.h"
#include "akinator.h"
#include "../io/output.h"

#define STACK_DEBUG

#include "../../Stack/stack/stack.h"

int find_character (Tree *tree, Node *node, const char *character, char *definition, Stack *stack);
int fill_character_stack (Tree *tree, Node *node, const char *character, Stack *stack);

static const int MAX_DEF_LEN = 400;
static const int MAX_NAME_LEN = 41;
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
    printf ("Incorrect input, continue? (y/n)");

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
                printf ("So easy..\nlet's try something more harder.\n");
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
                printf ("Hmm, you win, let's add this character to aki!\n");

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

/*Node *add_character (Tree *tree, Node *node)
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

    printf ("Enter character name\n");

    scanf ("\n%[^\n]%n", buf + *buf_pos, &temp);
    *(buf + *buf_pos + temp) = '\0';

    Node *new_character = tree_create_node (buf + *buf_pos);

    printf ("By what does %s differ from %s\n", buf + *buf_pos, node->data);
    *buf_pos += temp + 1;
    temp = 0;

    scanf ("\n%[^\n]%n", buf + *buf_pos, &temp);
    *(buf + *buf_pos + temp) = '\0';

    Node *differ_node = tree_create_node (buf + *buf_pos);

    *buf_pos += temp + 1;

    if (node->parent->left == node)
    {
        node->parent->left = differ_node;
    }
    else
    {
        node->parent->right = differ_node;
    }

    differ_node->parent = node->parent;
    differ_node->left = new_character;
    differ_node->right = node;

    node->parent = differ_node;
    new_character->parent = differ_node;

    printf ("Do you want to save changes?(y/n)");

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

    printf ("Enter character name: ");

    char character[MAX_NAME_LEN] = "";
    scanf (" %[^\n]", character);//fgets

    char definition[MAX_DEF_LEN] = "";

    Stack stk = {};
    unsigned int stk_size = 10;
    stack_init (&stk, stk_size);

    find_character (tree, tree->root, character, definition, &stk);

    if (stk.size)
    {
        *definition -= 32;
        printf ("%s.\n\n", definition);
    }
    else
    {
        printf ("No such character :(\n\n");
    }
    //printf ("1");
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

            //*(definition + number - 2) = '\0';
            //number = 0;

            return true;
        }

        temp = sprintf (definition + comma_size + num_now, "doesn't %s", node->data);
        number = num_now + temp + comma_size;

        if (find_character (tree, node->right, character, definition, stack) > 0)
        {
            stack_push (stack, 0);

            //*(definition + number - 2) = '\0';
            //number = 0;

            return true;
        }

        number -= temp + comma_size;
    }

    return false;
}

int fill_character_stack (Tree *tree, Node *node, const char *character, Stack *stack)
{
    if (node->data)
    {
        if (stricmp (node->data, character) == 0)
        {
            return 1;
        }
    }
    else if (node->left != nullptr && node->right != nullptr)
    {
        if (fill_character_stack (tree, node->left, character, stack) == 1)
        {
            stack_push (stack, 1);
            return 1;
        }
        else if (fill_character_stack (tree, node->right, character, stack) == 1)
        {
            stack_push (stack, 0);
            return 1;
        }
        else
        {
            return 0;
        }
    }
    return 0;
}

void compare (Tree *tree)
{
    printf ("enter first character to compare: ");
    char first_character[MAX_NAME_LEN] = "";
    scanf (" %[^\n]", first_character);

    printf ("enter second character to compare: ");
    char second_character[MAX_NAME_LEN] = "";
    scanf (" %[^\n]", second_character);

    char definition_1[MAX_DEF_LEN] = "";
    char definition_2[MAX_DEF_LEN] = "";

    unsigned int stk_size = 20;

    Stack stk_1 = {};
    stack_init (&stk_1, stk_size);

    int status_1 = find_character (tree, tree->root, first_character, definition_1, &stk_1);
    Stack stk_2 = {};
    stack_init (&stk_2, stk_size);

    int status_2 = find_character (tree, tree->root, second_character, definition_2, &stk_2);

    Node *node = tree->root;

    if (!(status_1 && status_2))
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
    int comma_size = 2;
    int shift = 0;
   // printf ("def_1: %s\n", definition_1);

    printf ("\n%s and %s ", first_character, second_character);

    while (is_true_data_1 == is_true_data_2)
    {
        if (is_start)
        {
            printf ("are both ");
            is_start = 0;
        }
        else
        {
            printf (", ");
        }

        if (is_true_data_1)
        {
            printf ("%s", node->data);

            shift += strlen (node->data) + comma_size;

            if (node->left)
            {
                node = node->left;
            }
            else
            {
                break;
            }
        }
        else
        {
            printf ("doesn't %s", node->data);

            shift += strlen (node->data) + strlen ("doesn't ") + comma_size;

            if (node->right)
            {
                node = node->right;
            }
            else
            {
                break;
            }
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
    printf (".\n");
    if (is_true_data_1 != is_true_data_2)
    {
     //   printf ("def_1: %s\n", definition_1);
       // printf ("def_2: %s\n", definition_2);

        //printf ("%d\n", shift);
        printf ("Distinctive qualities of %s: %s.\n", first_character, definition_1 + shift);
        printf ("Distinctive qualities of %s: %s.\n\n", second_character, definition_2 + shift);
    }

    stack_dtor  (&stk_2);
    stack_dtor  (&stk_1);
}
