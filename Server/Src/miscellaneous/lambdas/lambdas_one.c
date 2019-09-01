/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** mostly lambdas function pointer
*/

#include "my_functions.h"

bool lambda_client_cmp(void *client_one, void *client_to_test)
{
    return (client_one == client_to_test);
}

bool lambda_client_entity_cmp(void *entity_one, void *entity_two)
{
    entity_t *one = entity_one;

    return (one->data == entity_two);
}

bool lambda_entity_type_cmp(void *type, void *entity)
{
    entity_t *one = entity;

    return (one->type == *(type_t *)type);
}

bool lambda_entity_cmp(void *entity_one, void *entity_two)
{
    entity_t *one = entity_one;
    entity_t *two = entity_two;

    if (one->type == two->type)
        return (true);
    return (false);
}

bool lambda_client_max(void *one, void *two)
{
    client_t *client_one = one;
    client_t *client_two = two;

    if (client_one->socket > client_two->socket)
        return (true);
    return (false);
}
