/*
** EPITECH PROJECT, 2019
** NWP_my_ftp_2018
** File description:
** libc
*/

#include <stdlib.h>
#include "my_functions.h"

unsigned int my_strlen(const char *str)
{
    unsigned int i = 0;

    if (str == NULL)
        return (0);
    for (; str[i]; i++);
    return (i);
}
