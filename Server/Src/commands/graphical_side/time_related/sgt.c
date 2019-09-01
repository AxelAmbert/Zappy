/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** GRAPHICAL : time related functions
*/

#include "my_functions.h"

void sgt(server_t *server, client_t *client,
        char *args __attribute__((unused)))
{
    char *buffer = NULL;
    char *time = my_getchar((int)server->infos->freq);

    safe_strcat(&buffer, "sgt ");
    safe_strcat(&buffer, time);
    safe_strcat(&buffer, "\n");
    safe_send(client, buffer, my_strlen(buffer));
    free(time);
    free(buffer);
}