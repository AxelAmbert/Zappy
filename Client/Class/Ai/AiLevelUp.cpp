/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** by mlucas on 19/06/19
*/

#include "Ai.hpp"

bool clt::Ai::tryToLevelUp()
{
    this->lookAround();
    clearCommandQueue();
    if (this->_isAlive && this->_level == 1) {
        if (!this->hasEnoughStones() || !hasEnoughPlayers())
            return false;
        this->takeAllObjectOnTheTile();
        this->lookAround();
        clearCommandQueue();
        this->dropAllObjectToLevelUp();
        if (this->_isAlive)
            this->startIncantation();
        this->takeAllObjectOnTheTile();
        clearCommandQueue();
        return true;
    }
    if (this->_isAlive && !this->_inGroup && !this->_ready) {
        if (this->_isAlive && !this->hasEnoughStones())
            return false;
        this->takeAllObjectOnTheTile();
        this->_ready = true;
        this->clearCommandQueue();
        return true;
    }
    this->leaderLevelUp();
    this->notLeaderLevelUp();
    this->clearCommandQueue();
    return true;
}

void clt::Ai::leaderLevelUp()
{
    if (this->_isAlive && this->_inGroup && this->_leader &&
        this->verifEnoughPlayer()) {
        this->takeAllObjectOnTheTile();
        this->sendRequest("DROP", this->_id, -1);
        this->lookAround();
        clearCommandQueue();
        this->dropAllObjectToLevelUp();
        if (this->_isAlive)
            this->startIncantation();
        this->lookInventory();
        clearCommandQueue();
        this->deleteGroup();
        if (this->_inventory["food"] > 5) {
            this->lookAround();
            clearCommandQueue();
            this->takeAllObjectOnTheTile();
            clearCommandQueue();
        }
    }
}

void clt::Ai::notLeaderLevelUp()
{
    if (this->_isAlive && this->_inGroup && !this->_leader && this->_dropCommand) {
        while (this->_isAlive && this->_inGroup)
            usleep(5);
        this->_dropCommand = false;
    }
}

bool clt::Ai::hasEnoughStones()
{
    int count = 0;

    for (auto &it: this->_levelUpCondition[this->_level]) {
        count = 0;
        if (it.first == "player")
            continue;
        for (auto &object: this->_look[0])
            if (object == it.first)
                count++;
        if (it.second > this->_inventory[it.first] + count)
            return false;
    }
    return true;
}

bool clt::Ai::hasEnoughPlayers()
{
    int count = 0;
    for (auto &object: this->_look[0])
        if (object == "player")
            count++;
    return (this->_levelUpCondition[this->_level]["player"] == count);
}

bool clt::Ai::verifEnoughPlayer()
{
    for (int i = 0; i < 2; i++) {
        this->lookAround();
        clearCommandQueue();
        if (!this->hasEnoughPlayers())
            return false;
    }
    return true;
}

std::map<std::string, int> &clt::Ai::getWhatAiNeedsToLevelUp()
{
    this->_objects.clear();

    for (auto &it: this->_levelUpCondition[this->_level]) {
        if (it.first == "player")
            continue;
        if (it.second > this->_inventory[it.first]) {
            this->_objects.emplace(std::pair<std::string, int>(it.first, it.second - this->_inventory[it.first]));
        }
    }
    return this->_objects;
}

void clt::Ai::takeAllObjectOnTheTile()
{
    if (!this->_isAlive)
        return;

    for (auto &object: this->_look[0]) {
        if (object == "player")
            continue;
        if (this->queueIsFull())
            this->clearCommandQueue();
        if (!this->_isAlive)
            return;
        this->takeObject(object);
    }
}

void clt::Ai::dropAllObjectToLevelUp()
{
    int count = 0;

    if (!this->_isAlive)
        return;

    for (auto &it: this->_levelUpCondition[this->_level]) {
        count = 0;
        if (it.first == "player")
            continue;
        for (auto &object: this->_look[0])
            if (object == it.first)
                count++;
        for (int i = count; this->_isAlive && it.second - i > 0; i++) {
            if (this->queueIsFull())
                this->clearCommandQueue();
            if (!this->_isAlive)
                return;
            this->setObjectDown(const_cast<std::string &>(it.first));
        }
    }
}
