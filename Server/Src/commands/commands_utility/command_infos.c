/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** get infos about commands
*/

#include "my_functions.h"

bool command_integrity_is_ok(const char *command, const char *func_name)
{
    char space = ' ';

    if (character_is_in_string(func_name, &space) == true) {
        return (true);
    }
    return (my_strlen(command) == my_strlen(func_name));
}

unsigned int arguments_start(char *func_name)
{
    for (int i = 0; i < NB_OF_COMMANDS; i++) {
        if (my_strncmp(func_name, commands_string[i],
        my_strlen(commands_string[i]), false) == true) {
            return (my_strlen(commands_string[i]));
        }
    }
    return (0);
}

int get_func_time_cost(char *func_name)
{
    for (int i = 0; i < NB_OF_COMMANDS; i++) {
        if (my_strncmp(func_name, commands_string[i],
        my_strlen(commands_string[i]), false) == true) {
            return (commands_time_cost[i]);
        }
    }
    return (0);
}

command_function_t get_func_ptr(char *func_name)
{
    for (int i = 0; i < NB_OF_COMMANDS; i++) {
        if (my_strncmp(func_name, commands_string[i],
        my_strlen(commands_string[i]), false) == true &&
        command_integrity_is_ok(commands_string[i], func_name)) {
            return (commands_functions[i]);
        }
    }
    return (failed);
}