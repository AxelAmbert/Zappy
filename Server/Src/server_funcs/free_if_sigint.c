/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** Free the program even if a sigint is catched
*/

#include "my_functions.h"

void free_if_sigint(int signal_type __attribute__((unused)))
{
    exit_error("SUCCESS");
}