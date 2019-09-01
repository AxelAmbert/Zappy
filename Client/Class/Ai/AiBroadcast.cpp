/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** by mlucas on 20/06/19
*/

#include "Ai.hpp"

bool clt::Ai::groupCommunication()
{
    std::string msg;

    if (!this->_isAlive)
        return false;
    for (auto &it: this->_rejectedMembers)
        this->sendRequest("JOIN KO", this->_id, it);
    this->_rejectedMembers.clear();
    this->clearCommandQueue();
    if (this->_inGroup) {
        if (this->_leaderId == 0) {
            this->_inGroup = false;
            return true;
        }
        if (this->_leader)
            return this->leaderGroupCommunication();
        else
            return this->notLeaderGroupCommunication();
    } else {
        if (this->_leaderId == 0 || this->_leaderId == this->_id)
            return this->leaderNoGroupCommunication();
        else if (!this->_leader && this->_leaderId != 0)
            return this->notLeaderNoGroupCommunication();
    }
    return false;
}

bool clt::Ai::leaderGroupCommunication()
{
    for (auto &it: this->_members)
        std::cout << "\033[31mMEMBERS = \033[0m" << it << std::endl;
    for (auto &object: this->_look[0]) {
        if (!this->_isAlive)
            return true;
        if (object != "food")
            continue;
        this->clearCommandQueue();
        for (auto &it: this->_pings)
            this->sendRequest("PING", this->_id, it);
        this->_pings.clear();
        this->takeObject(object);
    }
    for (auto &it: this->_pings)
        this->sendRequest("PING", this->_id, it);
    this->_pings.clear();
    clearCommandQueue();
    return false;
}

bool clt::Ai::notLeaderGroupCommunication()
{
    if (this->_dropCommand)
        return false;
    this->_pinged = false;
    this->sendRequest("PING", this->_id, this->_leaderId);
    while (this->_isAlive && !this->_pinged) {
        this->lookInventory();
        this->clearCommandQueue();
        if (this->_inventory["food"] < 5)
            return true;
        usleep(5);
    }
    this->_pinged = false;
    if (this->_direction == 0) {
        return true;
    }
    this->moveToLeaderDirection();
    this->takeAllObjectOnTheTile();
    clearCommandQueue();
    return true;
}

bool clt::Ai::leaderNoGroupCommunication()
{
    if (this->_leaderId == 0 || this->_leaderId == this->_id) {
        if (!this->_ready || this->_nextLeaderId != 0)
            return false;
        this->_leader = true;
        this->_leaderId = this->_id;
        for (auto &it: this->_members)
            std::cout << "\033[36mMEMBERS = \033[0m" << it << std::endl;
        this->sendRequest("CREATE", this->_id, -1);
        if (this->_members.empty())
            return true;
        if ((int)(this->_members.size() + 1) == this->_levelUpCondition[this->_level]["player"]) {
            for (auto &it: this->_members) {
                if (!this->_isAlive)
                    return false;
                this->sendRequest("JOIN", this->_id, it);
            }
            this->_inGroup = true;
        } else
            this->deleteGroup();
        return true;
    }
    return false;
}

bool clt::Ai::notLeaderNoGroupCommunication()
{
     if (!this->_leader && this->_leaderId != 0) {
        this->_leader = false;
        this->sendRequest("JOIN", this->_id, this->_leaderId);
        return true;
    }
    return false;
}

void clt::Ai::moveToLeaderDirection()
{
    if (!this->_isAlive)
        return;

    clearCommandQueue();
    if (this->_direction == 1 || this->_direction == 2 || this->_direction == 8)
        this->goForward();
    if (this->_direction == 2 || this->_direction == 3 || this->_direction == 4) {
        this->turnLeft();
        this->goForward();
    }
    if (this->_direction == 4) {
        this->turnLeft();
        this->goForward();
    }
    if (this->_direction == 5) {
        this->turnLeft();
        this->turnLeft();
        this->goForward();
    }
    if (this->_direction == 8 || this->_direction == 7 || this->_direction == 6) {
        this->turnRight();
        this->goForward();
    }
    if (this->_direction == 6) {
        this->turnRight();
        this->goForward();
    }
    clearCommandQueue();
}

void clt::Ai::sendRequest(std::string action, int id, int targetId)
{
    std::string msg;

    if (!this->_isAlive)
        return;
    if (this->queueIsFull())
        this->clearCommandQueue();

    msg = "TEAM=" + this->_team;
    msg += " LVL=" + std::to_string(this->_level);
    msg += " ID=" + std::to_string(id);
    if (targetId == -1)
        msg += " TargetId=ALL";
    else
        msg += " TargetId=" + std::to_string(targetId);
    msg += " Action=" + action;
    msg += " " + std::to_string(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()));

    this->callBroadcastText(msg);
}

void clt::Ai::deleteGroup()
{
    std::string msg;

    if (!this->_isAlive || !this->_inGroup)
        return;
    for (auto &it: this->_pings)
        this->sendRequest("PING", this->_id, it);
    this->_pings.clear();
    this->sendRequest("DELETE", this->_id, -1);
    this->_leader = false;
    this->_leaderId = 0;
    this->_inGroup = false;
    this->_ready = false;
    this->_dropCommand = false;
    this->_members.clear();
    this->_rejectedMembers.clear();
    this->_leaderId = this->_nextLeaderId;
    this->_nextLeaderId = 0;
    this->_pinged = false;
}