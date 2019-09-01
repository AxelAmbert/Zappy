/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** GRAPHICAL : the all graphical client that an egg was layed
*/

#include "my_functions.h"

/*pdr {player nb} {resource pos {x y}} {RESOURCE_STR}*/

static void do_command(server_t *server, position_t pos, type_t type,
        char *action)
{
    char *x = my_getchar(pos.x);
    char *y = my_getchar(pos.y);
    char *buffer = NULL;

    safe_strcat(&buffer, action);
    safe_strcat(&buffer, " ");
    safe_strcat(&buffer, x);
    safe_strcat(&buffer, " ");
    safe_strcat(&buffer, y);
    safe_strcat(&buffer, " ");
    safe_strcat(&buffer, type_str[type]);
    safe_strcat(&buffer, "\n");
    tell_all_graphical_client(server, buffer);
    free(x);
    free(y);
    free(buffer);
}

void tell_graphical_resource_change(server_t *server, position_t pos,
        type_t type, char *action)
{
    if (count(server->clients, NULL, is_a_graphical_client) == 0)
        return;
    do_command(server, pos, type, action);
}
