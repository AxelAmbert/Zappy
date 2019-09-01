/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** send message, if not possible, buffer it
*/

#include "my_functions.h"

static operation send_bufferised_messages(client_t *client, ssize_t *answer)
{
    bufferised_message_t *bufferised_message;

    for (node_t *tmp = begin(client->answer_queue); tmp != NULL;) {
        bufferised_message = tmp->data;
        *answer = recv(client->socket, bufferised_message->message,
                bufferised_message->len, MSG_DONTWAIT);
        if (*answer == EWOULDBLOCK)
            return (FAILURE);
        free(bufferised_message->message);
        remove_from_linked_list(tmp, &client->answer_queue);
        if (client->answer_queue == NULL)
            break;
        tmp = client->answer_queue->begin;
    }
    return (SUCCESS);
}

void safe_send(client_t *client, void *message, size_t message_len)
{
    ssize_t answer = 0;
    bufferised_message_t *bufferised_message = NULL;

    if (send_bufferised_messages(client, &answer) == SUCCESS) {
        answer = send(client->socket, message, message_len,
                MSG_DONTWAIT | MSG_NOSIGNAL);
    }
    if (errno == EWOULDBLOCK) {
        bufferised_message = calloc(sizeof(*bufferised_message), 1);
        bufferised_message->message = malloc(sizeof(char) *message_len);
        memcpy(bufferised_message->message, message, message_len);
        bufferised_message->len = message_len;
        append(&client->answer_queue, bufferised_message);
    }
}