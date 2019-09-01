/*
** EPITECH PROJECT, 2019
** NWP_my_ftp_2018
** File description:
** libc
*/

#include "my_functions.h"

unsigned int intlen(const int to_size)
{
    unsigned int size = 0;
    int tmp = to_size;

    if (to_size == 0)
        return (1);
    else if (to_size < 0) {
        size++;
    }
    while (tmp != 0) {
        tmp /= 10;
        size++;
    }
    return (size);
}
