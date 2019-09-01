/*
** EPITECH PROJECT, 2019
** NWP_my_ftp_2018
** File description:
** libc
*/

#include "my_functions.h"

void next(node_t **node)
{
    if (node == NULL || node[0] == NULL)
        return;
    node[0] = node[0]->next;
}

void prev(node_t **node)
{
    if (node == NULL || node[0] == NULL)
        return;
    node[0] = node[0]->prev;
}