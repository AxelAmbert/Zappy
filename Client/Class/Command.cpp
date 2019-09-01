#include <utility>

/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** by mlucas on 03/06/19
*/

#include "Command.hpp"

/**
 * @brief Command Ctor
 * @param std::string Msg
 * @param std::vector<std::regex> Regex To Match The Msg
 * @param bool
 */
clt::Command::Command(std::string &msg, std::vector<std::regex> regex, bool special) : _msg(msg), _regex(std::move(regex))
{
    this->_special = special;
    this->_success = false;
    this->_isDone = false;
    this->_bug = false;
}

/**
 * @brief Message setter
 * @param std::string Message to set
 */
void clt::Command::setMsg(std::string &msg)
{
    this->_msg = msg;
}

/**
 * @brief Regex setter
 * @param std::vector<std::regex>
 */
void clt::Command::setRegex(std::vector<std::regex> regex)
{
    this->_regex = std::move(regex);
}

/**
 * @brief Special command setter
 * @param bool
 */
void clt::Command::setSpecial(bool value)
{
    this->_special = value;
}

/**
 * @brief Success status setter
 * @param bool
 */
void clt::Command::setSuccess(bool value)
{
    this->_success = value;
}

/**
 * @brief Set either the command is done or not
 * @param bool
 */
void clt::Command::setIsDone(bool value)
{
    this->_isDone = value;
}

/**
 * @brief Bug State bool getter
 * @param void
 * @return bool
 */
void clt::Command::setBug(bool value)
{
    this->_bug = value;
}

/**
 * @brief Message getter
 * @param void
 * @return std::string
 */
std::string clt::Command::getMsg() const
{
    return this->_msg;
}

/**
 * @brief Regex getter
 * @param void
 * @return std::vector<std::regex>
 */
std::vector<std::regex> clt::Command::getRegex() const
{
    return this->_regex;
}

/**
 * @brief Special bool getter
 * @param void
 * @return bool
 */
bool clt::Command::getSpecial() const
{
    return this->_special;
}

/**
 * @brief Success State bool getter
 * @param void
 * @return bool
 */
bool clt::Command::getSuccess() const
{
    return this->_success;
}

/**
 * @brief Is the command done or not getter
 * @param void
 * @return bool
 */
bool clt::Command::getIsDone() const
{
    return this->_isDone;
}

/**
 * @brief Bug state getter
 * @param void
 * @return bool
 */
bool clt::Command::getBug() const
{
    return this->_bug;
}