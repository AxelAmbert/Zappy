/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** GRAPHICAL : the all graphical client that a resource was put on a tile
*/

#include "my_functions.h"

static void do_command(server_t *server, client_t *client)
{
    char *player_nb = my_getchar(client->socket);
    char *buffer = NULL;
    char *egg_nb = my_getchar(length(server->eggs));
    char *x = my_getchar(client->position.x);
    char *y = my_getchar(client->position.y);

    safe_strcat(&buffer, "pfk ");
    safe_strcat(&buffer, player_nb);
    safe_strcat(&buffer, " ");
    safe_strcat(&buffer, egg_nb);
    safe_strcat(&buffer, " ");
    safe_strcat(&buffer, x);
    safe_strcat(&buffer, " ");
    safe_strcat(&buffer, y);
    safe_strcat(&buffer, "\n");
    tell_all_graphical_client(server, buffer);
    free(player_nb);
    free(buffer);
    free(egg_nb);
    free(x);
    free(y);
}

void tell_graphical_egg_laying(server_t *server, client_t *client)
{
    if (count(server->clients, NULL, is_a_graphical_client) == 0)
        return;
    do_command(server, client);
}