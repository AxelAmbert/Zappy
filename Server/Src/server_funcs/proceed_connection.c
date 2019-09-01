/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** handle clients commands
*/

#include "my_functions.h"

static inline void take_egg_place(server_t *server, client_t *client)
{
    egg_t *egg = NULL;

    for (node_t *tmp = begin(client->team->eggs); tmp != NULL; next(&tmp)) {
        egg = tmp->data;
        if (egg->is_hatched == true) {
            client->position = egg->position;
            tell_graphical_egg_dying(server, egg);
            remove_from_linked_list(tmp, &client->team->eggs);
            break;
        }
    }
}

static inline void init_client(server_t *server, client_t *client,
        team_t *team)
{
    entity_t *new_entity = calloc(sizeof(*new_entity), 1);

    new_entity->type = PLAYER;
    new_entity->data = client;
    client->team = team;
    client->is_connected = true;
    client->existence_time.start_time = clock_seconds();
    client->time_unit_left = 1260;
    client->looking_direction = rand() % 4;
    client->position = (position_t){
        rand() % (int)server->infos->width,
        rand() % (int)server->infos->height,
    };
    append(&server->map[client->position.y][client->position.x], new_entity);
    client->level = 1;
    take_egg_place(server, client);
}

static inline void accept_connection(server_t *server, client_t *client,
        team_t *team)
{
    char *nb = NULL;
    char *x = NULL;
    char *y = NULL;
    char *dummy_string = NULL;

    team->places_left -= 1;
    nb = my_getchar(team->places_left);
    my_reallocstrcat(&nb, "\n");
    x = my_getchar((int)server->infos->width);
    y = my_getchar((int)server->infos->height);
    dummy_string = my_strncat(4, x, " ", y, "\n");
    safe_send(client, nb, my_strlen(nb));
    safe_send(client, dummy_string, my_strlen(dummy_string));
    free(nb);
    free(x);
    free(y);
    free(dummy_string);
    init_client(server, client, team);
}

static bool graphical_client(client_t *client, char *args)
{
    if (my_strcmp(args, "GRAPHIC", true) == true) {
        client->is_connected = true;
        client->is_graphical = true;
        return (true);
    }
    return (false);
}

void proceed_connection(server_t *server, client_t *client, char *str)
{
    team_t *tmp_team = NULL;

    if (graphical_client(client, str) == true)
        return;
    if (str != NULL) {
        tmp_team = get_data_from_value(server->infos->teams,
                str, lambda_team_cmp);
        if (tmp_team != NULL && tmp_team->places_left > 0) {
            server->nb_of_non_graphical_client += 1;
            accept_connection(server, client, tmp_team);
            tell_graphical_new_connection(server, client);
            return;
        }
    }
    safe_send(client, "ko\n", 3);
}
