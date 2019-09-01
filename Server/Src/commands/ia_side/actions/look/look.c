/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** Look the map and tell the client whats on it
*/

#include "my_functions.h"

void safe_strcat(char **dest, const char *src)
{
    unsigned int dest_size = my_strlen(dest[0]);
    unsigned int src_size = my_strlen(src);
    unsigned int size_add = dest_size + src_size;

    if (dest_size / 100 != size_add / 100 || dest_size == 0) {
        dest[0] = realloc(dest[0], ((size_add / 100) + 1) * 100);
    }
    for (uint32_t i = 0; i < src_size; i++, dest_size++) {
        dest[0][dest_size] = src[i];
    }
    dest[0][dest_size] = '\0';
}

void get_object_on_tile(position_t where, char **message, list_t ***map)
{
    entity_t *entity = NULL;

    for (node_t *tmp = begin(map[where.y][where.x]); tmp != NULL;
    tmp = tmp->next) {
        entity = tmp->data;
        safe_strcat(message, type_str[entity->type]);
        if (tmp->next != NULL)
            safe_strcat(message, " ");
    }
    safe_strcat(message, ",");
}

void look_on_range(client_t *client, server_t *server,
        unsigned int incursion, char **message)
{
    unsigned int range = 1  + incursion * 2;
    position_t start = calculate_start_pos(client, server, incursion);
    position_t contrary =
            get_contrary(&moving_positions[client->looking_direction]);

    for (uint32_t i = 0; i < range; i++) {
        get_object_on_tile(start, message, server->map);
        start = get_new_valid_positions(&start, &contrary, server);
    }
}

void look(server_t *server, client_t *client,
        char *args __attribute__((unused)))
{
    char *message = NULL;

    safe_strcat(&message, "[ ");
    for (unsigned int i = 0; i <= client->level; i++) {
        look_on_range(client, server, i, &message);
    }
    safe_strcat(&message, " ]\n");
    safe_send(client, message, my_strlen(message));
    free(message);
}

