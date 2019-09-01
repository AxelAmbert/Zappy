/*
** EPITECH PROJECT, 2019
** NWP_my_ftp_2018
** File description:
** libc
*/

#include "my_functions.h"

void *max_value(list_t *list, bool (*func)(void *max_value, void *to_test))
{
    void *max = NULL;

    if (list == NULL)
        return (NULL);
    max = list->begin->data;
    for (node_t *tmp = begin(list); tmp != NULL; next(&tmp)) {
        if (func(max, tmp->data) == false) {
            max = tmp->data;
        }
    }
    return (max);
}

uint32_t count(list_t *list, void *data_cmp, bool (*func)(void *value_to_test,
        void *value_node))
{
    uint32_t counter = 0;

    for (node_t *tmp = begin(list); tmp; next(&tmp)) {
        if (func(data_cmp, tmp->data) == true)
            counter++;
    }
    return (counter);
}

void push_front(list_t **list, void *data)
{
    node_t *tmp = calloc(sizeof(*tmp), 1);

    tmp->data = data;
    if (list[0] == NULL)
        list[0] = calloc(sizeof(list_t), 1);
    if (list[0]->length == 0) {
        list[0]->begin = tmp;
        list[0]->end = tmp;
    } else {
        list[0]->begin->prev = tmp;
        tmp->next = list[0]->begin;
        list[0]->begin = tmp;
    }
    list[0]->length += 1;
}
