/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** by mlucas on 19/06/19
*/

#include "Ai.hpp"

void clt::Ai::moveToRandomDirection()
{
    this->clearCommandQueue();
    for (int i = rand() % 4; this->_isAlive && i > 0; i--)
        this->turnRight();
    for (int i = 0; this->_isAlive && i < (this->_level + 1) * 2; i++) {
        if (this->queueIsFull())
            this->clearCommandQueue();
        this->goForward();
    }
    this->clearCommandQueue();
}
