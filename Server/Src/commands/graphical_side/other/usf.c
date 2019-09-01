/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** GRAPHICAL : give all usefull infos to graphical server
*/

#include "my_functions.h"

void usf(server_t *server, client_t *client, __attribute__((unused)) char *args)
{
    tell_graphical_client_useful_infos(server, client);
}