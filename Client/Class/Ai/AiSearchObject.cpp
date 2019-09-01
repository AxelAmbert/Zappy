/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** by mlucas on 19/06/19
*/

#include "Ai.hpp"

/**
 * @brief Ai farms food to obtain 25 foods in his inventory
 * @return bool
 */
bool clt::Ai::needFoods()
{
    if (this->_inGroup && !this->_leader && this->_dropCommand)
        return false;
    if (this->_inventory["food"] > 5)
        return false;
    this->farmObject("food", 20 - this->_inventory["food"]);
    return true;
}

/**
 * @brief farm multiple type of objects
 * @param std::map<std::string, int> Objects To Look For
 */
void clt::Ai::farmMultipleObjects(std::map<std::string, int> &objects)
{
    bool end = false;

    while (this->_isAlive && this->_leaderId == 0 && !end) {
        if (this->_inventory["food"] < 5)
            return;
        end = true;
        for (auto &it: objects) {
            if (it.second > 0)
                end = false;
        }
        if (!end) {
            if (this->_isAlive && searchMultipleObjects(objects))
                this->clearCommandQueue();
            else
                this->moveToRandomDirection();
        }
    }
}

/**
 * @brief The Ai Look For Multiple Objects
 * @param std::map<std::string, int> Objects To Look For
 * return bool
 */
bool clt::Ai::searchMultipleObjects(std::map<std::string, int> &objects)
{
    for (int i = 0; this->_isAlive && this->_leaderId == 0 && i < 4; i++) {
        this->lookInventory();
        this->clearCommandQueue();
        if (this->_inventory["food"] < 5)
            return false;
        for (auto &it: objects) {
            if (this->_isAlive && it.second > 0 && this->searchAnObject(it.first)) {
                it.second--;
                return true;
            }
        }
        if (this->_isAlive)
            this->turnRight();
    }
    return false;
}

/**
 * @brief The Ai Look For An Object
 * @param std::string Object To Look For
 * @param int value of object to farm
 */
void clt::Ai::farmObject(const std::string &object, int value)
{
    while (this->_isAlive && value > 0) {
        if (this->searchAnObject(object)) {
            value--;
            this->clearCommandQueue();
        } else
            this->moveToRandomDirection();
        if (object == "food") {
            this->lookInventory();
            this->clearCommandQueue();
            if (this->_inventory["food"] >= 20)
                break;
        }
    }
}

/**
 * @brief The Ai Look For An Object
 * @param std::string Object To Look For
 * return bool
 */
bool clt::Ai::searchAnObject(const std::string &object)
{
    for (int i = 0; this->_isAlive && i < 4; i++) {
        clearCommandQueue();
        if (this->_isAlive && this->findObject(object))
            return true;
        else if (this->_isAlive)
            this->turnRight();
    }
    return false;
}

/**
 * @brief The Ai Look For An Object
 * @param std::string Object To Find
 * @return bool
 */
bool clt::Ai::findObject(std::string object)
{
    int commandId = 0;
    int objectPos = 0;
    int depth = 0;
    int middle = 0;
    int nb = 1;
    int valid = 0;

    this->lookAround();
    commandId = this->_commandQueue.size() - 1;
    while (this->_isAlive && !this->_commandQueue[commandId]->getIsDone())
        usleep(5);
    if (!this->_isAlive || !this->_commandQueue[commandId]->getSuccess())
        return false;
    clearCommandQueue();
    objectPos = this->getObjectPos(object);
    if (objectPos == -1)
        return false;
    while (objectPos >= nb) {
        depth++;
        nb += depth + depth * 2;
    }
    for (int i = depth; this->_isAlive && i > 0; i--) {
        if (this->queueIsFull())
            this->clearCommandQueue();
        if (!this->_isAlive)
            return false;
        this->goForward();
        middle += i * 2;
    }
    if (objectPos > middle) {
        if (this->queueIsFull())
            this->clearCommandQueue();
        if (!this->_isAlive)
            return false;
        this->turnRight();
        for (int i = objectPos; i != middle; i--) {
            if (this->queueIsFull())
                this->clearCommandQueue();
            if (!this->_isAlive)
                return false;
            this->goForward();
        }
    }
    if (objectPos < middle) {
        if (this->queueIsFull())
            this->clearCommandQueue();
        if (!this->_isAlive)
            return false;
        this->turnLeft();
        for (int i = objectPos; this->_isAlive && i != middle; i++) {
            if (this->queueIsFull())
                this->clearCommandQueue();
            if (!this->_isAlive)
                return false;
            this->goForward();
        }
    }
    if (!this->_isAlive)
        return false;
    this->clearCommandQueue();
    while (this->_isAlive) {
        this->takeObject(object);
        commandId = this->_commandQueue.size() - 1;
        while (this->_isAlive && !this->_commandQueue[commandId]->getIsDone())
            usleep(5);
        if (this->_commandQueue[commandId]->getSuccess())
            valid++;
        else
            break;
        if (object != "food")
            break;
        this->clearCommandQueue();
    }
    return (valid != 0);
}

int clt::Ai::getObjectPos(std::string object)
{
    bool isPlayer;
    int objectPos = -1;

    for (auto &it: this->_look) {
        isPlayer = false;
        for (auto &i : it.second) {
            if (i == object) {
                objectPos = it.first;
                break;
            }
        }
        if (it.first != 0) {
            for (auto &i : it.second) {
                if (i == "player")
                    isPlayer = true;
            }
        }
        if (objectPos != -1 && !isPlayer)
            break;
    }
    return objectPos;
}