/*
** EPITECH PROJECT, 2019
** NWP_my_ftp_2018
** File description:
** libc
*/

#include <stdlib.h>
#include "my_functions.h"

char *my_strcat(const char *first, const char *second)
{
    char *
    new = malloc(sizeof(char) * (my_strlen(first) +
            my_strlen(second) + 1));
    unsigned int counter = 0;

    if (!new)
        return (NULL);
    for (unsigned int tmp = 0; first && first[tmp]; tmp++, counter++)
        new[counter] = first[tmp];
    for (unsigned int tmp = 0; second && second[tmp]; tmp++, counter++)
        new[counter] = second[tmp];
    new[counter] = '\0';
    return (new);
}

unsigned char *my_ustrcat(const unsigned char *first,
        const unsigned char *second)
{
    unsigned char *
    new = malloc(sizeof(unsigned char) * (my_strlen((char *)first) +
            my_strlen((char *)second) + 1));
    unsigned int counter = 0;

    if (!new)
        return (NULL);
    for (unsigned int tmp = 0; first && first[tmp]; tmp++, counter++)
        new[counter] = first[tmp];
    for (unsigned int tmp = 0; second && second[tmp]; tmp++, counter++)
        new[counter] = second[tmp];
    new[counter] = '\0';
    return (new);
}

void my_reallocstrcat(char **dest, const char *to_cat)
{
    char *tmp = NULL;

    if (dest[0] == NULL) {
        dest[0] = my_strcpy(to_cat);
        return;
    }
    tmp = my_strcpy(dest[0]);
    free(dest[0]);
    dest[0] = my_strcat(tmp, to_cat);
    free(tmp);
}
