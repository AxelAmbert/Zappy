/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** GRAPHICAL : the all graphical client that an egg was hatched
*/

#include "my_functions.h"

static void release_resources(char *buffer, char *egg_nb)
{
    free(buffer);
    free(egg_nb);
}

void tell_graphical_egg_dying(server_t *server, egg_t *egg)
{
    char *buffer = NULL;
    char *egg_nb = NULL;
    char *tmp = NULL;

    if (count(server->clients, NULL, is_a_graphical_client) == 0)
        return;
    egg_nb = my_getchar(egg->egg_nb);
    safe_strcat(&buffer, "edi ");
    safe_strcat(&buffer, egg_nb);
    safe_strcat(&buffer, " ");
    tmp = my_getchar(egg->position.x);
    safe_strcat(&buffer, tmp);
    free(tmp);
    safe_strcat(&buffer, " ");
    tmp = my_getchar(egg->position.y);
    safe_strcat(&buffer, tmp);
    free(tmp);
    safe_strcat(&buffer, "\n");
    tell_all_graphical_client(server, buffer);
    release_resources(buffer, egg_nb);
}