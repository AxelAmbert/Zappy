/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** GRAPHICAL : time related functions
*/

#include "my_functions.h"

void tg(client_t *client)
{
    safe_send(client, "tg\n", 3);
}