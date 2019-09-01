/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** by mlucas on 03/06/19
*/

#include "Ai.hpp"

/**
 * @brief Check if the queue if full
 * @retunr bool
 */
bool clt::Ai::queueIsFull()
{
    int count = 0;

    for (auto &it: this->_commandQueue) {
        if (it->getIsDone())
            count++;
    }
    return this->_commandQueue.size() - count >= 10;
}

/**
 * @brief Run The Ai Algorithm
 * @param void
 */
void clt::Ai::startAiAlgo()
{
    srand(time(nullptr));
    std::thread serverAnswersManagementThread([this]() {
        this->serverAnswersManagement();
    });
    serverAnswersManagementThread.detach();

    while (this->_isAlive) {
        this->_isEject = false;
        this->lookInventory();
        this->clearCommandQueue();
        std::cout << "Inventory Food =" << this->_inventory["food"] << " ID = " << this->_id << " LEADER " << this->_leader << " LEADER ID = " << this->_leaderId << " LVL " << this->_level << " DIRECTION = " << this->_direction << " GROUP = " << this->_inGroup <<std::endl;
        if (!this->_isAlive || this->needFoods())
            continue;
        if (this->_level == 8)
            continue;
        if (!this->_isAlive || this->groupCommunication())
            continue;
        if (!this->_isAlive || this->tryToLevelUp())
            continue;
        if (this->_isAlive) {
            this->farmMultipleObjects(this->getWhatAiNeedsToLevelUp());
        }
    }
    while (!this->_threadIsDone)
        usleep(5);
}