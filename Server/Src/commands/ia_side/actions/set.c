/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** Leave an object on the tile
*/

#include "my_functions.h"

static void leave_food(server_t *server, client_t *client, list_t *tile)
{
    entity_t *new_food = NULL;

    if (client->time_unit_left >= 126) {
        tell_graphical_resource_change(server,
        (position_t){client->position.x, client->position.y}, FOOD, "pdr");
        client->time_unit_left -= 126;
        new_food = calloc(sizeof(*new_food), 1);
        new_food->type = FOOD;
        append(&tile, new_food);
        safe_send(client, "ok\n", 3);
    } else {
        safe_send(client, "ko\n", 3);
    }
}

void leave_object(server_t *server, client_t *client, list_t *tile, type_t type)
{
    entity_t *entity = NULL;

    if (type == FOOD) {
        leave_food(server, client, tile);
        return;
    }
    for (node_t *tmp = begin(client->inventory); tmp != NULL; tmp = tmp->next) {
        entity = tmp->data;
        if (entity->type == type) {
            transfert_a_node(&client->inventory, &tile, tmp);
            safe_send(client, "ok\n", 3);
            tell_graphical_resource_change(server,
                    (position_t){client->position.x, client->position.y},
                    type, "pdr");
            return;
        }
    }
    safe_send(client, "ko\n", 3);
}

void set(server_t *server, client_t *client, char *args)
{
    list_t *tile = server->map[client->position.y][client->position.x];
    type_t type = str_to_type(args);

    if (type == NOT_KNOWN || (length(client->inventory) == 0 && type != FOOD)) {
        safe_send(client, "ko\n", 3);
    } else {
        leave_object(server, client, tile, type);
    }
}