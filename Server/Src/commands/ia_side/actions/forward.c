/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** Go forward from where player is looking
*/

#include "my_functions.h"

position_t get_new_valid_positions(
        const position_t *one,
        const position_t *two,
        server_t *server)
{
    position_t to_return;

    to_return.x = one->x + two->x;
    to_return.y = one->y + two->y;
    if (to_return.x >= server->infos->width) {
        to_return.x = 0;
    } else if (to_return.x < 0) {
        to_return.x = (int)server->infos->width - 1;
    }
    if (to_return.y >= server->infos->height) {
        to_return.y = 0;
    } else if (to_return.y < 0) {
        to_return.y = (int)server->infos->height - 1;
    }
    return (to_return);
}

void forward(server_t *server, client_t *client,
        char *args __attribute__((unused)))
{
    position_t new_pos = get_new_valid_positions(
            &client->position, &moving_positions[client->looking_direction],
            server);
    list_t **old_list = &server->map[client->position.y][client->position.x];
    list_t **new_list = &server->map[new_pos.y][new_pos.x];
    node_t *client_node = get_node_by_value(old_list[0], client,
            lambda_client_entity_cmp);

    tell_graphical_forward(server, client, new_pos);
    client->position = new_pos;
    transfert_a_node(old_list, new_list, client_node);
    safe_send(client, "ok\n", 3);
}