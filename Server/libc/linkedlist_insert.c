/*
** EPITECH PROJECT, 2019
** NWP_my_ftp_2018
** File description:
** libc
*/


#include "my_functions.h"

static void add_node(list_t **list, node_t *new_node, node_t *tmp, void *data)
{
    new_node = calloc(sizeof(*new_node), 1);
    new_node->data = data;
    new_node->next = tmp->next;
    tmp->next = new_node;
    new_node->prev = tmp;
    if (new_node->next == NULL)
        list[0]->end = new_node;
}

void insert_at_index(list_t **list, void *data, uint32_t index)
{
    node_t *tmp = NULL;
    node_t *new_node = NULL;

    if (length(list[0]) == 0) {
        append(list, data);
        return;
    }
    tmp = list[0]->begin;
    for (uint32_t i = 0; i + 1 < index; i++) {
        if (tmp != NULL && tmp->next == NULL)
            break;
        next(&tmp);
    }
    if (tmp == NULL)
        return;
    add_node(list, new_node, tmp, data);
}