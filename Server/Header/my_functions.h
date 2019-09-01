/*
** EPITECH PROJECT, 2018
** my_functions.h
** File description:
** prototype of my functions
*/

#ifndef MY_FUNCTIONS_H
#define MY_FUNCTIONS_H

#define _USE_MATH_DEFINES

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>
#include <time.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdint.h>
#include <unistd.h>
#include <math.h>
#include <assert.h>

#include "linkedlist.h"
#include "my_structures.h"
#include "libc_headers.h"

bool arg_isset(char *arg, const char **in);
void set_default_argument(infos_t *infos);
void parse_arguments(infos_t **infos, int argc, const char **argv);
void free_the_server(server_t *server);
void check_for_new_client(server_t *server);
void init_server(server_t *server);
void get_clients_commands(server_t *server);
void free_if_sigint(int signal_type);
void dummy_free(void *data);
unsigned int length(list_t *list);
void failed(server_t *server, client_t *client, char *args);
bool lambda_team_cmp(void *one, void *two);
command_function_t get_func_ptr(char *func_name);
int get_func_time_cost(char *func_name);
void pop_back(list_t **list);
void pop_front(list_t **list);
void handle_clients_commands(server_t *server);
void proceed_connection(server_t *server, client_t *client, char *str);
void *get_next_entity(list_t *tile_entities, type_t type, bool reset);
void decrease_players_life(server_t *server, node_t *start);
double clock_seconds();
void free_a_client(void *data);
bool lambda_client_cmp(void *client_one, void *client_to_test);
void dead(server_t *server, client_t *client, char *args);
void transfert_a_node(list_t **old_list, list_t **new_list, node_t *node);
bool lambda_client_entity_cmp(void *entity_one, void *entity_two);
void show_map(server_t *server, client_t *client, char *args);
unsigned int arguments_start(char *func_name);

void look(server_t *server, client_t *client, char *args);
void take(server_t *server, client_t *client, char *args);
void set(server_t *server, client_t *client, char *args);
void eject(server_t *server, client_t *client, char *args);
void fork_egg(server_t *server, client_t *client,
        char *args __attribute__((unused)));
void forward(server_t *server, client_t *client, char *args);
void connect_nbr(server_t *server __attribute__((unused)),
        client_t *client, char *args);
void right(server_t *server __attribute__((unused)), client_t *client,
        char *args);
void left(server_t *server __attribute__((unused)), client_t *client,
        char *args);
void inventory(server_t *server, client_t *client, char *args);
void start_incantation(server_t *server, client_t *client, char *args);
void msz(server_t *server, client_t *client, char *args);
void bct(server_t *server, client_t *client, char *args);
void mct(server_t *server, client_t *client, char *args);
void ppo(server_t *server, client_t *client, char *args);
void plv(server_t *server, client_t *client, char *args);
void pin(server_t *server, client_t *client, char *args);
void tna(server_t *server, client_t *client, char *args);
void sgt(server_t *server, client_t *client, char *args);
void sst(server_t *server, client_t *client, char *args);
void usf(server_t *server, client_t *client, char *args);
void chat(server_t *server, client_t *client, char *args);
void scan(server_t *server, client_t *client, char *args);
void usr(server_t *server, client_t *client, char *args);
void do_incantation(server_t *server, client_t *client, char *args);
void broadcast_text(server_t *server, client_t *client, char *args);

position_t get_new_valid_positions(const position_t *one,
        const position_t *two,
        server_t *server);
position_t calculate_start_pos(client_t *client, server_t *server,
        unsigned int incursion);
position_t get_contrary(const position_t *of);
type_t str_to_type(char *args);
direction_t get_opposite(direction_t direction);
direction_t unclockwise_ninety(direction_t direction);
direction_t clockwise_ninety(direction_t direction);
void check_for_eggs_hatching(server_t *server);
void safe_strcat(char **dest, const char *src);

void test_if_clients_are_still_here(server_t *server);
void next(node_t **node);
void prev(node_t **node);
void remove_a_client_from_server(server_t *server, node_t *client_node);
void *max_value(list_t *list, bool (*func)(void *max_value, void *to_test));
bool lambda_client_max(void *one, void *two);
bool lambda_cmp_entity(void *entity, void *type);
void reset_server_max_client(server_t *server);
void extract_and_free(list_t **list, node_t *node,
        void (*free_func)(void *data));
uint32_t count(list_t *list, void *data_cmp, bool (*func)(void *value_to_test,
        void *value_node));
bool lambda_entity_cmp(void *entity_one, void *entity_two);
void safe_send(client_t *client, void *message, size_t message_len);
void push_front(list_t **list, void *data);
bool lambda_client_nb_cmp(void *client_one, void *client_two);
void add_new_type_to_message(type_t type, char **message, list_t *inventory);
bool lambda_entity_type_cmp(void *entity, void *type);
bool lambda_entity_level(void *entity, void *level);
void add_all_resources_to_buffer(char **buffer, list_t *tile);
bool check_if_incantation_can_be_done(client_t *client, list_t *tile, 
        bool check_level);
client_resposivity_t interpret_command(server_t *server,
        node_t *client_node);
void generate_random_elsewhere(server_t *server, type_t type);
bool someone_is_doing_incantation(list_t *tile);
void random_resources_generation(server_t *server);

//Functions that communicate with the graphical client
void tell_all_graphical_client(server_t *server, char *message);
void tell_graphical_new_connection(server_t *server, client_t *client);
void tell_graphical_eject(server_t *server, int_pair_t client_sockets,
        position_t *old, position_t *new);
void tell_graphical_broadcast(server_t *server, client_t *client,
        char *message);
void tell_graphical_egg_laying(server_t *server, client_t *client);
void tell_graphical_egg_hatching(server_t *server, egg_t *egg);
bool is_a_graphical_client(void *client, void *null_data);
void tell_graphical_resource_change(server_t *server, position_t pos,
        type_t type, char *action);
void tell_graphical_dead(server_t *server, client_t *dead_client);
void tell_graphical_egg_dying(server_t *server, egg_t *egg);
void add_all_map_resources_to_buffer(server_t *server, char **buffer);
void add_a_player_to_buffer(client_t *client, char **buffer);
void tell_graphical_client_useful_infos(server_t *server, client_t *client);
void add_player_infos_to_buffer(client_t *client, char **buffer);
void tell_graphical_forward(server_t *server, client_t *client,
        position_t new_pos);
void tell_graphical_incantation_start(server_t *server, client_t *client);
void tell_graphical_incantation_end(server_t *server, client_t *client);
bool game_is_finished(server_t *server);
void tell_graphical_winning_team(server_t *server, char *winning_team);
void kick(server_t *server, char *args);
void set_user(server_t *server, client_t *client, char *args);
void tg(client_t *client);

static inline v2d_t position_to_v2d(position_t p)
{
    return (v2d_t){
        .x = p.x,
        .y = p.y,
    };
}

static inline orientation_t position_to_direction (direction_t d)
{
    switch (d) {
        case UP:
            return N;
        case RIGHT:
            return E;
        case DOWN:
            return S;
        case LEFT:
            return W;
        default:
            assert(0);
            return E;
    }
}

static inline double euclidian_dist(double x1, double x2, double y1, double y2)
{
    return sqrt((pow(x2 - x1, 2)) + pow(y2 - y1, 2));
}

static inline double trig_orientation(double x, double y)
{
    double arg = atan2(y, x);

    return (arg >= 0 ? arg : (arg + _2_PI));
}

#endif
