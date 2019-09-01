/*
** EPITECH PROJECT, 2019
** NWP_my_ftp_2018
** File description:
** libc
*/

#include <stdlib.h>
#include <stdbool.h>
#include "my_functions.h"

bool is_a_numeric_string(char const *string)
{
    for (int i = 0; string[i]; i++) {
        if (string[i] < 48 || string[i] > 57)
            return (false);
    }
    return (true);
}

char *copy_after_x_character(const char *str, const char charac)
{
    char *new_str = NULL;
    unsigned int i = 0;

    if (str == NULL)
        return (NULL);
    while (str[i] && str[i] == charac)
        i++;
    if (!str[i])
        return (NULL);
    new_str = cut_str(str, i, my_strlen(str) - 1);
    return (new_str);
}

unsigned int bigger(const char *one, const char *two)
{
    unsigned int one_len = 0;
    unsigned int two_len = 0;

    for (; one && one[0] && one[0] == '0'; one++);
    for (; two && two[0] && two[0] == '0'; two++);
    one_len = my_strlen(one);
    two_len = my_strlen(two);
    if (one_len > two_len)
        return (1);
    else if (two_len > one_len)
        return (2);
    if (one_len == 0 && two_len == 0)
        return (0);
    for (int i = 0; one[i] && two[i]; i++) {
        if (one[i] > two[i])
            return (1);
        else if (two[i] > one[i])
            return (2);
    }
    return (0);
}
