/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** GRAPHICAL : the all graphical client that a message was sent
*/

#include "my_functions.h"

void tell_graphical_broadcast(server_t *server, client_t *client,
        char *message)
{
    char *buffer = NULL;
    char *client_nb = NULL;

    if (count(server->clients, NULL, is_a_graphical_client) == 0)
        return;
    client_nb = my_getchar(client->socket);
    safe_strcat(&buffer, "pbc ");
    safe_strcat(&buffer, client_nb);
    safe_strcat(&buffer, " ");
    safe_strcat(&buffer, message);
    safe_strcat(&buffer, "\n");
    tell_all_graphical_client(server, buffer);
    free(buffer);
    free(client_nb);
}