/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** GRAPHICAL : players related functions
*/

#include "my_functions.h"

static void add_all_resources_infos(char **buffer, client_t *real_client)
{
    char *tmp_food = NULL;

    tmp_food = my_getchar((const int)real_client->time_unit_left / 126);
    safe_strcat(buffer, " FOOD ");
    safe_strcat(buffer, tmp_food);
    safe_strcat(buffer, " ");
    for (type_t type = LINEMATE; type < PLAYER; type += 1) {
        add_new_type_to_message(type, buffer, real_client->inventory);
        safe_strcat(buffer, type + 1 == PLAYER ? "\n" : " ");
    }
    free(tmp_food);
}

void pin(server_t *server, client_t *client, char *args)
{
    char *buffer = NULL;
    node_t *ask_client_node = get_node_by_value(server->clients,
            (void *)(intptr_t)getnbr(args), lambda_client_nb_cmp);
    client_t *real_client = NULL;
    char *tmp_nb = NULL;

    if (ask_client_node == NULL)
        return;
    real_client = ask_client_node->data;
    tmp_nb = my_getchar(real_client->socket);
    safe_strcat(&buffer, "pin ");
    safe_strcat(&buffer, tmp_nb);
    add_all_resources_infos(&buffer, real_client);
    safe_send(client, buffer, my_strlen(buffer));
    free(buffer);
    free(tmp_nb);
}