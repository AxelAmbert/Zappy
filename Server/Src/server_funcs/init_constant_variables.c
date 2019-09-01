/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** init the server
*/

#include "my_functions.h"

const char *commands_string[NB_OF_COMMANDS] = {"Forward", "Right", "Left", "Look",
    "Inventory", "Broadcast ",
    "Connect_nbr", "Fork", "Eject",
    "Take ", "Set ", "Incantation",
    "msz", "bct ", "mct", "tna",
    "ppo ", "plv ", "pin ", "sgt", "sst ",
    "usf", "chat ", "scan"};

const int commands_time_cost[NB_OF_COMMANDS] =
        {7, 7, 7, 7, 1, 7, 0, 42, 7, 7, 7, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

const command_function_t commands_functions[NB_OF_COMMANDS] = {
        forward,
        right,
        left,
        look,
        inventory,
        broadcast_text,
        connect_nbr,
        fork_egg,
        eject,
        take,
        set,
        start_incantation,
        msz,
        bct,
        mct,
        tna,
        ppo,
        plv,
        pin,
        sgt,
        sst,
        usf,
        chat,
        scan
};

const position_t moving_positions[4] =
        {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};

const char *type_str[8] = {"food", "linemate", "deraumere", "sibur",
    "mendiane", "phiras", "thystame", "player"};

const uint32_t elevation_requirement[7][9] =
        {
                {0, 1, 0, 0, 0, 0, 0, 1, 1},
                {0, 1, 1, 1, 0, 0, 0, 2, 2},
                {0, 2, 0, 1, 0, 2, 0, 2, 3},
                {0, 1, 1, 2, 0, 1, 0, 4, 4},
                {0, 1, 2, 1, 3, 0, 0, 4, 5},
                {0, 1, 2, 3, 0, 1, 0, 6, 6},
                {0, 2, 2, 2, 2, 2, 1, 6, 7}
        };

const char *orientation_str[4] = {"UP", "RIGHT", "DOWN", "LEFT"};
