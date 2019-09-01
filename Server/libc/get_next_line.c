/*
** EPITECH PROJECT, 2019
** NWP_my_ftp_2018
** File description:
** libc
*/

#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "my_functions.h"

void reset_buffer(char **buffer, bool reset)
{
    if (reset == true) {
        if (buffer[0] == NULL)
            return;
        free(buffer[0]);
        buffer[0] = NULL;
    }
}

char *special_case(char **buffer)
{
    char *tmp = NULL;

    if (buffer[0][0] == '\0') {
        free(buffer[0]);
        buffer[0] = NULL;
        return (NULL);
    }
    tmp = malloc(sizeof(char));
    my_realloc_cut_str(buffer, buffer[0], 1, my_strlen(buffer[0]) - 1);
    tmp[0] = '\0';
    return (tmp);
}

char *part_of_str(char **buffer)
{
    char *tmp = NULL;
    unsigned until_new_line = 0;

    if (buffer[0] == NULL)
        return (NULL);
    if (buffer[0][0] == '\n' || buffer[0][0] == '\0')
        return (special_case(buffer));
    if (find_occurencies(buffer[0], "\n") == 0) {
        tmp = my_strcpy(buffer[0]);
        free(buffer[0]);
        buffer[0] = NULL;
        return (tmp);
    }
    for (; buffer[0][until_new_line] != '\n'; until_new_line++);
    tmp = cut_str(buffer[0], 0, until_new_line - 1);
    if (tmp == NULL)
        return (tmp);
    my_realloc_cut_str(buffer, buffer[0],
            until_new_line + 1, my_strlen(buffer[0]) - 1);
    return (tmp);
}

char *get_next_line(int fd, bool reset, unsigned int readsize)
{
    static char *buffer = NULL;
    char *mini_buffer = malloc(sizeof(char) * readsize + 1);
    ssize_t bytes_read = readsize;

    reset_buffer(&buffer, reset);
    while (bytes_read == readsize && find_occurencies(buffer, "\n") == 0) {
        bytes_read = read(fd, mini_buffer, readsize);
        mini_buffer[bytes_read] = '\0';
        my_reallocstrcat(&buffer, mini_buffer);
    }
    free(mini_buffer);
    return (part_of_str(&buffer));
}
