/*
** EPITECH PROJECT, 2019
** NWP_my_ftp_2018
** File description:
** libc
*/

#include <stdlib.h>
#include <stdbool.h>
#include "my_functions.h"

int safe_getnbr(const char *to_translate)
{
    if (is_a_numeric_string(to_translate) == false)
        return (0);
    return (getnbr(to_translate));
}

int getnbr(const char *to_translate)
{
    int to_return = 0;
    unsigned int multiplicator = 1;
    int where = 0;

    if (to_translate == NULL)
        return (0);
    if (to_translate[0] == '-')
        where++;
    if (bigger(to_translate, "2147483647") == 1)
        return (to_return);
    for (unsigned int i = 0; to_translate[i] && to_translate[i] == '0';
        i++, where++);
    for (int i = my_strlen(to_translate) - 1; i >= where; i--) {
        to_return += (to_translate[i] - 48) * multiplicator;
        multiplicator *= 10;
    }
    if (to_translate[0] == '-')
        to_return *= -1;
    return (to_return);
}
