/*
** EPITECH PROJECT, 2019
** NWP_my_ftp_2018
** File description:
** libc
*/

#include <stdlib.h>
#include <stdbool.h>
#include "my_functions.h"

bool character_is_in_string(const char *in_string, const char *character)
{
    if (*character == '\0')
        return (false);
    for (unsigned int iterator = 0; in_string[iterator]; iterator++) {
        if (in_string[iterator] == *character)
            return (true);
    }
    return (false);
}

bool str_in_str(const char *to_find, const char *in)
{
    unsigned int len = my_strlen(to_find);
    unsigned int occurencies = 0;

    if (len < my_strlen(in) || to_find == NULL || in == NULL)
        return (false);
    for (unsigned int i = 0; in[i]; i++) {
        if (to_find[occurencies] == in[i])
            occurencies++;
        else
            occurencies = 0;
        if (occurencies == len)
            return (true);
    }
    return (false);
}

unsigned int find_occurencies(char *in_str, char *to_find)
{
    unsigned int occurencies = 0;

    if (in_str == NULL || to_find == NULL)
        return (occurencies);
    for (int i = 0; in_str[i]; i++) {
        if (character_is_in_string(to_find, &in_str[i]) == true)
            occurencies++;
    }
    return (occurencies);
}
