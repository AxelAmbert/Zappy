/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** Functions about entities
*/

#include "my_functions.h"

type_t str_to_type(char *args)
{
    for (type_t type = FOOD; type < PLAYER; type += 1) {
        if (my_strcmp(args, type_str[type], true) == true) {
            return (type);
        }
    }
    return (NOT_KNOWN);
}