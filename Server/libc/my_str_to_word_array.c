/*
** EPITECH PROJECT, 2019
** NWP_my_ftp_2018
** File description:
** libc
*/

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "my_functions.h"

unsigned int its_end(const char *in_string, const char *separators, int where)
{
    while (in_string[where]) {
        if (character_is_in_string(separators,
                &in_string[where]) == true)
            return (false);
        where++;
    }
    return (true);
}

unsigned int get_number_of_dimensions(const char *in_string,
        const char *separator)
{
    unsigned int counter = 0;
    unsigned int i = 0;

    for (; character_is_in_string(separator, &in_string[i]) == true; i++);
    if (in_string[i] == '\0')
        return (0);
    for (; in_string[i]; i++) {
        if (its_end(in_string, separator, i) == true)
            return (counter + 1);
        if (character_is_in_string(separator, &in_string[i]) == true)
            counter++;
        for (; character_is_in_string(separator, &in_string[i]) == true; i++);
        if (in_string[i] == '\0')
            break;
    }
    return (counter + 1);
}

void get_next_separator(const char *string, const char *separator,
        unsigned int *from)
{
    if (string == NULL || my_strlen(string) + 1 < *from ||
        string[*from] == '\0') {
        *from = -1;
        return;
    }
    for (; string[*from]; *from += 1) {
        if (character_is_in_string(separator, &string[*from]) == true)
            return;
    }
}

void get_the_tab(const char *string_to_cut, const char *separator,
        char ***array)
{
    unsigned int dimension = 0;
    unsigned int last_pos = 0;
    int iterator = 0;

    for (; character_is_in_string(separator, &string_to_cut[iterator]) == true;
        iterator++);
    last_pos = iterator;
    get_next_separator(string_to_cut, separator, (unsigned int *) &iterator);
    while (iterator != -1) {
        array[0][dimension] = cut_str(string_to_cut,
                last_pos, iterator - 1);
        for (; character_is_in_string(separator,
                &string_to_cut[iterator]) == true; iterator++);
        last_pos = iterator;
        get_next_separator(string_to_cut, separator,
                (unsigned int *) &iterator);
        dimension++;
    }
    array[0][dimension] = NULL;
}

char **my_str_to_word_array(const char *string_to_cut, const char *separator)
{
    char **array = NULL;
    unsigned int dimensions =
            get_number_of_dimensions(string_to_cut, separator);

    if (dimensions == 0)
        return (NULL);
    array = malloc(sizeof(char *) * (dimensions + 1));
    if (!array)
        return (NULL);
    get_the_tab(string_to_cut, separator, &array);
    return (array);
}