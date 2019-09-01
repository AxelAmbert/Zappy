/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** give player's inventory
*/

#include "my_functions.h"

void add_new_type_to_message(type_t type, char **message, list_t *inventory)
{
    int nb = 0;
    entity_t *item = NULL;
    char *tmp = NULL;

    for (node_t *tmp = begin(inventory); tmp != NULL; tmp = tmp->next) {
        item = tmp->data;
        if (item->type == type)
            nb += 1;
    }
    tmp = my_getchar(nb);
    safe_strcat(message, type_str[type]);
    safe_strcat(message, " ");
    safe_strcat(message, tmp);
    free(tmp);
}

void case_food(client_t *client, char **message)
{
    char *tmp = my_getchar(client->time_unit_left / 126);

    safe_strcat(message, "[food ");
    safe_strcat(message, tmp);
    safe_strcat(message, ", ");
    free(tmp);
}

void inventory(server_t *server __attribute__((unused)), client_t *client,
        char *args __attribute__((unused)))
{
    char *message = NULL;

    case_food(client, &message);
    for (type_t type = LINEMATE; type < PLAYER; type += 1) {
        add_new_type_to_message(type, &message, client->inventory);
        if (type + 1 != PLAYER)
            safe_strcat(&message, ", ");
        else
            safe_strcat(&message, "]\n");
    }
    safe_send(client, message, my_strlen(message));
    free(message);
}