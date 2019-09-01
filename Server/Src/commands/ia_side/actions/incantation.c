/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** Do the incantation
*/

#include "my_functions.h"

void do_incantation(server_t *server, client_t *client,
        char *args __attribute__((unused)))
{
    char buffer[18];
    list_t *tile = server->map[client->position.y][client->position.x];

    strcpy(buffer, "Current level:  \n");
    buffer[15] = (char)client->level + (char)48;
    if (check_if_incantation_can_be_done(client, tile, false) == false) {
        if (client->incantation_initiator == true)
            safe_send(client, "ko\n", 3);
        else
            safe_send(client, buffer, 17);
    } else {
        client->level += 1;
        if (client->level == 8)
            client->team->level_six_members += 1;
        buffer[15] += 1;
        safe_send(client, buffer, 17);
    }
    client->incantation_initiator = false;
    tell_graphical_incantation_end(server, client);
}