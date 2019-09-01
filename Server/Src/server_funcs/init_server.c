/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** init the server
*/

#include "my_functions.h"


inline static void fill_tile_randomly(list_t **list)
{
    entity_t *new_entity = NULL;
    uint32_t random = rand();

    for (type_t type = FOOD; type != PLAYER; type += 1) {
        if ((type == FOOD && random % 4 == 0) || (random % 5 == 0)) {
            new_entity = calloc(sizeof(*new_entity), 1);
            new_entity->type = type;
            append(list, new_entity);
        }
        random = rand();
    }
}

inline static void init_server_map(server_t *server)
{
    server->map = calloc(sizeof(list_t *), server->infos->height);

    for (unsigned int i = 0; i < server->infos->height; i++)
        server->map[i] = calloc(sizeof(list_t *), server->infos->width);
    for (unsigned int y = 0; y < server->infos->height; y++) {
        for (unsigned int x = 0; x < server->infos->width; x++) {
            fill_tile_randomly(&server->map[y][x]);
        }
    }
}

static void bind_server(server_t *server)
{
    struct sockaddr_in *sockaddr = calloc(sizeof(*sockaddr), 1);

    if (sockaddr == NULL)
        exit_error("CRITICAL : Failed to allocate socket address\n");
    server->socket_address = sockaddr;
    sockaddr->sin_port = htons((uint16_t)server->infos->port);
    sockaddr->sin_addr.s_addr = INADDR_ANY;
    sockaddr->sin_family = AF_INET;
    if (bind(server->connection_socket,
    (struct sockaddr *)sockaddr, sizeof(*sockaddr)) < 0) {
        exit_error("CRITICAL : FAILED TO BIND THE SERVER\n");
    }
    if (listen(server->connection_socket, MAX_BACKLOG) < 0) {
        exit_error("CRITICAL : FAILED TO LISTEN ON THE SOCKET\n");
    }
}

void init_server(server_t *server)
{
    int tmp = 1;

    server->connection_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server->connection_socket == -1) {
        exit_error("CRITICAL : CAN'T CREATE CONNECTION SOCKET\n");
    }
    setsockopt(server->connection_socket, SOL_SOCKET, SO_REUSEADDR, &tmp,
            sizeof(int));
    server->select_struct = calloc(sizeof(*server->select_struct), 1);
    FD_ZERO(&server->select_struct->clients_socket_set);
    FD_ZERO(&server->select_struct->connection_socket_set);
    FD_ZERO(&server->select_struct->clients_socket_set_save);
    FD_ZERO(&server->select_struct->connection_socket_set_save);
    FD_SET(server->connection_socket,
            &server->select_struct->connection_socket_set_save);
    RESET_CONNECTION_SET();
    server->select_struct->timeout.tv_usec = 1000;
    server->select_struct->timeout.tv_sec = 0;
    bind_server(server);
    init_server_map(server);
}