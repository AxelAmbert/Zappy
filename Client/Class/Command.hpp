/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** by mlucas on 03/06/19
*/

#ifndef PSU_ZAPPY_2018_COMMAND_HPP
#define PSU_ZAPPY_2018_COMMAND_HPP

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <regex>

namespace clt {
         /**
        * @class Command
        * @brief Command class
        */
        class Command {
            public:
            Command() = default;
            Command(std::string &, std::vector<std::regex>, bool);
            ~Command() = default;

            void setMsg(std::string &);
            void setRegex(std::vector<std::regex>);
            void setSpecial(bool);
            void setSuccess(bool);
            void setIsDone(bool);
            void setBug(bool);

            std::string getMsg() const;
            std::vector<std::regex> getRegex() const;
            bool getSuccess() const;
            bool getSpecial() const;
            bool getIsDone() const;
            bool getBug() const;

        private:
            std::string _msg;
            std::vector<std::regex> _regex;
            bool _special;
            bool _success;
            bool _isDone;
            bool _bug;
        };
}

#endif //PSU_ZAPPY_2018_COMMAND_HPP
