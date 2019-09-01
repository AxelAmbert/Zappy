/*
** EPITECH PROJECT, 2019
** NWP_my_ftp_2018
** File description:
** libc
*/

#include <stdlib.h>
#include <stdarg.h>
#include "my_functions.h"

char *my_strncat(const int unsigned number, ...)
{
    char *new_str = NULL;
    unsigned int i = 0;
    va_list arg_list;

    va_start(arg_list, number);
    for (; i < number; i++)
        my_reallocstrcat(&new_str, va_arg(arg_list, char * ));
    return (new_str);
}

void my_reallocstrncat(const unsigned number, char **to_realloc, ...)
{
    unsigned int i = 0;
    va_list arg_list;

    if (to_realloc[0] != NULL)
        free(to_realloc[0]);
    va_start(arg_list, to_realloc);
    for (; i < number; i++)
        my_reallocstrcat(to_realloc, va_arg(arg_list, char * ));
}
