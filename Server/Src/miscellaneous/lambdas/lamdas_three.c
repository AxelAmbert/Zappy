/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** mostly lambdas function pointer
*/

#include "my_functions.h"

bool lambda_team_cmp(void *one, void *two)
{
    team_t *team_one = one;
    char *team_two = two;

    return (my_strcmp(team_one->team_name, team_two, false));
}