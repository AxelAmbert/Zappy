/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** GRAPHICAL : map size
*/

#include "my_functions.h"

void add_all_resources_to_buffer(char **buffer, list_t *tile)
{
    unsigned int counter = 0;
    char *nb_of_resources = NULL;

    for (type_t type = FOOD; type < PLAYER; type++) {
        counter = count(tile, &type, lambda_entity_type_cmp);
        nb_of_resources = my_getchar(counter);
        safe_strcat(buffer, nb_of_resources);
        safe_strcat(buffer, type + 1 == PLAYER ? "" : " ");
        free(nb_of_resources);
    }
}

void bct(server_t *server, client_t *client, char *args)
{
    char **pos = my_str_to_word_array(args, " ");
    int x = getnbr(pos[0]);
    int y = getnbr(pos[1]);
    char *buffer = NULL;

    free_two_dim_tab(pos);
    if (x >= server->infos->width || y >= server->infos->height)
        return;
    safe_strcat(&buffer, "bct ");
    add_all_resources_to_buffer(&buffer, server->map[y][x]);
    safe_strcat(&buffer, "\n");
    safe_send(client, buffer, my_strlen(buffer));
    free(buffer);
}
