/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** Decrease the player life
*/

#include "my_functions.h"

static void kill_a_player(server_t *server, node_t **tmp)
{
    node_t *next_client = tmp[0]->next;

    dead(server, tmp[0]->data, NULL);
    tmp[0] = next_client;
}

static void iterate_through_player(server_t *server, node_t *start,
        double units_to_remove)
{
    client_t *tmp_client = NULL;

    for (node_t *tmp = start; tmp != NULL; next(&tmp)) {
        tmp_client = tmp->data;
        if (tmp_client->is_connected == false ||
            tmp_client->is_graphical == true)
            continue;
        tmp_client->time_unit_left -= units_to_remove;
        if (tmp_client->time_unit_left <= 0) {
            kill_a_player(server, &tmp);
            decrease_players_life(server, tmp);
            return;
        }
    }
}

void decrease_players_life(server_t *server, node_t *start)
{
    static double time_at_last_call = 0;
    double units_to_remove = (clock_seconds() - time_at_last_call) *
            server->infos->freq;

    if (length(server->clients) == 0)
        return;
    if (time_at_last_call == 0)
        units_to_remove = 0;
    if (start == NULL)
        start = begin(server->clients);
    iterate_through_player(server, start, units_to_remove);
    time_at_last_call = clock_seconds();
}