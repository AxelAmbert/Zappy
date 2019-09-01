/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** GRAPHICAL : tell all graphical clients that clients are ejected
*/

#include "my_functions.h"
//5 4-3 4-5

static void add_player_numbers(char **buffer, int_pair_t client_sockets)
{
    char *player_nb = my_getchar(client_sockets.one);
    char *other_player = my_getchar(client_sockets.two);

    safe_strcat(buffer, other_player);
    safe_strcat(buffer, " ");
    safe_strcat(buffer, player_nb);
    safe_strcat(buffer, " ");
    free(player_nb);
    free(other_player);
}

static void add_new_and_old_x_y(char **buffer, position_t *old,
        position_t *new)
{
    char *x_old = my_getchar(old->x);
    char *y_old = my_getchar(old->y);
    char *x_new = my_getchar(new->x);
    char *y_new = my_getchar(new->y);

    safe_strcat(buffer, x_old);
    safe_strcat(buffer, "-");
    safe_strcat(buffer, y_old);
    safe_strcat(buffer, " ");
    safe_strcat(buffer, x_new);
    safe_strcat(buffer, "-");
    safe_strcat(buffer, y_new);
    free(x_old);
    free(y_old);
    free(y_new);
    free(x_new);
}

void tell_graphical_eject(server_t *server, int_pair_t client_sockets,
        position_t *old, position_t *new)
{
    char *buffer = NULL;

    if (count(server->clients, NULL, is_a_graphical_client) == 0)
        return;
    safe_strcat(&buffer, "pex ");
    add_player_numbers(&buffer, client_sockets);
    add_new_and_old_x_y(&buffer, old, new);
    safe_strcat(&buffer, "\n");
    tell_all_graphical_client(server, buffer);
    free(buffer);
}