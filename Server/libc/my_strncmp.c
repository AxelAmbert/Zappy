/*
** EPITECH PROJECT, 2019
** NWP_my_ftp_2018
** File description:
** libc
*/

#include <stdbool.h>
#include <stdlib.h>
#include "my_functions.h"

bool my_strncmp(const char *first, const char *two, unsigned int max,
        bool case_sensitive)
{
    if (first == NULL || two == NULL)
        return (false);
    for (unsigned int i = 0; i < max; i++) {
        if (first[i] == '\0' && two[i] == '\0')
            return (true);
        else if (first[i] == '\0' || two[i] == '\0')
            return (false);
        if (first[i] != two[i] && (case_sensitive == false ||
        case_sensitive_validity(first[i], two[i]) != true))
            return (false);
    }
    return (true);
}
