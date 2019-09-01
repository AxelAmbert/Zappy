/*
** EPITECH PROJECT, 2019
** NWP_my_ftp_2018
** File description:
** libc
*/

#include "my_functions.h"

static void extract_two(node_t *to_remove, list_t **list)
{
    if (to_remove->prev == NULL && to_remove->next != NULL) {
        list[0]->begin->next->prev = NULL;
        list[0]->begin = list[0]->begin->next;
    } else if (to_remove->prev != NULL && to_remove->next != NULL) {
        to_remove->prev->next = to_remove->next;
        to_remove->next->prev = to_remove->prev;
    }
}

void extract_a_node(list_t **list, node_t *to_remove)
{
    if (to_remove == NULL)
        return;
    if (list[0]->length != 0)
        list[0]->length--;
    if (to_remove->prev == NULL && to_remove->next == NULL) {
        free(list[0]);
        list[0] = NULL;
        return;
    } else if (to_remove->prev != NULL && to_remove->next == NULL) {
        list[0]->end->prev->next = NULL;
        list[0]->end = list[0]->end->prev;
        return;
    }
    extract_two(to_remove, list);
}

void append_node(list_t **list, node_t *node)
{
    if (node == NULL || list == NULL)
        return;
    node->next = NULL;
    node->prev = end(list[0]);
    if (list[0] == NULL) {
        list[0] = malloc(sizeof(list_t));
        list[0]->length = 1;
        list[0]->begin = node;
        list[0]->end = node;
    } else {
        list[0]->end->next = node;
        node->prev = list[0]->end;
        list[0]->end = node;
        list[0]->length += 1;
    }
}

void transfert_a_node(list_t **old_list, list_t **new_list, node_t *node)
{
    if (old_list == NULL || node == NULL) {
        return;
    }
    extract_a_node(old_list, node);
    append_node(new_list, node);
}