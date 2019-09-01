/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** return the clock() function, directly transformed in seconds
*/

#include "my_functions.h"
#include <sys/time.h>

/*
    Return time since the begining of the program
    Milisecond precision
*/

double clock_seconds(void)
{
    static double base_time = 0;
    struct timeval tv;

    gettimeofday(&tv, NULL);
    if (base_time == 0) {
        base_time = (double)tv.tv_sec + (double)tv.tv_usec / 1000000;
        return (0);
    }
    return (((double)tv.tv_sec + (double)tv.tv_usec / 1000000) - base_time);
}