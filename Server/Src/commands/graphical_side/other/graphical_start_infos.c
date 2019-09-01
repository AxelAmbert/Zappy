/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** GRAPHICAL : players related functions
*/

#include "my_functions.h"

void graphical_start_infos(server_t *server,
        client_t *client __attribute__((unused)))
{
    char *buffer = NULL;

    add_all_map_resources_to_buffer(server, &buffer);
}