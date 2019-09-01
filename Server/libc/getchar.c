/*
** EPITECH PROJECT, 2019
** NWP_my_ftp_2018
** File description:
** libc
*/

#include <stdlib.h>
#include <stdbool.h>
#include "my_functions.h"

bool getchar_special_cases(char **new_str, int *to_translate, int *counter)
{
    if (*to_translate == 0) {
        new_str[0][0] = '0';
        new_str[0][1] = '\0';
        return (true);
    } else if (*to_translate < 0) {
        new_str[0][0] = '-';
        *counter += 1;
        *to_translate *= -1;
    }
    return (false);
}

void get_the_number_in_str(char **new_str, unsigned int counter,
        unsigned int power, int tmp)
{
    while (tmp) {
        new_str[0][counter] = tmp / power + 48;
        tmp %= power;
        power /= 10;
        counter++;
    }
    while (power) {
        new_str[0][counter] = '0';
        counter++;
        power /= 10;
    }
    new_str[0][counter] = '\0';
}

char *my_getchar(const int to_translate)
{
    char *new_str = NULL;
    unsigned int len = intlen(to_translate);
    unsigned int counter = 0;
    unsigned int power = 1;
    int tmp = to_translate;

    new_str = malloc(sizeof(char) * (len + 1));
    if (getchar_special_cases(&new_str, &tmp, (int *) &counter) == true)
        return (new_str);
    if (to_translate < 0)
        len--;
    for (unsigned int i = 0; i < len - 1; i++, power *= 10);
    get_the_number_in_str(&new_str, counter, power, tmp);
    return (new_str);
}
