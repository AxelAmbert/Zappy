/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** GRAPHICAL : time related functions
*/

#include "my_functions.h"

void sst(server_t *server, client_t *client, char *args)
{
    int new_frequency = getnbr(args);
    char *buffer = NULL;

    if (new_frequency <= 0)
        return;
    server->infos->freq = new_frequency;
    safe_strcat(&buffer, "sst ");
    safe_strcat(&buffer, args);
    safe_strcat(&buffer, "\n");
    safe_send(client, buffer, my_strlen(buffer));
    free(buffer);
}