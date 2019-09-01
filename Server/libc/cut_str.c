/*
** EPITECH PROJECT, 2019
** NWP_my_ftp_2018
** File description:
** libc
*/

#include "my_functions.h"

char *cut_str(const char *string_to_cut, const unsigned int from,
        const unsigned int to)
{
    char *new_str = NULL;
    unsigned int counter = 0;

    if (string_to_cut == NULL || my_strlen(string_to_cut) - 1 < to ||
        my_strlen(string_to_cut) - 1 <= from)
        return (NULL);
    new_str = malloc(sizeof(char) * to - from + 2);
    if (new_str == NULL)
        return (NULL);
    for (unsigned int iterator = from; iterator <= to; iterator++) {
        new_str[counter] = string_to_cut[iterator];
        counter++;
    }
    new_str[counter] = '\0';
    return (new_str);
}