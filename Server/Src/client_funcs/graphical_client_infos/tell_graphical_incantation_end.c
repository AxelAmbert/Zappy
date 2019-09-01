/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** GRAPHICAL : tell all graphical clients that an incantation end
*/

#include "my_functions.h"

void tell_graphical_incantation_end(server_t *server, client_t *client)
{
    char *buffer = NULL;
    char *player_nb = my_getchar(client->socket);

    safe_strcat(&buffer, "pie ");
    safe_strcat(&buffer, player_nb);
    safe_strcat(&buffer, "\n");
    tell_all_graphical_client(server, buffer);
    free(player_nb);
    free(buffer);
}