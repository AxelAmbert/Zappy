/*
** EPITECH PROJECT, 2018
** NWP_myarpspoof_2018
** File description:
** libc
*/

#include "my_functions.h"

node_t *begin(list_t *list)
{
    if (list == NULL)
        return (NULL);
    return (list->begin);
}

node_t *end(list_t *list)
{
    if (list == NULL)
        return (NULL);
    return (list->end);
}