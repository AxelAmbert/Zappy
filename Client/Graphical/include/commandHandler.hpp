#ifndef MYARPSPOOF_COMMANDHANDLER_HPP
#define MYARPSPOOF_COMMANDHANDLER_HPP

#include <iostream>
#include <string>
#include <list>
#include <vector>
#include "../tools/include/tcpCommunication.hpp"
#include "tile.hpp"
#include <thread>
#include <atomic>
#include <mutex>
#include <map>
#include <functional>
#include <optional>

namespace graphical {
    class zappy;
}
/**
 * @class CommandHandler
 * @brief CommandHandler class
 */
class CommandHandler {
    public:
        CommandHandler(graphical::tcpCommunication &tcpCommunication, size_t &_sceneIndex);
        void getNewCommands(graphical::zappy &);
        void setFunctionInPlayer(std::string &receivedCommand, graphical::zappy &zappy);
    private:
        graphical::tcpCommunication &Communication;
        fd_set server_set;
        timeval timeout;
        size_t &sceneIndex;
        int socket;
        std::map<std::string, bool(graphical::player::*)(std::vector<std::vector<graphical::tile>> &, std::string, graphical::zappy &)> commandFunction;
};

#endif //MYARPSPOOF_COMMANDHANDLER_HPP
