/*
** EPITECH PROJECT, 2019
** NWP_my_ftp_2018
** File description:
** libc
*/

#include <stdbool.h>
#include <stdlib.h>
#include "my_functions.h"

unsigned int is_lower_upper(const char to_verify)
{
    if (to_verify >= 97 && to_verify <= 122)
        return (1);
    else if (to_verify >= 65 && to_verify <= 90)
        return (2);
    return (0);
}

bool is_numerical(const char to_verify)
{
    if (to_verify >= 48 && to_verify <= 57)
        return (true);
    return (false);
}

bool is_alphabetical(const char to_verify)
{
    if (to_verify >= 65 && to_verify <= 90)
        return (true);
    else if (to_verify >= 97 && to_verify <= 122)
        return (true);
    return (false);
}

bool is_alphanumerical(const char to_verify)
{
    if (is_alphabetical(to_verify) || is_numerical(to_verify))
        return (true);
    return (false);
}

bool case_sensitive_validity(const char first, const char two)
{
    if (is_alphabetical(first) != true || is_alphabetical(two) != true)
        return (false);
    if (first - 32 == two || first + 32 == two)
        return (true);
    return (false);
}
