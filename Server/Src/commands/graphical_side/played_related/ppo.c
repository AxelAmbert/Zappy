/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** GRAPHICAL : print player pos/orientation
*/

#include "my_functions.h"

void add_player_infos_to_buffer(client_t *client, char **buffer)
{
    char *x = my_getchar(client->position.x);
    char *y = my_getchar(client->position.y);
    char *level = my_getchar(client->socket);

    safe_strcat(buffer, level);
    safe_strcat(buffer, " ");
    safe_strcat(buffer, x);
    safe_strcat(buffer, " ");
    safe_strcat(buffer, y);
    safe_strcat(buffer, " ");
    safe_strcat(buffer, orientation_str[client->looking_direction]);
    free(x);
    free(y);
    free(level);
}

void ppo(server_t *server, client_t *client,
        char *args)
{
    char *buffer = NULL;
    node_t *asked_client_node = get_node_by_value(server->clients,
            (void *)(intptr_t)getnbr(args), lambda_client_nb_cmp);
    client_t *real_client = NULL;

    if (asked_client_node != NULL) {
        real_client = asked_client_node->data;
        safe_strcat(&buffer, "ppo ");
        add_player_infos_to_buffer(real_client, &buffer);
        safe_strcat(&buffer, "\n");
        safe_send(client, buffer, my_strlen(buffer));
    }
    free(buffer);
}
