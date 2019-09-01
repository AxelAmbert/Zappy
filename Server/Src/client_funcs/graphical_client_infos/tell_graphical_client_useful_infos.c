/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** Tell a graphical client usefull infos
*/

#include "my_functions.h"

static void add_an_egg_infos_to_buffer(egg_t *egg, char **buffer)
{
    char *tmp_str = NULL;

    tmp_str = my_getchar(egg->egg_nb);
    safe_strcat(buffer, tmp_str);
    free(tmp_str);
    safe_strcat(buffer, " ");
    tmp_str = my_getchar(egg->position.x);
    safe_strcat(buffer, tmp_str);
    safe_strcat(buffer, " ");
    free(tmp_str);
    tmp_str = my_getchar(egg->position.y);
    safe_strcat(buffer, tmp_str);
    free(tmp_str);
    safe_strcat(buffer, " ");
    tmp_str = my_getchar(egg->is_hatched);
    safe_strcat(buffer, tmp_str);
    safe_strcat(buffer, " ");
    free(tmp_str);
    safe_strcat(buffer, egg->associated_team->team_name);
    safe_strcat(buffer, "\n");
}

static void add_all_eggs_to_buffer(server_t *server, char **buffer)
{
    egg_t *egg = NULL;

    safe_strcat(buffer, "EGGS :\n");
    for (node_t *tmp = begin(server->eggs); tmp != NULL; next(&tmp)) {
        egg = tmp->data;
        if (egg == NULL || egg->associated_team == NULL)
            continue;
        add_an_egg_infos_to_buffer(egg, buffer);
    }
}

static void send_and_release_resources(client_t *client, char *buffer)
{
    safe_send(client, buffer, my_strlen(buffer));
    free(buffer);
}

void tell_graphical_client_useful_infos(server_t *server, client_t *client)
{
    char *buffer = NULL;
    client_t *tmp_client = NULL;
    char *tmp_level = NULL;

    add_all_map_resources_to_buffer(server, &buffer);
    for (node_t *tmp = begin(server->clients); tmp != NULL; next(&tmp)) {
        tmp_client = tmp->data;
        if (tmp_client->is_graphical || !tmp_client->is_connected)
            continue;
        add_player_infos_to_buffer(tmp_client, &buffer);
        safe_strcat(&buffer, " ");
        tmp_level = my_getchar(tmp_client->level);
        safe_strcat(&buffer, tmp_level);
        free(tmp_level);
        safe_strcat(&buffer, " ");
        safe_strcat(&buffer, tmp_client->team->team_name);
        safe_strcat(&buffer, "\n");
    }
    add_all_eggs_to_buffer(server, &buffer);
    send_and_release_resources(client, buffer);
}