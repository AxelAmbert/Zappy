/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** check if argument is set somewhere
*/

#include "my_functions.h"

bool arg_isset(char *arg, const char **in)
{
    for (int i = 0; in[i]; i++) {
        if (my_strcmp(in[i], arg, false) == true)
            return (true);
    }
    return (false);
}