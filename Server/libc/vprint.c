/*
** EPITECH PROJECT, 2019
** NWP_my_ftp_2018
** File description:
** libc
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdbool.h>
#include "my_functions.h"

void putstr(const char *str)
{
    write(1, str, my_strlen(str));
}

void vprint_special_cases(char flag, va_list *list)
{
    switch (flag) {
        case 'd':
            putnbr(va_arg(*list, int));
            break;
        case 's':
            putstr(va_arg(*list, char * ));
            break;
        case 'c':
            my_putchar(va_arg(*list, int));
            break;
        case 'u':
            uputnbr(va_arg(*list, unsigned int));
            break;
    }
}

bool its_a_special_case(const char *str, int *place, va_list *list)
{
    if (str[*place] == '%' && str[*place + 1] &&
        character_is_in_string("dsuc", &str[*place + 1]) == true) {
        vprint_special_cases(str[*place + 1], list);
        *place += 1;
        return (true);
    }
    return (false);
}

void vprint(const char *to_print, ...)
{
    va_list list;

    va_start(list, to_print);
    for (unsigned int i = 0; to_print[i]; i++) {
        if (its_a_special_case(to_print, (int *) &i, &list) == true)
            continue;
        my_putchar(to_print[i]);
    }
    va_end(list);
}
