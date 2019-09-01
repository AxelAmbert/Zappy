/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** GRAPHICAL : the all graphical client that an egg was hatched
*/

#include "my_functions.h"

static inline void do_command(server_t *server, egg_t *egg)
{
    char *buffer = NULL;
    char *egg_nb = my_getchar(length(server->eggs));
    char *x = my_getchar(egg->position.x);
    char *y = my_getchar(egg->position.y);

    safe_strcat(&buffer, "eht ");
    safe_strcat(&buffer, egg_nb);
    safe_strcat(&buffer, " ");
    safe_strcat(&buffer, x);
    safe_strcat(&buffer, " ");
    safe_strcat(&buffer, y);
    safe_strcat(&buffer, "\n");
    tell_all_graphical_client(server, buffer);
    free(buffer);
    free(egg_nb);
    free(x);
    free(y);
}

void tell_graphical_egg_hatching(server_t *server, egg_t *egg)
{
    if (count(server->clients, NULL, is_a_graphical_client) == 0)
        return;
    do_command(server, egg);
}