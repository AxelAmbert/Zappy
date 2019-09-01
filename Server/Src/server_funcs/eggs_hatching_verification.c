/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** Check if the eggs laid by client is hatched
*/

#include "my_functions.h"

inline static void add_a_new_place_in_team(server_t *server, egg_t *egg,
        node_t *tmp)
{
    egg->associated_team->places_left += 1;
    egg->is_hatched = true;
    transfert_a_node(&server->eggs, &egg->client->team->eggs, tmp);
}

void check_for_eggs_hatching(server_t *server)
{
    egg_t *egg = NULL;
    double actual_time = clock_seconds();

    for (node_t *tmp = begin(server->eggs); tmp != NULL; tmp = tmp->next) {
        egg = tmp->data;
        if (actual_time - egg->start_time >=
        ((double)600 / server->infos->freq)) {
            tell_graphical_egg_hatching(server, egg);
            add_a_new_place_in_team(server, egg, tmp);
            check_for_eggs_hatching(server);
            return;
        }
    }
}