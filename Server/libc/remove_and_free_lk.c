/*
** EPITECH PROJECT, 2018
** NWP_myarpspoof_2018
** File description:
** libc
*/

#include "my_functions.h"

void extract_and_free(list_t **list, node_t *node,
        void (*free_func)(void *data))
{
    void *data = NULL;

    if (list == NULL || list[0] == NULL || node == NULL)
        return;
    data = node->data;
    extract_a_node(list, node);
    free_func(data);
    free(node);
}