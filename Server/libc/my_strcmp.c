/*
** EPITECH PROJECT, 2019
** NWP_my_ftp_2018
** File description:
** libc
*/

#include <stdbool.h>
#include <stdlib.h>
#include "my_functions.h"

bool my_strcmp(const char *first, const char *two, bool case_sensitive)
{
    if (first == NULL || two == NULL)
        return (false);
    if (my_strlen(first) != my_strlen(two))
        return (false);
    for (unsigned int i = 0; first[i]; i++) {
        if (first[i] != two[i] && (case_sensitive == false ||
        case_sensitive_validity(first[i], two[i]) != true))
            return (false);
    }
    return (true);
}
