/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** Take an object on the tile
*/

#include "my_functions.h"

static void take_food(client_t *client, list_t **tile, node_t *food)
{
    remove_from_linked_list(food, tile);
    client->time_unit_left += 126;
    safe_send(client, "ok\n", 3);
}

static void get_object(server_t *server, client_t *client, list_t *tile,
        type_t type)
{
    entity_t *entity = NULL;
    position_t pos = {client->position.x, client->position.y};

    for (node_t *tmp = begin(tile); tmp != NULL; tmp = tmp->next) {
        entity = tmp->data;
        if (entity->type == type && type == FOOD) {
            tell_graphical_resource_change(server, pos, type, "pgt");
            take_food(client, &tile, tmp);
            generate_random_elsewhere(server, FOOD);
            return;
        } else if (entity->type == type) {
            tell_graphical_resource_change(server, pos, type, "pgt");
            transfert_a_node(&tile, &client->inventory, tmp);
            generate_random_elsewhere(server, type);
            safe_send(client, "ok\n", 3);
            return;
        }
    }
    safe_send(client, "ko\n", 3);
}

void take(server_t *server, client_t *client, char *args)
{
    list_t *tile = server->map[client->position.y][client->position.x];
    type_t type = str_to_type(args);

    if (type == NOT_KNOWN || length(tile) <= 1) {
        safe_send(client, "ko\n", 3);
    } else {
        get_object(server, client, tile, type);
    }
}