/*
** EPITECH PROJECT, 2018
** my_functions.h
** File description:
** prototype of my functions
*/

#ifndef MY_STURCTURES_H
#define MY_STURCTURES_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/select.h>

#include "linkedlist.h"


typedef bool operation;
#define SUCCESS true
#define FAILURE false
#define MAX_BACKLOG 128
#define MAX_PORT_NB 65535
#define FILE_FUNC __FILE__, __FUNCTION__
#define FILE_FUNC_LINE __FILE__, __FUNCTION__, __LINE__
#define NB_OF_CLIENTS (server->clients ? server->clients->length : 0)
#define TCP_MESSAGE_MAX_LENGTH 1500
#define END_OF_FREE_LIST NULL
#define SET_FREE_LIST NULL
#define NB_OF_COMMANDS 25
#define RESET_CONNECTION_SET() server->select_struct->connection_socket_set = \
    server->select_struct->connection_socket_set_save;
#define RESET_TIMEOUT() server->select_struct->timeout.tv_usec = 1000; \
    server->select_struct->timeout.tv_sec = 0;
#define RESET_COMMUNICATION_SET() \
    server->select_struct->clients_socket_set = \
    server->select_struct->clients_socket_set_save;
//#define TELNET_COMPATIBILITY

#define _PI ((double)M_PI)
#define  _2_PI (((double)_PI) * ((double)2.0))
#define _PI_4 (((double)_PI) / ((double)4.0))
#define _PI_8 (((double)_PI) / ((double)8.0))

typedef enum direction_looking_s
{
    UP, RIGHT, DOWN, LEFT
}direction_t;

typedef enum {
    E = 0,
    S = 2,
    W = 4,
    N = 6
} orientation_t;

typedef struct team_s
{
    unsigned int places_left;
    char *team_name;
    list_t *eggs;
    uint32_t level_six_members;
}team_t;

typedef struct existence_time_s
{
    double start_time;
    double time_elapsed_since_life_decrease;
}existence_time_t;

typedef struct free_func_ptr_and_data_s
{
    void (*free_ptr)(void *data_to_free);
    void *data_to_free;
}free_func_ptr_and_data_t;

typedef struct
{
    double x;
    double y;
} v2d_t;

typedef struct direction_values_s
{
    int x;
    int y;
}position_t;

typedef struct client_s
{
    int socket;
    list_t *command_queue;
    list_t *inventory;
    list_t *answer_queue;
    existence_time_t existence_time;
    team_t *team;
    bool is_connected;
    bool is_graphical;
    double time_unit_left;
    direction_t looking_direction;
    position_t position;
    unsigned level;
    bool incantation_initiator;
    char *username;
}client_t;

typedef struct __attribute__((packed)) infos_s
{
    ssize_t port;
    ssize_t width;
    ssize_t height;
    ssize_t nb_of_client_in_a_team;
    ssize_t freq;
    list_t *teams;
}infos_t;

typedef struct select_struct_s
{
    fd_set clients_socket_set;
    fd_set connection_socket_set;
    fd_set clients_socket_set_save;
    fd_set connection_socket_set_save;
    struct timeval timeout;
}select_struct_t;

typedef struct server_s
{
    list_t ***map;
    list_t *clients;
    list_t *eggs;
    infos_t *infos;
    int connection_socket;
    select_struct_t *select_struct;
    struct sockaddr_in *socket_address;
    bool client_removed;
    int max_socket;
    double time_alive;
    uint32_t nb_of_non_graphical_client;
}server_t;

typedef struct command_s
{
    void (*command)(server_t *server, client_t *client, char *args);
    double command_time;
    double start_time;
    char args[TCP_MESSAGE_MAX_LENGTH];
}command_t;

typedef enum type_s
{
    NOT_KNOWN = -1, FOOD = 0, LINEMATE = 1, DERAUMERE = 2, SIBUR = 3,
    MENDIANE = 4, PHIRAS = 5, THYSTAME = 6, PLAYER = 7, END = 8
}type_t;

typedef enum client_responsivity_s
{
    NO_COMMAND, COMMAND, CLIENT_GONE
}client_resposivity_t;

typedef struct entity_s
{
    void *data;
    type_t type;
}entity_t;

typedef struct egg_s
{
    double start_time;
    team_t *associated_team;
    client_t *client;
    uint32_t egg_nb;
    bool is_hatched;
    position_t position;
}egg_t;

typedef struct bufferised_message_s
{
    void *message;
    size_t len;
}bufferised_message_t;

typedef struct int_pair_s
{
    int one;
    int two;
}int_pair_t;

typedef void (*command_function_t)(server_t *, client_t *, char *);

//const extern void (*commands_functions[21])(server_t *server,
//        client_t *client, char *args);
extern const command_function_t commands_functions[NB_OF_COMMANDS];
extern const char *commands_string[NB_OF_COMMANDS];
extern const int commands_time_cost[NB_OF_COMMANDS];
extern const position_t moving_positions[4];
extern const char *type_str[8];
extern const uint32_t elevation_requirement[7][9];
extern const char *orientation_str[4];
#endif