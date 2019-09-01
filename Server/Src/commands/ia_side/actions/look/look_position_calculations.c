/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** Position calculation for the look function
*/

#include "my_functions.h"

position_t multiply_pos(const position_t *to_mutliply,
        uint32_t by)
{
    return ((position_t){to_mutliply->x * by, to_mutliply->y * by});
}

bool direction_cmp(const position_t *one, const position_t *two)
{
    return (one->x == two->x && one->y == two->y);
}

position_t get_contrary(const position_t *of)
{
    if (direction_cmp(of, &moving_positions[LEFT]) == true) {
        return (moving_positions[UP]);
    } else if (direction_cmp(of, &moving_positions[RIGHT]) == true) {
        return (moving_positions[DOWN]);
    }
    if (direction_cmp(of, &moving_positions[UP]) == true) {
        return (moving_positions[RIGHT]);
    } else if (direction_cmp(of, &moving_positions[DOWN]) == true) {
        return (moving_positions[LEFT]);
    }
    return (*of);
}

direction_t clockwise_ninety(direction_t direction)
{
    switch (direction) {
        case UP:
            return (RIGHT);
        case RIGHT:
            return (DOWN);
        case DOWN:
            return (LEFT);
        case LEFT:
            return (UP);
    }
    return (UP);
}

direction_t unclockwise_ninety(direction_t direction)
{
    switch (direction) {
        case UP:
            return (LEFT);
        case RIGHT:
            return (UP);
        case DOWN:
            return (RIGHT);
        case LEFT:
            return (DOWN);
    }
    return (UP);
}

direction_t get_opposite(direction_t direction)
{
    switch (direction) {
        case UP:
            return (DOWN);
        case DOWN:
            return (UP);
        case RIGHT:
            return (LEFT);
        case LEFT:
            return (RIGHT);
    }
    return (UP);
}

static const position_t *start_direction(direction_t direction)
{
    switch (direction) {
        case UP:
            return (&moving_positions[LEFT]);
        case DOWN:
            return (&moving_positions[RIGHT]);
        case LEFT:
            return (&moving_positions[DOWN]);
        case RIGHT:
            return (&moving_positions[UP]);
    }
    return (NULL);
}

position_t calculate_start_pos(client_t *client, server_t *server,
        unsigned int incursion)
{
    position_t denominator =
            multiply_pos(start_direction(client->looking_direction), incursion);
    position_t incursion_direction =
            multiply_pos(&moving_positions[client->looking_direction],
            incursion);
    position_t incursion_adding = (position_t)
            {denominator.x + incursion_direction.x,
            denominator.y + incursion_direction.y};
    return (get_new_valid_positions(&incursion_adding,
            &client->position, server));
}