/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** free the server
*/

#include "my_functions.h"

void free_the_map(list_t ***map, ssize_t height, ssize_t width)
{
    for (ssize_t y = 0; y < height; y++) {
        for (ssize_t x = 0; x < width; x++) {
            free_the_list(&map[y][x], free);
        }
        free(map[y]);
    }
    free(map);
}

void free_a_client(void *data)
{
    client_t *client = data;

    free_the_list(&client->command_queue, free);
    free_the_list(&client->inventory, free);
    free(client->username);
    free(client);
}

void dead_all_client(server_t *server)
{
    if (server->clients == NULL)
        return;
    dead(server, server->clients->begin->data, NULL);
    dead_all_client(server);
}

void free_the_server(server_t *server)
{
    tell_all_graphical_client(server, "JeDeadCaChacal\n");
    dead_all_client(server);
    free_the_map(server->map, server->infos->height, server->infos->width);
    free(server->select_struct);
    free(server->socket_address);
    free_the_list(&server->infos->teams, free);
    free(server->infos);
    free(server);
}