/*
** EPITECH PROJECT, 2019
** NWP_my_ftp_2018
** File description:
** libc
*/

#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include "my_functions.h"

char **strings_to_two_dim(const unsigned int nb, ...)
{
    char **array = malloc(sizeof(char *) * (nb + 1));
    unsigned int i = 0;
    va_list arg_list;

    va_start(arg_list, nb);
    for (; i < nb; i++)
        array[i] = my_strcpy(va_arg(arg_list, char * ));
    array[i] = NULL;
    va_end(arg_list);
    return (array);
}
