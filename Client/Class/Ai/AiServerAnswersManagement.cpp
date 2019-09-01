/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** by mlucas on 03/06/19
*/

#include "Ai.hpp"

/**
 * @brief Stack The Identical command
 * @param void
 * @return std::vector<std::string>
 */
std::vector<std::string> clt::Ai::fillCommandsSameReceive()
{
    std::vector<std::string> vec;
    std::string tmp = this->_buffer;
    std::string str = "";

    while (!tmp.empty()) {
        if (tmp[0] == '\n') {
            vec.push_back(str);
            str = "";
        } else
            str += tmp[0];
        tmp.erase(0, 1);
    }
    if (!str.empty())
        vec.push_back(str);
    return vec;
}

/**
 * @brief Receive Broadcast
 * @param void
 * @return bool
 */
bool clt::Ai::receiveBroadcast(std::string &msg)
{
    std::string tmp = msg;
    std::string tmp2 = msg;
    std::string broadcast("message");
    std::string team("TEAM=" + this->_team);
    std::string lvl("LVL=" + std::to_string(this->_level));
    std::string lvlSup("LVL=" + std::to_string(this->_level + 1));
    std::string id("ID=" + std::to_string(this->_id));
    std::string leaderId("ID=" + std::to_string(this->_leaderId));
    std::string targetAll("TargetId=ALL");
    std::string targetId("TargetId=" + std::to_string(this->_id));
    std::string actionCreate("Action=CREATE");
    std::string actionJoin("Action=JOIN");
    std::string actionDelete("Action=DELETE");
    std::string actionDrop("Action=DROP");
    std::string actionPing("Action=PING");

    if (msg.find(broadcast) == std::string::npos)
        return false;
    if (msg.find(team) == std::string::npos || msg.find(id) != std::string::npos) {
        return true;
    }
    if (msg.find(actionJoin) != std::string::npos && msg.find(targetId) != std::string::npos) {
        if (msg.find(lvl) == std::string::npos && this->_leader) {
            tmp = msg;
            tmp.erase(0, 26 + this->_team.length());
            for (auto &it: this->_rejectedMembers)
                if (it == std::atoi(tmp.c_str()))
                    return true;
            for (auto &it: this->_members)
                if (it == std::atoi(tmp.c_str()))
                    return true;
            this->_rejectedMembers.push_back(std::atoi(tmp.c_str()));
            return true;
        } else if (msg.find(lvl) == std::string::npos && !this->_leader && msg.find(leaderId) != std::string::npos) {
            this->_leader = false;
            this->_leaderId = 0;
            this->_nextLeaderId = 0;
            this->_inGroup = false;
            return true;
        }
    }
    if (msg.find(lvl) == std::string::npos && msg.find(lvlSup) == std::string::npos) {
        return true;
    }
    if (msg.find(lvlSup) != std::string::npos) {
        if (this->_inGroup && this->_evolve && msg.find(actionCreate) != std::string::npos) {
            tmp = msg;
            tmp.erase(0, 26 + this->_team.length());
            this->_nextLeaderId = std::atoi(tmp.c_str());
        }
        return true;
    }
    if (!this->_inGroup && this->_leader && msg.find(actionCreate) != std::string::npos) {
            if (!this->_members.empty())
                return true;
            this->_leaderId = 0;
            this->_leader = false;
            return true;
    }
    if (!this->_inGroup && !this->_leader && msg.find(actionCreate) != std::string::npos) {
        tmp = msg;
        tmp.erase(0, 26 + this->_team.length());
        this->_leaderId = std::atoi(tmp.c_str());
        return true;
    }
    if (msg.find(actionJoin) != std::string::npos) {
        tmp = msg;
        tmp.erase(0, 26 + this->_team.length());
        tmp2 = tmp;
        tmp2.erase(0, std::to_string(std::atoi(tmp.c_str())).length() + 10);
        if (this->_leader) {
            if (msg.find("KO") != std::string::npos)
                return true;
            if ((int)(this->_members.size() + 1) == this->_levelUpCondition[this->_level]["player"]) {
                for (auto &it: this->_rejectedMembers)
                    if (it == std::atoi(tmp.c_str()))
                        return true;
                for (auto &it: this->_members)
                    if (it == std::atoi(tmp.c_str()))
                        return true;
                this->_rejectedMembers.push_back(std::atoi(tmp.c_str()));
            } else {
                for (auto &it: this->_members)
                    if (it == std::atoi(tmp.c_str()))
                        return true;
                this->_members.push_back(std::atoi(tmp.c_str()));
            }
        } else {
            if (this->_id != std::atoi(tmp2.c_str())) {
                return true;
            }
            if ((this->_leaderId == 0 || this->_leaderId == std::atoi(tmp.c_str())) && msg.find("KO") != std::string::npos) {
                this->_leaderId = 0;
                this->_inGroup = false;
                this->_nextLeaderId = 0;
                return true;
            }
            if (msg.find("KO") == std::string::npos) {
                tmp = msg;
                tmp.erase(0, 8);
                this->_direction = std::atoi(tmp.c_str());
                this->_inGroup = true;
            }
        }
    }
    if (this->_inGroup && !this->_leader && msg.find(leaderId) != std::string::npos) {
        if (msg.find(actionDelete) != std::string::npos) {
            this->_inGroup = false;
            this->_ready = false;
            this->_leaderId = 0;
            this->_dropCommand = false;
            this->_direction = 0;
            this->_members.clear();
            this->_rejectedMembers.clear();
            this->_leaderId = this->_nextLeaderId;
            this->_nextLeaderId = 0;
            this->_pinged = false;
            return true;
        }
        if (msg.find(actionDrop) != std::string::npos) {
            this->_dropCommand = true;
            return true;
        }
    }
    if (msg.find(actionPing) != std::string::npos) {
        tmp = msg;
        tmp.erase(0, 8);
        if (this->_leader && msg.find(targetId) != std::string::npos) {
            tmp = msg;
            tmp.erase(0, 26 + this->_team.length());
            for (auto &it: this->_pings)
                if (it == std::atoi(tmp.c_str()))
                    return true;
            this->_pings.push_back(std::atoi(tmp.c_str()));
        } else if (msg.find(leaderId) != std::string::npos) {
            this->_direction = std::atoi(tmp.c_str());
            this->_pinged = true;
        }
    }
    return true;
}

/**
 * @brief Receive Death Signal
 * @param void
 * @return bool
 */
bool clt::Ai::receiveDead(std::string &msg)
{
    std::regex dead("^dead$");

    if (std::regex_match(msg, dead)) {
        this->_isAlive = false;
        std::cout << "I'm dead !" << std::endl;
        return true;
    }
    return false;
}

/**
 * @brief Receive Eject Signal
 * @param void
 * @return bool
 */
bool clt::Ai::receiveEject(std::string &msg)
{
    std::regex eject("^eject: [0-9]$");

    if (std::regex_match(msg, eject)) {
        this->_isEject = true;
        this->_ejectFrom = this->_buffer.erase(0, 7);
        return true;
    }
    return false;
}

/**
 * @brief Receive Incantation Signal
 * @param void
 * @return bool
 */
bool clt::Ai::receiveIncantation(std::string &msg)
{
    std::regex incantation("^Elevation underway");

    if (std::regex_match(msg, incantation)) {
        this->_evolve = true;
        return true;
    }
    return false;
}

/**
 * @brief Receive Current Lvl
 * @param void
 * @return bool
 */
bool clt::Ai::receiveCurrentLvl(std::string &msg)
{
    std::string lvl("Current level: ");
    std::string tmp = msg;

    if (this->_level > 1 && !this->_leader && msg.find(lvl) != std::string::npos) {
        tmp.erase(0, 15);
        this->_level = std::atoi(tmp.c_str());
        return true;
    }
    return false;
}

/**
 * @brief Get The Last Command Sent
 * @param void
 * @return std::pair<clt::Command *, bool>
 */
std::pair<clt::Command *, bool> clt::Ai::getTheLastCommand()
{
    std::pair<Command *, bool> tmp;

    for (auto &command: this->_commandQueue) {
        if (command->getIsDone())
            continue;
        tmp.first = command;
        tmp.second = true;
        return tmp;
    }
    tmp.first = new Command();
    tmp.second = false;
    return tmp;
}

/**
 * @brief Handle The Server Answer
 * @param void
 */
void clt::Ai::serverAnswersManagement()
{
    std::string lastBuffer;
    std::pair<Command *, bool> command;
    std::vector<std::string> commandsSameReceive;

    while (this->_isAlive) {
        commandsSameReceive.clear();
        this->receiveMsg();
        commandsSameReceive = fillCommandsSameReceive();
        for (int i = 0; this->_isAlive && i < (int)commandsSameReceive.size(); i++) {
            std::cout << "\033[34mCommand\033[0m = " << commandsSameReceive[i] << std::endl;
            if (this->receiveDead(commandsSameReceive[i]) || this->receiveEject(commandsSameReceive[i])
            || this->receiveBroadcast(commandsSameReceive[i]) || this->receiveIncantation(commandsSameReceive[i])
            || this->receiveCurrentLvl(commandsSameReceive[i]))
                continue;
            command = getTheLastCommand();
            if (!command.second) {
                this->clearCommandQueue();
                continue;
            }
            if (command.first->getMsg() == "Incantation" || this->_evolve) {
                this->manageIncantation(command, commandsSameReceive[i]);
            } else if (command.first->getSpecial()) {
                serverAnswersSpecialCase(command, commandsSameReceive[i], lastBuffer);
            } else {
                command.first->setSuccess(std::regex_match(commandsSameReceive[i], command.first->getRegex()[0]));
                command.first->setIsDone(true);
            }
            lastBuffer = commandsSameReceive[i];
        }
    }
    this->_threadIsDone = true;
}

void clt::Ai::manageIncantation(std::pair<Command *, bool> command, std::string &msg)
{
    std::regex ko("^ko$");

    command.first->setSuccess(false);
    if (this->_evolve) {
        if (msg.find("Current level:") != std::string::npos) {
            command.first->setSuccess(true);
            msg.erase(0, 15);
            if (this->_level ==  std::atoi(msg.c_str()))
                command.first->setSuccess(false);
            else
                this->_level = std::atoi(msg.c_str());
        } else
            command.first->setSuccess(false);
        this->_evolve = false;
        command.first->setIsDone(true);
    } else {
        if (std::regex_match(msg, ko))
            this->_evolve = true;
    }
}

/**
 * @brief Handle The Special Answer From The Server
 * @param std::pair<Command *, bool> Special Case To Handle
 */
void clt::Ai::serverAnswersSpecialCase(std::pair<Command *, bool> command, std::string &msg, std::string &last)
{
    bool valid = false;

    for (auto &it : command.first->getRegex()) {
        if (std::regex_match(msg, it))
            valid = true;
    }
    if (!valid && command.first->getBug()) {
        msg = last + msg;
        if (!std::regex_match(msg, command.first->getRegex()[0])) {
            command.first->setSuccess(false);
            command.first->setIsDone(true);
            return;
        }
    } else if (!valid && !command.first->getBug()) {
        command.first->setBug(true);
        return;
    }
    if (!std::regex_match(msg, command.first->getRegex()[0])) {
        command.first->setSuccess(false);
        command.first->setIsDone(true);
        return;
    }
    command.first->setSuccess(true);
    if (command.first->getMsg() == "Inventory")
        this->parseInventory(msg);
    if (command.first->getMsg() == "Look")
        this->parseLook(msg);
    if (command.first->getMsg() == "Connect_nbr")
        this->_unusedSlots = std::atoi(msg.c_str());
    command.first->setIsDone(true);
}

/**
 * @brief Parse The Result Of The Inventory Command
 * @param void
 */
void clt::Ai::parseInventory(std::string &msg)
{
    std::vector<std::string> vec;
    std::string tmp = msg;
    std::string str = "";

    while (!isalpha(tmp[0]))
        tmp.erase(0, 1);
    while (!isdigit(tmp[tmp.length() - 1]))
        tmp.erase(tmp.length() - 1);
    while (!tmp.empty()) {
        if (tmp[0] == ',') {
            vec.push_back(str);
            str = "";
        } else
            str += tmp[0];
        tmp.erase(0, 1);
    }
    vec.push_back(str);
    for (auto &it: vec) {
        str = "";
        while (!isalpha(it[0]))
            it.erase(0, 1);
        while (!isdigit(it[it.length() - 1]))
            it.erase(it.length() - 1);
        while (it[0] != ' ') {
            str += it[0];
            it.erase(0, 1);
        }
        it.erase(0, 1);
        this->_inventory[str] = std::atoi(it.c_str());
    }
}

/**
 * @brief Parse The Result From The Look Command
 * @param void
 */
void clt::Ai::parseLook(std::string &msg)
{
    std::vector<std::string> vec;
    std::string tmp = msg;
    std::string str = "";
    int nb = 0;

    this->_look.clear();
    while (!isalpha(tmp[0]) && tmp[0] != ',')
        tmp.erase(0, 1);
    while (!isalpha(tmp[tmp.length() - 1]) && tmp[tmp.length() - 1] != ',')
        tmp.erase(tmp.length() - 1);
    while (!tmp.empty()) {
        if (tmp[0] == ',') {
            vec.push_back(str);
            str = "";
        } else
            str += tmp[0];
        tmp.erase(0, 1);
    }
    vec.push_back(str);
    for (auto &it: vec) {
        while (!it.empty() && !isalpha(it[0]))
            it.erase(0, 1);
        while (!it.empty() && !isalpha(it[it.length() - 1]))
            it.erase(it.length() - 1);
        this->_look.emplace(std::pair<int, std::vector<std::string>>(nb, std::vector<std::string>()));
        str = "";
        while (!it.empty()) {
            if (it[0] == ' ') {
                this->_look[nb].push_back(str);
                str = "";
            } else
                str += it[0];
            it.erase(0, 1);
        }
        if (!str.empty())
            this->_look[nb].push_back(str);
        nb++;
    }
}