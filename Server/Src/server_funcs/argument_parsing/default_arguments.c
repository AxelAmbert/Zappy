/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** set default arguments of server
*/

#include "my_functions.h"

static void set_default_team_names(infos_t *infos)
{
    team_t *team = NULL;

    if (length(infos->teams) == 0) {
        team = calloc(sizeof(*team), 1);
        team->team_name = my_strcpy("Team1");
        append(&infos->teams, team);
        team = calloc(sizeof(*team), 1);
        team->team_name = my_strcpy("Team2");
        append(&infos->teams, team);
        team = calloc(sizeof(*team), 1);
        team->team_name = my_strcpy("Team3");
        append(&infos->teams, team);
        team = calloc(sizeof(*team), 1);
        team->team_name = my_strcpy("Team4");
        append(&infos->teams, team);
    }
}

void set_default_argument(infos_t *infos)
{
    set_default_team_names(infos);
    if (infos->height == 0)
        infos->height = 10;
    if (infos->width == 0)
        infos->width = 10;
    if (infos->nb_of_client_in_a_team == 0)
        infos->nb_of_client_in_a_team = 3;
    if (infos->freq == 0)
        infos->freq = 10;
    if (infos->port == 0)
        infos->port = 4242;
    printf("Port : %d\n", (int)infos->port);
}