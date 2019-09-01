/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** GRAPHICAL : tell a scanning utility usefull infos
*/

#include "my_functions.h"

void scan(server_t *server, client_t *client,
        char *args __attribute__((unused)))
{
    char *buffer = NULL;
    char *time = my_getchar((int)server->time_alive);
    char *nb = my_getchar(server->nb_of_non_graphical_client);

    safe_strcat(&buffer, "scan ");
    safe_strcat(&buffer, nb);
    safe_strcat(&buffer, " ");
    safe_strcat(&buffer, time);
    safe_strcat(&buffer, "\n");
    safe_send(client, buffer, my_strlen(buffer));
    free(time);
    free(nb);
    free(buffer);
}