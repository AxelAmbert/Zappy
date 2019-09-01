/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** GRAPHICAL : tell all graphical clients that a new client is here
*/

#include "my_functions.h"

static void release_resources(char *buffer, char *x, char *y, char *playernb)
{
    free(buffer);
    free(x);
    free(y);
    free(playernb);
}

static void do_command(server_t *server, client_t *client)
{
    char *buffer = NULL;
    char *player_nb = my_getchar(client->socket);
    char player_level[2] = {49, 0};
    char *x = my_getchar(client->position.x);
    char *y = my_getchar(client->position.y);

    safe_strcat(&buffer, "pwn ");
    safe_strcat(&buffer, player_nb);
    safe_strcat(&buffer, " ");
    safe_strcat(&buffer, x);
    safe_strcat(&buffer, " ");
    safe_strcat(&buffer, y);
    safe_strcat(&buffer, " ");
    safe_strcat(&buffer, orientation_str[client->looking_direction]);
    safe_strcat(&buffer, " ");
    safe_strcat(&buffer, player_level);
    safe_strcat(&buffer, " ");
    safe_strcat(&buffer, client->team->team_name);
    safe_strcat(&buffer, "\n");
    tell_all_graphical_client(server, buffer);
    release_resources(buffer, x, y, player_nb);
}

void tell_graphical_new_connection(server_t *server, client_t *client)
{
    if (count(server->clients, NULL, is_a_graphical_client) == 0)
        return;
    do_command(server, client);
}