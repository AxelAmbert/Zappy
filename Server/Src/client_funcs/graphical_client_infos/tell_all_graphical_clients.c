/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** Tell all graphical clients an information
*/

#include "my_functions.h"

void tell_all_graphical_client(server_t *server, char *message)
{
    client_t *client = NULL;

    for (node_t *tmp = begin(server->clients); tmp != NULL; next(&tmp)) {
        client = tmp->data;
        if (client->is_graphical) {
            safe_send(client, message, my_strlen(message));
        }
    }
}