/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** turn 90 degrees left
*/

#include "my_functions.h"

void left(server_t *server __attribute__((unused)), client_t *client,
        char *args __attribute__((unused)))
{
    if (client->looking_direction == UP)
        client->looking_direction = LEFT;
    else
        client->looking_direction -= 1;
    safe_send(client, "ok\n", 3);
}

