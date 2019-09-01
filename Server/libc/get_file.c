/*
** EPITECH PROJECT, 2019
** NWP_my_ftp_2018
** File description:
** libc
*/

#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>

#include "my_functions.h"

long unsigned int get_number_of_line(char *path)
{
    char *tmp = NULL;
    long unsigned int length = 0;
    int fd = open(path, O_RDONLY);

    while ((tmp = get_next_line(fd, false, 10000)) != NULL) {
        length++;
        free(tmp);
    }
    return (length);
}

char **get_file(char *file_path)
{
    char **file = NULL;
    int fd = open(file_path, O_RDONLY);
    char *tmp = NULL;
    unsigned int counter = 0;

    if (fd < 0)
        return (NULL);
    file = malloc(sizeof(char *) * (get_number_of_line(file_path) + 1));
    do {
        tmp = get_next_line(fd, false, 1);
        file[counter] = tmp;
        counter++;
    } while (tmp != NULL);
    return (file);
}
