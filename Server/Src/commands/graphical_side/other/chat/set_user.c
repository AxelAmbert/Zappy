/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** GRAPHICAL : time related functions
*/

#include "my_functions.h"

void set_user(server_t *server, client_t *client, char *args)
{
    char *buffer = NULL;
    char *tmp = my_strcat(args, " ");
    char **args_split = my_str_to_word_array(args, " ");

    if (tab_len((const char **)args_split) == 2 &&
    my_strlen(args_split[1]) <= 8) {
        safe_strcat(&buffer, client->username);
        safe_strcat(&buffer, " is now ");
        safe_strcat(&buffer, args_split[1]);
        free(client->username);
        client->username = my_strcpy(args_split[1]);
        chat(server, NULL, buffer);
    }
    free_two_dim_tab(args_split);
    free(tmp);
    free(buffer);
}