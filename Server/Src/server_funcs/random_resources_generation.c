/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** add ressource randomly
*/

#include "my_functions.h"


bool someone_is_doing_incantation(list_t *tile)
{
    entity_t *entity = NULL;
    client_t *client = NULL;
    command_t *command = NULL;

    for (node_t *tmp = begin(tile); tmp; next(&tmp)) {
        entity = tmp->data;
        if (entity->type != PLAYER || entity->data)
            continue;
        client = entity->data;
        command = data_at_index(client->command_queue, 0);
        if (command && command->command == do_incantation)
            return (true);
    }
    return (false);
}

void generate_random_elsewhere(server_t *server, type_t type)
{
    position_t pos = {0, 0};
    entity_t *entity = NULL;

    for (int i = 0; i < 30; i++) {
        pos.x = rand() % server->infos->width;
        pos.y = rand() % server->infos->height;
        if (someone_is_doing_incantation(server->map[pos.y][pos.x]) == true)
            continue;
        else {
            entity = calloc(sizeof(*entity), 1);
            entity->data = NULL;
            entity->type = type;
            append(&server->map[pos.y][pos.x], entity);
            tell_graphical_resource_change(server, pos, type, "pdr");
            break;
        }
    }
}

static void generate_objects(server_t *server,
        double *time_since_last_food_generation,
        double *time_since_last_object_generation,
        double actual_time)
{
    if (actual_time - *time_since_last_food_generation >=
        (double) 126 / ((float)server->infos->freq / 4)
        / length(server->clients)) {
        *time_since_last_food_generation = actual_time;
        generate_random_elsewhere(server, FOOD);
    }
    if (actual_time - *time_since_last_object_generation >=
        (double)1008 / ((float)server->infos->freq / 4)
        / length(server->clients)) {
        *time_since_last_object_generation = actual_time;
        generate_random_elsewhere(server, rand() % 5 + 1);
    }
}

void random_resources_generation(server_t *server)
{
    static double time_since_last_food_generation = 0;
    static double time_since_last_object_generation = 0;
    double actual_time = clock_seconds();

    if (server->nb_of_non_graphical_client <= 0 || length(server->clients) <= 0)
        return;
    if (time_since_last_food_generation == 0) {
        time_since_last_food_generation = actual_time;
        time_since_last_object_generation = actual_time;
        return;
    }
    generate_objects(server, &time_since_last_food_generation,
            &time_since_last_object_generation, actual_time);
}
