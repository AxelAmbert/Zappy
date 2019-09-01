/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** GRAPHICAL : players related functions
*/

#include "my_functions.h"

void add_a_player_to_buffer(client_t *client, char **buffer)
{
    char *level = my_getchar(client->level);
    char *nb = my_getchar(client->socket);

    safe_strcat(buffer, nb);
    safe_strcat(buffer, " ");
    safe_strcat(buffer, level);
    free(level);
    free(nb);
}

void plv(server_t *server, client_t *client, char *args)
{
    char *buffer = NULL;
    char *level = NULL;
    node_t *asked_client_node = get_node_by_value(server->clients,
            (void *)(intptr_t)getnbr(args), lambda_client_nb_cmp);
    client_t *real_client = NULL;

    if (asked_client_node != NULL) {
        real_client = asked_client_node->data;
        if (client->is_graphical == false) {
            safe_strcat(&buffer, "plv ");
            add_a_player_to_buffer(real_client, &buffer);
            safe_strcat(&buffer, "\n");
            safe_send(client, buffer, my_strlen(buffer));
        }
    }
    free(buffer);
    free(level);
}