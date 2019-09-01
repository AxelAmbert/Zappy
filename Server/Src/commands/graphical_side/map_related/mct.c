/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** GRAPHICAL : map related functions
*/

#include "my_functions.h"

static void conditional_strcat(server_t *server, char **buffer, int x, int y)
{
    if (y + 1 == server->infos->height && x + 1 == server->infos->width) {
        safe_strcat(buffer, "\n");
    } else {
        safe_strcat(buffer, " - ");
    }
}

void add_all_map_resources_to_buffer(server_t *server, char **buffer)
{
    for (uint32_t y = 0; y < server->infos->height; y++) {
        for (uint32_t x = 0; x < server->infos->width; x++) {
            add_all_resources_to_buffer(buffer, server->map[y][x]);
            conditional_strcat(server, buffer, x, y);
        }
    }
}

void mct(server_t *server, client_t *client,
        char *args __attribute__((unused)))
{
    char *buffer = NULL;

    safe_strcat(&buffer, "mct - ");
    add_all_map_resources_to_buffer(server, &buffer);
    safe_send(client, buffer, my_strlen(buffer));
    free(buffer);
}
