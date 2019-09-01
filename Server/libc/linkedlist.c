/*
** EPITECH PROJECT, 2019
** NWP_my_ftp_2018
** File description:
** libc
*/

#include "linkedlist.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

void list_for_each(list_t *list, void (func)(void *data))
{
    if (list == NULL)
        return;
    for (node_t *tmp = list->begin; tmp; tmp = tmp->next)
        func(tmp->data);
}

void remove_two(node_t *to_remove, list_t **list)
{
    if (to_remove->prev == NULL && to_remove->next != NULL) {
        list[0]->begin->next->prev = NULL;
        list[0]->begin = list[0]->begin->next;
        free(to_remove);
    } else if (to_remove->prev != NULL && to_remove->next != NULL) {
        to_remove->prev->next = to_remove->next;
        to_remove->next->prev = to_remove->prev;
        free(to_remove);
    }
}

void remove_from_linked_list(node_t *to_remove, list_t **list)
{
    if (to_remove == NULL)
        return;
    if (list[0]->length != 0)
        list[0]->length--;
    free(to_remove->data);
    if (to_remove->prev == NULL && to_remove->next == NULL) {
        free(to_remove);
        free(list[0]);
        list[0] = NULL;
        return;
    } else if (to_remove->prev != NULL && to_remove->next == NULL) {
        list[0]->end->prev->next = NULL;
        list[0]->end = list[0]->end->prev;
        free(to_remove);
        return;
    }
    remove_two(to_remove, list);
}

node_t *case_first_node(list_t **list, node_t *new_member)
{
    list[0] = malloc(sizeof(list_t));
    if (list[0] == NULL) {
        free(new_member);
        return (NULL);
    }
    list[0]->begin = new_member;
    list[0]->end = new_member;
    list[0]->length = 1;
    return (new_member);
}

node_t *append(list_t **list, void *data_to_add)
{
    node_t *new_member = malloc(sizeof(node_t));

    if (new_member == NULL)
        return (NULL);
    new_member->data = data_to_add;
    new_member->prev = NULL;
    new_member->next = NULL;
    if (list[0] == NULL)
        return (case_first_node(list, new_member));
    list[0]->end->next = new_member;
    new_member->prev = list[0]->end;
    list[0]->end = new_member;
    list[0]->length += 1;
    return (new_member);
}
