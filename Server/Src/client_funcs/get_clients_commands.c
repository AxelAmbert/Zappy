/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** handle clients commands
*/

#include "my_functions.h"

static inline client_resposivity_t try_to_receive_client_command(
        server_t *server, node_t *tmp_client)
{
    client_t *client = tmp_client->data;

    if (FD_ISSET(client->socket, &server->select_struct->clients_socket_set)) {
        if (interpret_command(server, tmp_client) == CLIENT_GONE) {
            return (CLIENT_GONE);
        }
        return (COMMAND);
    }
    return (NO_COMMAND);
}

void get_clients_commands(server_t *server)
{
    select(server->max_socket,
    &server->select_struct->clients_socket_set, NULL, NULL,
    &server->select_struct->timeout);
    for (node_t *tmp = begin(server->clients); tmp != NULL; next(&tmp)) {
        if (try_to_receive_client_command(server, tmp) == CLIENT_GONE) {
            RESET_COMMUNICATION_SET()
            get_clients_commands(server);
            return;
        }
    }
    RESET_COMMUNICATION_SET()
}