/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** send to the client the nbr of team unused slots
*/

#include "my_functions.h"

static int get_k_bis(v2d_t send, v2d_t recv, orientation_t o)
{
    if (o == S) {
        if (send.x == recv.x && send.y != recv.y)
            return 5;
        if (send.x != recv.x && send.y != recv.y)
            return 4;
        if (send.x != recv.x && send.y == recv.y)
            return 3;
    }
    if (o == W) {
        if (send.x == recv.x && send.y != recv.y)
            return 7;
        if (send.x != recv.x && send.y != recv.y)
            return 6;
        if (send.x != recv.x && send.y == recv.y)
            return 7;
    }
    return 0;
}

static int get_k(v2d_t send, v2d_t recv, orientation_t o)
{
    if (o == N) {
        if (send.x == recv.x && send.y != recv.y)
            return 1;
        if (send.x != recv.x && send.y != recv.y)
            return 8;
        if (send.x != recv.x && send.y == recv.y)
            return 7;
    }
    if (o == E) {
        if (send.x == recv.x && send.y != recv.y)
            return 3;
        if (send.x != recv.x && send.y != recv.y)
            return 2;
        if (send.x != recv.x && send.y == recv.y)
            return 1;
    }
    return get_k_bis(send, recv, o);
}

static char calculate_k_zeub(server_t *server, client_t *sending_client,
    client_t *receiving_client)
{
    v2d_t sending = (v2d_t){
        .x = sending_client->position.x,
        .y = sending_client->position.y
    };
    if (sending_client->position.x == receiving_client->position.x &&
        sending_client->position.y == receiving_client->position.y)
        return '0';
    return '0' + get_k(sending,
        position_to_v2d(receiving_client->position),
        position_to_direction(receiving_client->looking_direction));
}

static void add_k_to_message(char *buffer, client_t *tmp_client,
        client_t *client, server_t *server)
{
    if (tmp_client->position.x == client->position.x
    && tmp_client->position.y == client->position.y)
        buffer[8] = '0';
    else
        buffer[8] = calculate_k_zeub(server, client, tmp_client);
}

void broadcast_text(server_t *server, client_t *client, char *args)
{
    char *buffer = malloc(sizeof(char) *
            my_strlen(args) + my_strlen("message K,  \n") + 1);
    client_t *tmp_client = NULL;

    tell_graphical_broadcast(server, client, args);
    strcpy(buffer, "message K, ");
    strcat(buffer, args);
    strcat(buffer, "\n");
    for (node_t *tmp = begin(server->clients); tmp != NULL; next(&tmp)) {
        tmp_client = tmp->data;
        if (tmp_client == client || tmp_client->is_graphical == true ||
            tmp_client->is_connected == false)
            continue;
        add_k_to_message(buffer, tmp_client, client, server);
        safe_send(tmp_client, buffer, my_strlen(buffer));
    }
    safe_send(client, "ok\n", 3);
    free(buffer);
}
