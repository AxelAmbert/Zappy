/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** Start the incantation process
*/

#include "my_functions.h"

static void is_incantation_player(server_t *server, client_t *client,
        client_t *incantation_client)
{
    command_t *incantation_cmd = NULL;

    incantation_cmd = calloc(sizeof(*incantation_cmd), 1);
    incantation_cmd->start_time = clock_seconds();
    incantation_cmd->command = do_incantation;
    incantation_cmd->command_time = (double)300 / server->infos->freq;
    safe_send(client, "Elevation underway\n", 19);
    tell_graphical_incantation_start(server, client);
    if (client == incantation_client) {
        insert_at_index(&client->command_queue, incantation_cmd, 1);
    } else {
        push_front(&client->command_queue, incantation_cmd);
    }
}

static void tell_incantation_is_ready_to_everyone(list_t *tile,
        server_t *server, client_t *incantation_client)
{
    entity_t *entity = NULL;

    for (node_t *tmp = begin(tile); tmp != NULL; next(&tmp)) {
        entity = tmp->data;
        if (entity->type == PLAYER) {
            is_incantation_player(server, entity->data, incantation_client);
        }
    }
}

bool check_if_incantation_can_be_done(client_t *client, list_t *tile,
        bool check_level)
{
    for (type_t type = FOOD; type != END; type += 1) {
        if (elevation_requirement[client->level - 1][type] !=
        count(tile, &type, lambda_entity_type_cmp)) {
            return (false);
        }
    }
    if (check_level == true &&
    count(tile, &client->level, lambda_entity_level) !=
    elevation_requirement[client->level - 1][7]) {
        return (false);
    }
    return (true);
}

void start_incantation(server_t *server, client_t *client,
        char *args __attribute__((unused)))
{
    list_t *tile = server->map[client->position.y][client->position.x];
    command_t *incantation_cmd = NULL;

    client->incantation_initiator = true;
    if (check_if_incantation_can_be_done(client, tile, true) == false) {
        incantation_cmd = calloc(sizeof(*incantation_cmd), 1);
        incantation_cmd->command = do_incantation;
        incantation_cmd->start_time = clock_seconds();
        incantation_cmd->command_time = (double)300 / server->infos->freq;
        insert_at_index(&client->command_queue, incantation_cmd, 1);
        safe_send(client, "ko\n", 3);
        tell_graphical_incantation_start(server, client);
    } else {
        tell_incantation_is_ready_to_everyone(tile, server, client);
    }
}
