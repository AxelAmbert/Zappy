//
// Created by axel on 5/27/19.
//

#include "my_functions.h"

void reset_server_max_client(server_t *server)
{
    client_t *client = max_value(server->clients, lambda_client_max);

    if (client == NULL)
        server->max_socket = 0;
    else
        server->max_socket = client->socket + server->connection_socket + 1;
}

static void destroy_non_used_eggs(server_t *server, client_t *client)
{
    egg_t *egg = NULL;

    if (client->is_connected == false || client->is_graphical == true)
        return;
    for (node_t *tmp = begin(client->team->eggs); tmp != NULL; next(&tmp)) {
        egg = tmp->data;
        if (egg->client == client) {
            tell_graphical_egg_dying(server, egg);
            client->team->places_left -= egg->is_hatched;
            remove_from_linked_list(tmp, &client->team->eggs);
            destroy_non_used_eggs(server, client);
            return;
        }
    }
}

void remove_a_client_from_server(server_t *server, node_t *client_node)
{
    client_t *client = client_node->data;

    close(client->socket);
    shutdown(client->socket, SHUT_RDWR);
    destroy_non_used_eggs(server, client);
    FD_CLR(client->socket, &server->select_struct->clients_socket_set_save);
    FD_CLR(client->socket, &server->select_struct->clients_socket_set);
    if (client->is_connected == true && client->is_graphical != true) {
        server->nb_of_non_graphical_client -= 1;
        remove_by_value(&server->map[client->position.y][client->position.x],
                client, lambda_client_entity_cmp);
        client->team->places_left += 1;
    }
    extract_and_free(&server->clients, client_node, free_a_client);
    reset_server_max_client(server);
    RESET_COMMUNICATION_SET()
}
