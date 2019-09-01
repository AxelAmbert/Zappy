/*
** EPITECH PROJECT, 2018
** my_functions.h
** File description:
** prototype of my functions
*/


#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#define DYNAMIC_S(data) dynamic(&dump, data, STRING)

typedef enum data_types
{
    STRING, TWODARRAY, SFRECT, SFTEX, SFTEXT, SFSPRITE
}data_types;

typedef struct node_s
{
    void *data;
    struct node_s *prev;
    struct node_s *next;
}node_t;

typedef struct list_s
{
    node_t *begin;
    node_t *end;
    unsigned int length;
}list_t;


#endif //DUMP
