/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** GRAPHICAL : set graphical player its in-game username
*/

#include "my_functions.h"


void usr(server_t *server __attribute__((unused)), client_t *client, char *args)
{
    char *random = NULL;
    char *buffer = NULL;

    if (my_strlen(args) <= 0) {
        random = my_getchar(abs(rand() % 1000));
        safe_strcat(&buffer, "USR_");
        safe_strcat(&buffer, random);
        free(random);
        client->username = buffer;
    } else {
        client->username = my_strcpy(args);
    }
}