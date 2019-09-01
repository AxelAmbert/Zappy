/*
** EPITECH PROJECT, 2018
** NWP_myarpspoof_2018
** File description:
** string func
*/

#include <ctype.h>

void str_replace(char *str, char to_replace, char by)
{
    for (int i = 0; str[i]; i++) {
        if (str[i] == to_replace)
            str[i] = by;
    }
}

void str_toupper(char *str)
{
    for (int i = 0; str[i]; i++) {
        str[i] = toupper(str[i]);
    }
}