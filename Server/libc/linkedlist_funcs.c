/*
** EPITECH PROJECT, 2019
** NWP_my_ftp_2018
** File description:
** libc
*/

#include "my_functions.h"

unsigned int length(list_t *list)
{
    return (list == NULL ? 0 : list->length);
}

node_t *get_node_by_value(list_t *list, void *value,
        bool (*cmp_func)(void *data, void *data_to_compare))
{
    node_t *tmp = NULL;

    if (list == NULL)
        return (NULL);
    for (tmp = list->begin; tmp != NULL; tmp = tmp->next) {
        if (cmp_func(tmp->data, value))
            return (tmp);
    }
    return (NULL);
}

void remove_at_index(list_t **list, unsigned int index)
{
    node_t *tmp = NULL;

    if (list == NULL || list[0] == NULL)
        return;
    tmp = list[0]->begin;
    for (uint32_t i = 0; i < index; i++) {
        tmp = tmp->next;
        if (tmp == NULL)
            return;
    }
    remove_from_linked_list(tmp, list);
}

void pop_back(list_t **list)
{
    if (list == NULL || list[0] == NULL)
        return;
    remove_at_index(list, list[0]->length - 1);
}

void pop_front(list_t **list)
{
    if (list == NULL || list[0] == NULL)
        return;
    remove_at_index(list, 0);
}