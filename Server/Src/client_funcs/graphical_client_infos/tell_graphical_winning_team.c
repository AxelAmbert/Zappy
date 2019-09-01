/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** GRAPHICAL : the all graphical client that an egg was layed
*/

#include "my_functions.h"

void tell_graphical_winning_team(server_t *server, char *winning_team)
{
    char *buffer = NULL;

    safe_strcat(&buffer, "win ");
    safe_strcat(&buffer, winning_team);
    safe_strcat(&buffer, "\n");
    tell_all_graphical_client(server, buffer);
    free(buffer);
}