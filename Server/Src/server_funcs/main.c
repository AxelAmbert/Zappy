/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** main file of the zappy server
*/

#include <signal.h>
#include "my_functions.h"
#include <time.h>

void zappy_server(server_t *server)
{
    volatile bool until_end = true;

    while (until_end) {
        check_for_new_client(server);
        if (length(server->clients) != 0) {
            get_clients_commands(server);
            handle_clients_commands(server);
            decrease_players_life(server, NULL);
            random_resources_generation(server);
        }
        if (game_is_finished(server)) {
            exit_error("SUCCESS : ENDGAME\n");
        }
        check_for_eggs_hatching(server);
        server->time_alive = clock_seconds();
    }
}

int main(int argc, const char **argv)
{
    server_t *server = NULL;

    srand(time(NULL));
    signal(SIGINT, free_if_sigint);
    server = calloc(sizeof(*server), 1);
    if (server == NULL)
        exit_error("CRITICAL : Server allocation failed\n");
    parse_arguments(&server->infos, argc - 1, argv + 1);
    init_server(server);
    exit_error(SET_FREE_LIST, free_the_server, server, END_OF_FREE_LIST);
    zappy_server(server);
}
