/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** handle clients commands
*/

#include "my_functions.h"

static void do_client_command(server_t *server, client_t *client,
        command_t *first_command)
{
    if (client->is_graphical != true &&
    client->time_unit_left <= 0) {
        dead(server, client, NULL);
        return;
    }
    first_command->command(server, client, first_command->args);
    pop_front(&client->command_queue);
    if (length(client->command_queue) != 0) {
        first_command = data_at_index(client->command_queue, 0);
        first_command->start_time = clock_seconds();
    }
}

void check_if_command_is_ready(server_t *server, client_t *client)
{
    command_t *first_command = data_at_index(client->command_queue, 0);
    double elapsed_time = 0;

    if (first_command == NULL)
        return;
    elapsed_time = clock_seconds() - first_command->start_time;
    if (elapsed_time >= first_command->command_time)
        do_client_command(server, client, first_command);
}

void handle_clients_commands(server_t *server)
{
    for (node_t *tmp = begin(server->clients); tmp != NULL; next(&tmp))
        check_if_command_is_ready(server, tmp->data);
}