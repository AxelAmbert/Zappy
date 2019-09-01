/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** check if a connection is a available
*/

#include "my_functions.h"

static void accept_new_client(server_t *server)
{
    client_t *new_client = calloc(sizeof(*new_client), 1);
    int flag = 1;

    if (new_client == NULL)
        exit_error("Failed to malloc a new client %s\n", __func__);
    new_client->socket = accept(server->connection_socket, NULL, NULL);
    if (new_client->socket == -1)
        exit_error("Failed to accept a new client -> %s\n", strerror(errno));
    append(&server->clients, new_client);
    reset_server_max_client(server);
    FD_SET(new_client->socket,
        &server->select_struct->clients_socket_set_save);
    setsockopt(new_client->socket, SOL_SOCKET, SO_KEEPALIVE,
            &flag, sizeof(int));
    safe_send(new_client, "WELCOME\n", strlen("WELCOME\n"));
    RESET_CONNECTION_SET()
}

inline __attribute__((always_inline))

void check_for_new_client(server_t *server)
{
    int new_client = 0;

    new_client = select(server->connection_socket + 1,
            &server->select_struct->connection_socket_set,
            NULL, NULL, &server->select_struct->timeout);
    if (new_client > 0)
        accept_new_client(server);
    RESET_CONNECTION_SET()
    RESET_TIMEOUT()
}