/*
** EPITECH PROJECT, 2019
** NWP_my_ftp_2018
** File description:
** libc
*/

#include "my_functions.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <dirent.h>

list_t *get_all_files_in_folder(char *path)
{
    list_t *file_list = NULL;
    DIR *directory;
    struct dirent *dir;

    directory = opendir(path);
    if (directory == NULL)
        return (NULL);
    while ((dir = readdir(directory)) != NULL) {
        append(&file_list, my_strcpy(dir->d_name));
    }
    return (file_list);
}

void *data_at_index(list_t *list, unsigned int index)
{
    node_t *tmp = NULL;

    if (list == NULL)
        return (tmp);
    tmp = list->begin;
    for (unsigned int i = 0; i < index; tmp = tmp->next, i++) {
        if (tmp == NULL)
            return (list->end);
    }
    return (tmp->data);
}

void free_the_list(list_t **list, void (free_func)(void *data))
{
    if (list == NULL || list[0] == NULL) {
        return;
    }
    for (node_t *tmp = begin(list[0]); tmp != NULL; tmp = tmp->next) {
        free_func(tmp->data);
        free(tmp->prev);
    }
    free(list[0]->end);
    free(list[0]);
    list[0] = NULL;
}

void remove_by_value(list_t **list, void *to_find,
        bool (compare_func)(void *node_value, void *data_to_test))
{
    for (node_t *tmp = list[0]->begin; tmp != NULL; tmp = tmp->next) {
        if (compare_func(tmp->data, to_find) == true) {
            remove_from_linked_list(tmp, list);
            return;
        } else {
            entity_t *entity = tmp->data;
            if (entity->type == PLAYER) {

            }
        }
    }
}

void *get_data_from_value(list_t *list, void *to_find,
        bool (compare_func)(void *node_value, void *data_to_test))
{
    for (node_t *tmp = list->begin; tmp != NULL; tmp = tmp->next) {
        if (compare_func(tmp->data, to_find) == true)
            return (tmp->data);
    }
    return (NULL);
}