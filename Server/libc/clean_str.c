/*
** EPITECH PROJECT, 2019
** NWP_my_ftp_2018
** File description:
** libc
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#include "my_functions.h"

bool only_wrong_characters(const char *to_test, const char *bad_characters)
{
    for (int i = 0; to_test[i]; i++) {
        if (character_is_in_string(bad_characters,
                &to_test[i]) == false)
            return (false);
    }
    return (true);
}

char *get_cleaned_str(char **tmp)
{
    unsigned int len = 0;
    char *new_str = NULL;
    unsigned int x = 0;
    unsigned int i = 0;

    for (; tmp[i]; i++)
        len += my_strlen(tmp[i]);
    new_str = malloc(sizeof(char) * len + 1 + i);
    for (int y = 0; tmp[y]; y++, x++) {
        for (int u = 0; tmp[y][u]; u++, x++)
            new_str[x] = tmp[y][u];
        if (tmp[y + 1])
            new_str[x] = ' ';
    }
    new_str[x - 1] = '\0';
    return (new_str);
}

char *clean_str(const char *to_clean, const char *bad_characters)
{
    char *new_str = NULL;
    char **tmp = NULL;

    if (to_clean == NULL ||
        only_wrong_characters(to_clean, bad_characters) == true)
        return (NULL);
    tmp = my_str_to_word_array(to_clean, bad_characters);
    if (tmp == NULL)
        return (NULL);
    new_str = get_cleaned_str(tmp);
    free_two_dim_tab(tmp);
    return (new_str);
}