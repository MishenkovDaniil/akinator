#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <strings.h>

#include "tree/tree.h"
#include "io/input.h"
#include "io/output.h"
#include "../standart_functions/io/io.h"
#include "akinator/akinator.h"

void print_help_info (void);


int main ()
{
    printf ("WELCOME TO AKINATOR!\n");

    char *cmd = (char *)calloc (100, sizeof (char));

    system_voice (cmd, 1, "..\\balcon -n Irina -t \"WELCOME TO AKINATOR\"");

    const char *tree_info = "tree_info.txt";

    FILE *info_file = fopen (tree_info, "r");

    size_t tree_info_size = get_file_size (tree_info);
    char *buf = (char *)calloc (tree_info_size, sizeof (char));     ///buffer of "akinator" cases
    assert (buf);

    int buf_pos = 0;                                                ///free position in buffer of "akinator" cases

    Tree tree = {};
    tree_ctor (&tree);

    tree_fill (&tree, tree.root, info_file, buf, &buf_pos);

#define run_cmd(full_name, short_name, letter, number, action)  \
if (strcasecmp (option, full_name)  == 0 ||                        \
    strcasecmp (option, short_name) == 0 ||                        \
    strcasecmp (option, letter)     == 0 ||                        \
    strcasecmp (option, number)     == 0)                          \
{                                                               \
    action                                                      \
}                                                               \
else

    const int MAX_OPTION_LEN = 15;
    char option[MAX_OPTION_LEN] = "";

    for (;;)
    {
        printf ("Choose game option (\"help\" for more info):\n");
        system_voice (cmd, 1, "..\\balcon -n Irina -t \" Choose game option\"");

        scanf ("%s", option);

        if (strcasecmp (option, "help") == 0 ||
            strcasecmp (option, "h")    == 0)
        {
            print_help_info ();
            continue;
        }
        //run_cmd ("help", "h", "h", "h", {print_help_info (); continue;}) -- what's better??
        run_cmd ("akinator", "aki", "a", "1", {aki_play (&tree, tree.root, info_file, buf, &buf_pos, tree_info);})
        run_cmd ("definition", "def", "d", "2", {give_definition (&tree);})
        run_cmd ("compare", "comp", "c", "3", {compare (&tree);})
        run_cmd ("show", "show", "s", "4", {tree_graph (&tree);})
        run_cmd ("quit", "quit", "q", "5", {break;})
        /*else*/
        {
            printf ("ERROR: wrong command (%s)", option);
            system_voice (cmd, 3, "..\\balcon -n Irina -t \" wrong command ", option, "\"");
        }
    }

#undef run_cmd

    tree_dtor (&tree);

    free (buf);
    fclose (info_file);
    free (cmd);

    return 0;
}


void print_help_info (void)
{
    printf ("\"aki\"/\"akinator\"       start the game;\n"
            "\"def\"/\"definition\"     receive the definition of character;\n"
            "\"comp\"/\"compare\"       compare two characters;\n"
            "\"show\"                 receive the akinator graph;\n"
            "\"voice\"                turn on voice;\n"
            "\"quit\"                 end the game;\n"
            "\"help\"                 see this message.\n\n");
}

