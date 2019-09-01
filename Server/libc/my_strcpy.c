/*
** EPITECH PROJECT, 2019
** NWP_my_ftp_2018
** File description:
** libc
*/

#include <stdlib.h>
#include "my_functions.h"

char *my_strcpy(const char *to_copy)
{
    char * new = malloc(sizeof(char) * my_strlen(to_copy) + 1);
    unsigned int i = 0;

    if (new == NULL || to_copy == NULL) {
        free(new);
        return (NULL);
    }
    for (; to_copy[i]; i++)
        new[i] = to_copy[i];
    new[i] = '\0';
    return (new);
}

void my_reallocstrcpy(char **dest, const char *to_copy)
{
    if (dest[0] != NULL)
        free(dest[0]);
    dest[0] = my_strcpy(to_copy);
}