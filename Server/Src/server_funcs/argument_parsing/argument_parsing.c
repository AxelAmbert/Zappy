/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** parse argument of the zappy server
*/

#include "my_functions.h"

static void get_team_names(infos_t *infos, int *i, const char **argv)
{
    team_t *team = NULL;

    *i += 1;
    while (my_strlen(argv[*i]) != 0 && argv[*i][0] != '-') {
        team = calloc(sizeof(*team), 1);
        team->team_name = (char *)argv[*i];
        append(&infos->teams, team);
        *i += 1;
    }
    *i -= 1;
}

static void treat_argument(infos_t *infos, int *i, const char **argv)
{
    switch (argv[*i][1]) {
        case 'p':
            infos->port = safe_getnbr(argv[++*i]);
            break;
        case 'x':
            infos->width = safe_getnbr(argv[++*i]);
            break;
        case 'y':
            infos->height = safe_getnbr(argv[++*i]);
            break;
        case 'c':
            infos->nb_of_client_in_a_team = safe_getnbr(argv[++*i]);
            break;
        case 'n':
            get_team_names(infos, i, argv);
            break;
        case 'f':
            infos->freq = safe_getnbr(argv[++*i]);
            break;
    }
}

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

static void verify_arguments_integrity(infos_t *infos, const char **argv)
{
    if (infos->port > MAX_PORT_NB)
        exit_error("CRITICAL : PORT NUMBER IS TOO HIGH\n");
    if ((infos->height < 10 || infos->height > 30) && arg_isset("-y", argv))
        exit_error("CRITICAL : HEIGHT SHOULD BE BETWEEN 10 AND 30\n");
    if ((infos->width < 10 || infos->width > 30) && arg_isset("-x", argv))
        exit_error("CRITICAL : WIDTH SHOULD BE BETWEEN 10 AND 30\n");
    if ((infos->freq < 2 || infos->freq > 1000) && arg_isset("-f", argv))
        exit_error("CRITICAL : FREQ SHOULD BE BETWEEN 2 AND 1000\n");
    if (infos->nb_of_client_in_a_team < 1 && arg_isset("-c", argv))
        exit_error("CRITICAL : -c option only accepts integer values >= 1\n");
}

void parse_arguments(infos_t **infos, int argc, const char **argv)
{
    infos[0] = malloc(sizeof(**infos));
    if (infos[0] == NULL)
        exit_error("CRITICAL : Infos struct allocation failed\n");
    bzero(infos[0], sizeof(**infos));
    for (int i = 0; i < argc; i++) {
        if (my_strlen(argv[i]) != 2 || i + 1 == argc) {
            exit_error("CRITICAL : error in argument parsing\n");
        }
        treat_argument(infos[0], &i, argv);
    }
    verify_arguments_integrity(infos[0], argv);
    set_default_argument(infos[0]);
    set_default_team_names(infos[0]);
    for (node_t *tmp = begin(infos[0]->teams); tmp; next(&tmp)) {
        ((team_t *)tmp->data)->places_left =
                (uint32_t)infos[0]->nb_of_client_in_a_team;
    }
}
