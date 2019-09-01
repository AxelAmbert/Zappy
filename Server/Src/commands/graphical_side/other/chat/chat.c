/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** GRAPHICAL : time related functions
*/

#include "my_functions.h"

static void check_if_username_exist(server_t *server, client_t *client)
{
    if (client && client->username == NULL)
        usr(server, client, "");
}

static bool redirect_commands(server_t *server, client_t *client, char *args)
{
    if (my_strncmp(args, "/kick", my_strlen("/kick"), true) == true) {
        kick(server, args);
        return (true);
    } else if (my_strncmp(args, "/setuser", my_strlen("/setuser"), true)
    == true) {
        set_user(server, client, args);
        return (true);
    }
    if (my_strncmp(args, "/tg", my_strlen("/tg"), true) == true) {
        tg(client);
        return (true);
    }
    return (false);
}

void chat(server_t *server, client_t *client, char *args)
{
    char *buffer = NULL;
    client_t *tmp_client = NULL;

    check_if_username_exist(server, client);
    if (redirect_commands(server, client, args) == true)
        return;
    safe_strcat(&buffer, "chat ");
    if (client != NULL) {
        safe_strcat(&buffer, client->username);
        safe_strcat(&buffer, " : ");
    } else
        safe_strcat(&buffer, "[INFOS] ");
    safe_strcat(&buffer, args);
    safe_strcat(&buffer, "\n");
    for (node_t *tmp = begin(server->clients); tmp; next(&tmp)) {
        tmp_client = tmp->data;
        if (tmp_client->is_graphical)
            safe_send(tmp_client, buffer, strlen(buffer));
    }
    free(buffer);
}