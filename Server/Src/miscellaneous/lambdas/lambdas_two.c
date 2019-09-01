/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** mostly lambdas function pointer
*/

#include "my_functions.h"

bool is_a_graphical_client(void *null_data __attribute__((unused)),
        void *client)
{
    return (((client_t *)client)->is_graphical);
}

void dummy_free(void *data __attribute__((unused)))
{

}

bool lambda_entity_level(void *level, void *entity)
{
    entity_t *test_entity = entity;

    if (test_entity->type != PLAYER)
        return (false);
    return (((client_t *)test_entity->data)->level == *((uint32_t *)level));
}

bool lambda_cmp_entity(void *entity, void *type)
{
    return (((entity_t *)entity)->type == *((type_t *)type));
}

bool lambda_client_nb_cmp(void *client_one, void *data)
{
    return (((client_t *)client_one)->socket == (intptr_t)data);
}
