/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** GRAPHICAL : team related functions
*/

#include "my_functions.h"

void tna(server_t *server, client_t *client,
        char *args __attribute__((unused)))
{
    char *buffer = NULL;
    team_t *team = NULL;

    safe_strcat(&buffer, "tna ");
    for (node_t *tmp = begin(server->infos->teams); tmp; next(&tmp)) {
        team = tmp->data;
        safe_strcat(&buffer, team->team_name);
        safe_strcat(&buffer, tmp->next == NULL ? "\n" : " ");
    }
    safe_send(client, buffer, my_strlen(buffer));
    free(buffer);
}