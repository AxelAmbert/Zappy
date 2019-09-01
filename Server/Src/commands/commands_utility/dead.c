/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** Player is dead, he is kicked from the server
*/

#include "my_functions.h"

static void remove_all_client_eggs_from_list(server_t *server, client_t *client)
{
    egg_t *tmp_egg = NULL;

    for (node_t *tmp = begin(server->eggs); tmp; next(&tmp)) {
        tmp_egg = tmp->data;
        if (tmp_egg->client == client) {
            remove_from_linked_list(tmp, &server->eggs);
            remove_all_client_eggs_from_list(server, client);
            return;
        }
    }
}

void dead(server_t *server, client_t *client,
        char *args __attribute__((unused)))
{
    node_t *tmp = get_node_by_value(server->clients, client, lambda_client_cmp);

    remove_all_client_eggs_from_list(server, client);
    safe_send(client, "dead\n", 5);
    FD_CLR(client->socket, &server->select_struct->clients_socket_set_save);
    FD_CLR(client->socket, &server->select_struct->clients_socket_set);
    tell_graphical_dead(server, client);
    remove_a_client_from_server(server, tmp);

}