/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** interpret clients commands
*/

#include "my_functions.h"

static void start_first_command(list_t *command_list)
{
    command_t *command = data_at_index(command_list, 0);

    command->start_time = clock_seconds();
}

static void add_command_to_command_queue(server_t *server, client_t *client,
        char *client_message)
{
    command_function_t command_func = get_func_ptr(client_message);
    command_t *new_command = calloc(sizeof(*new_command), 1);

    new_command->command = command_func;
    new_command->command_time = (double)get_func_time_cost(client_message) /
                                server->infos->freq;
    strcpy(new_command->args,
            client_message + arguments_start(client_message));
    append(&client->command_queue, new_command);
    if (client->command_queue->length == 1)
        start_first_command(client->command_queue);
}

void add_all_commands(server_t *server, client_t *client, char **all_commands)
{
    for (uint32_t i = 0; all_commands && all_commands[i] &&
    (length(client->command_queue) < 10 || client->is_graphical); i++) {
        if (client->is_connected == false)
            proceed_connection(server, client, all_commands[i]);
        else
            add_command_to_command_queue(server, client, all_commands[i]);
    }
    free_two_dim_tab(all_commands);
}

client_resposivity_t interpret_command(server_t *server,
        node_t *client_node)
{
    ssize_t nb_of_byte_read = 0;
    char tmp_message[TCP_MESSAGE_MAX_LENGTH];
    client_t *client = client_node->data;
    char **all_commands = NULL;

    nb_of_byte_read =
            recv(client->socket, tmp_message, TCP_MESSAGE_MAX_LENGTH, 0);
    if (nb_of_byte_read <= 0) {
        tell_graphical_dead(server, client_node->data);
        remove_a_client_from_server(server, client_node);
        return (CLIENT_GONE);
    }
    if (length(client->command_queue) == 10)
        return (NO_COMMAND);
    tmp_message[nb_of_byte_read] = '\0';
    all_commands = my_str_to_word_array(tmp_message, "\n");
    add_all_commands(server, client, all_commands);
    return (COMMAND);
}