/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** send to the client the nbr of team unused slots
*/

#include "my_functions.h"

void connect_nbr(server_t *server __attribute__((unused)), client_t *client,
        char *args __attribute__((unused)))
{
    char *nb_of_places_left = my_getchar(client->team->places_left);

    my_reallocstrcat(&nb_of_places_left, "\n");
    safe_send(client, nb_of_places_left, my_strlen(nb_of_places_left));
    free(nb_of_places_left);
}
