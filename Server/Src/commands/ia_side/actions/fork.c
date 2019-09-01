/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** Lay an egg, after 600 unit time one more place is available in team
*/

#include "my_functions.h"

void fork_egg(server_t *server, client_t *client,
        char *args __attribute__((unused)))
{
    egg_t *egg = calloc(sizeof(*egg), 1);

    egg->start_time = clock_seconds();
    egg->associated_team = client->team;
    egg->client = client;
    egg->egg_nb = length(server->eggs) + 1;
    egg->position.x = client->position.x;
    egg->position.y = client->position.y;
    append(&server->eggs, egg);
    tell_graphical_egg_laying(server, client);
    safe_send(client, "ok\n", 3);
}