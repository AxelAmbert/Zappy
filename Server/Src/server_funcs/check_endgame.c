/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** Check if the game is finished
*/

#include "my_functions.h"

bool game_is_finished(server_t *server)
{
    team_t *team = NULL;

    for (node_t *tmp = begin(server->infos->teams); tmp; next(&tmp)) {
        team = tmp->data;
        if (team->level_six_members >= 6) {
            tell_graphical_winning_team(server, team->team_name);
            return (true);
        }
    }
    return (false);
}