/*
** EPITECH PROJECT, 2018
** NWP_myarpspoof_2018
** File description:
** exit with an error message
*/

#include "my_functions.h"
#include <stdarg.h>

/* When this function is called it check if message == NULL
** if its NULL, it means that it will set the free at exit function pointer
** and data to free list, the last arg must be NULL to end the list
** if you want the function not to free the free list the message must have
** "CRITICAL" behind its message
** When the variadic arguments are not used to set the "free list", you
** can use them to send argument, the error message is print with vfprintf
*/

static void set_the_free_list(list_t **free_list, va_list args_list)
{
    volatile bool until_end = true;
    free_func_ptr_and_data_t *tmp = NULL;
    void (*stop_ptr)(void *) = NULL;

    while (until_end) {
        stop_ptr = va_arg(args_list, void (*)(void *));
        if (stop_ptr == NULL)
            break;
        tmp = malloc(sizeof(*tmp));
        if (tmp == NULL)
            exit_error("Failed to allocate free list\n");
        tmp->free_ptr = stop_ptr;
        tmp->data_to_free = va_arg(args_list, void *);
        append(free_list, tmp);
    }
    va_end(args_list);
}

static void free_the_free_list(list_t *list)
{
    free_func_ptr_and_data_t *free_struct = NULL;

    for (node_t *tmp = list->begin; tmp; tmp = tmp->next) {
        free_struct = tmp->data;
        free_struct->free_ptr(free_struct->data_to_free);
    }
    free_the_list(&list, free);
}

void exit_error(const char *message, ...)
{
    static list_t *free_list = NULL;
    va_list arg_list;

    va_start(arg_list, message);
    if (free_list == NULL && message == NULL) {
        set_the_free_list(&free_list, arg_list);
    } else {
        if (my_strcmp(message, "SUCCESS", false) != true)
            vfprintf(stderr, message, arg_list);
        if (free_list != NULL &&
        my_strncmp(message, "CRITICAL", my_strlen("CRITICAL"), false) != true) {
            free_the_free_list(free_list);
        }
        if (my_strcmp(message, "SUCCESS", false) == true)
            exit(0);
        exit(84);
    }
}