/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** GRAPHICAL : map size
*/

#include "my_functions.h"

void msz(server_t *server, client_t *client,
        char *args __attribute__((unused)))
{
    char buffer[11];
    char *x = my_getchar((int)server->infos->width);
    char *y = my_getchar((int)server->infos->height);

    strcpy(buffer, "msz 00 00\n");
    memcpy(buffer + 4, x, 2);
    memcpy(buffer + 7, y, 2);
    safe_send(client, buffer, 11);
    free(x);
    free(y);
}