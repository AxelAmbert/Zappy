/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** GRAPHICAL : time related functions
*/

#include "my_functions.h"

static void kick_the_user(char *user, server_t *server)
{
    client_t *tmp_client = NULL;
    int client_to_kick = 0;
    char *buffer = NULL;

    client_to_kick = getnbr(user);
    for (node_t *tmp = begin(server->clients); tmp; next(&tmp)) {
        tmp_client = tmp->data;
        if (tmp_client->socket == client_to_kick && !tmp_client->is_graphical) {
            safe_strcat(&buffer, user);
            safe_strcat(&buffer, " ");
            safe_strcat(&buffer, "bas been kicked");
            chat(server, NULL, buffer);
            free(buffer);
            dead(server, tmp_client, NULL);
            return;
        }
    }
}

void kick(server_t *server, char *args)
{
    char **values = NULL;
    char *tmp = NULL;

    tmp = my_strcat(args, " ");
    values = my_str_to_word_array(tmp, " ");
    if (tab_len((const char **)values) != 2) {
        free_two_dim_tab(values);
        return;
    }
    kick_the_user(values[1], server);
    free(tmp);
    free_two_dim_tab(values);
}
