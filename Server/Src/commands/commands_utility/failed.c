/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** KO func, when command don't exist or command can't be executed
*/

#include "my_functions.h"

void failed(server_t *server __attribute__((unused)), client_t *client,
        char *args __attribute__((unused)))
{
    safe_send(client, "ko\n", 3);
}