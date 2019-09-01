/*
** EPITECH PROJECT, 2019
** NWP_my_ftp_2018
** File description:
** libc
*/

#include "my_functions.h"

unsigned int tab_len(const char **tab)
{
    unsigned int i = 0;

    if (tab == NULL)
        return (0);
    while (tab[i])
        i++;
    return (i);
}

void free_two_dim_tab(char **tab)
{
    unsigned int i = 0;

    if (tab == NULL)
        return;
    for (; tab[i]; i++)
        free(tab[i]);
    free(tab[i]);
    free(tab);
}