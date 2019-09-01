/*
** EPITECH PROJECT, 2019
** NWP_my_ftp_2018
** File description:
** libc
*/

#include <stdlib.h>
#include "my_functions.h"

void my_realloc_cut_str(char **

new,
const char *to_copy,
const unsigned int from,
const unsigned int to
)
{
char *tmp = cut_str(to_copy, from, to);

if (new[0] != NULL)
free(new[0]);
new[0] =
tmp;
}
