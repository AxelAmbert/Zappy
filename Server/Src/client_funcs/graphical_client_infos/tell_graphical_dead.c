/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** GRAPHICAL : the all graphical client that a client died
*/

#include "my_functions.h"

void tell_graphical_dead(server_t *server, client_t *dead_client)
{
    char *player_nb = NULL;
    char *buffer = NULL;

    if (count(server->clients, NULL, is_a_graphical_client) != 0) {
        safe_strcat(&buffer, "pdi ");
        player_nb = my_getchar(dead_client->socket);
        safe_strcat(&buffer, player_nb);
        safe_strcat(&buffer, "\n");
        tell_all_graphical_client(server, buffer);
        free(buffer);
        free(player_nb);
    }
}