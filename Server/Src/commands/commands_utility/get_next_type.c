/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** handle clients commands
*/

#include "my_functions.h"

void *get_next_entity(list_t *tile_entities, type_t type, bool reset)
{
    static node_t *tmp = NULL;
    entity_t *entity = NULL;
    void *data = NULL;

    if (tmp == NULL || reset == true)
        tmp = tile_entities->begin;
    while (tmp != NULL) {
        entity = tmp->data;
        if (entity->type == type) {
            data = entity->data;
            tmp = tmp->next;
            return (data);
        }
        tmp = tmp->next;
    }
    return (NULL);
}

