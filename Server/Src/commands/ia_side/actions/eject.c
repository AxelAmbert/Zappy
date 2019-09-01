/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** send to the client the nbr of team unused slots
*/

#include "my_functions.h"

static void tell_ejected_player_direction(client_t *client,
        client_t *ejected_client)
{
    char buffer[11] = {0};

    strcpy(buffer, "eject:  \n");
    if (client->looking_direction == ejected_client->looking_direction)
        buffer[7] = 5 + 48;
    else if (get_opposite(client->looking_direction) ==
    ejected_client->looking_direction) {
        buffer[7] = 1 + 48;
    }
    if (unclockwise_ninety(client->looking_direction) ==
    ejected_client->looking_direction) {
        buffer[7] = 3 + 48;
    } else if (clockwise_ninety(client->looking_direction) ==
    ejected_client->looking_direction) {
        buffer[7] = 7 + 48;
    }
    safe_send(ejected_client, buffer, strlen(buffer));
}

static void eject_a_player(server_t *server, client_t *client,
        client_t *ejected_client, list_t **tile)
{
    position_t new_pos = get_new_valid_positions(
            &ejected_client->position,
            &moving_positions[client->looking_direction], server);
    node_t *ejected_client_node = get_node_by_value(tile[0], ejected_client,
            lambda_client_entity_cmp);

    transfert_a_node(tile, &server->map[new_pos.y][new_pos.x],
            ejected_client_node);
    tell_graphical_eject(server, (int_pair_t){client->socket,
        ejected_client->socket}, &ejected_client->position, &new_pos);
    ejected_client->position = new_pos;
    tell_ejected_player_direction(client, ejected_client);
}

void eject(server_t *server, client_t *client,
        char *args __attribute__((unused)))
{
    bool other_player_on_tyle = false;
    list_t **tile = &server->map[client->position.y][client->position.x];
    entity_t *entity = NULL;

    for (node_t *tmp = begin(tile[0]); tmp != NULL; next(&tmp)) {
        entity = tmp->data;
        if (entity->type == PLAYER && entity->data != client) {
            other_player_on_tyle = true;
            eject_a_player(server, client, entity->data, tile);
            tmp = begin(tile[0]);
        }
    }
    if (other_player_on_tyle == true) {
        safe_send(client, "ok\n", 3);
    } else {
        safe_send(client, "ko\n", 3);
    }
}
