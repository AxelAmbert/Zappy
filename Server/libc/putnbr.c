/*
** EPITECH PROJECT, 2019
** NWP_my_ftp_2018
** File description:
** libc
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "my_functions.h"

void my_putchar(char to_print)
{
    write(1, &to_print, 1);
}

unsigned int determine_modulo(const int to_print)
{
    unsigned int modulo = 1;

    while (to_print / modulo)
        modulo *= 10;
    return (modulo / 10);
}

void putnbr(const int to_print)
{
    unsigned int modulo = 0;
    int tmp = to_print;

    if (tmp < 0) {
        write(1, "-", 1);
        tmp *= -1;
    } else if (tmp == 0) {
        write(1, "0", 1);
        return;
    }
    modulo = determine_modulo(tmp);
    while (tmp) {
        my_putchar(tmp / modulo + 48);
        tmp %= modulo;
        modulo /= 10;
    }
    while (modulo) {
        my_putchar('0');
        modulo /= 10;
    }
}

void uputnbr(const unsigned int to_print)
{
    unsigned int modulo = 0;
    unsigned int tmp = to_print;

    if (tmp == 0) {
        write(1, "0", 1);
        return;
    }
    modulo = determine_modulo(tmp);
    while (tmp) {
        my_putchar(tmp / modulo + 48);
        tmp %= modulo;
        modulo /= 10;
    }
    while (modulo) {
        my_putchar('0');
        modulo /= 10;
    }
}
