/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** GRAPHICAL : the all graphical client when a player forward
*/

#include "my_functions.h"

static void do_command(server_t *server, client_t *client, position_t new_pos)
{
    char *buffer = NULL;
    char *nb = my_getchar(client->socket);
    char *x = my_getchar(new_pos.x);
    char *y = my_getchar(new_pos.y);

    safe_strcat(&buffer, "forward ");
    safe_strcat(&buffer, nb);
    safe_strcat(&buffer, " ");
    safe_strcat(&buffer, x);
    safe_strcat(&buffer, " ");
    safe_strcat(&buffer, y);
    safe_strcat(&buffer, "\n");
    tell_all_graphical_client(server, buffer);
    free(buffer);
    free(nb);
    free(x);
    free(y);
}

void tell_graphical_forward(server_t *server, client_t *client,
        position_t new_pos)
{
    if (count(server->clients, NULL, is_a_graphical_client) == 0)
        return;
    do_command(server, client, new_pos);
}