#include "../include/commandHandler.hpp"
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include "../include/zappy.hpp"

/**
 * @brief CommandHandler CTor
 * @param graphical::tcpCommunication &
 */
CommandHandler::CommandHandler(graphical::tcpCommunication &tcpCommunication, size_t &_sceneIndex) : Communication(tcpCommunication), sceneIndex(_sceneIndex)
{
    commandFunction.insert(
            {"forward", &graphical::player::forward}
    );
    commandFunction.insert(
            {"ppo", &graphical::player::ppo}
    );
    commandFunction.insert(
            {"pex", &graphical::player::pex}
    );
    commandFunction.insert(
            {"pdi", &graphical::player::pdi}
    );
    commandFunction.insert(
            {"pfk", &graphical::player::pfk}
    );
    commandFunction.insert(
            {"pbc", &graphical::player::pbc}
    );
    commandFunction.insert(
            {"pie", &graphical::player::pie}
    );
    commandFunction.insert(
            {"pic", &graphical::player::pic}
    );
}

/**
 * @brief Function setter for player
 * @param std::string
 * @param graphical::zappy &
 */
void CommandHandler::setFunctionInPlayer(std::string &receivedCommand, graphical::zappy &zappy)
{
    std::string func = receivedCommand.substr(0, receivedCommand.find_first_of(' '));
    if (func == "JeDeadCaChacal")
        sceneIndex = 0;
    receivedCommand.erase(0, receivedCommand.find_first_of(' ') + 1);
    std::optional<graphical::player*> player = zappy.findAPlayer(receivedCommand.substr(0, receivedCommand.find_first_of(' ')));

    std::map<std::string, std::function<void(std::string &, graphical::zappy &)>> spetialCase;
    spetialCase.insert(
            {"eht", [](std::string &receivedCommand, graphical::zappy &zappy){zappy.hatchingOfAnEgg(receivedCommand);}}
    );
    spetialCase.insert(
            {"edi", [](std::string &receivedCommand, graphical::zappy &zappy){zappy.deleteThisEgg(receivedCommand);}}
    );
    spetialCase.insert(
            {"pin", [](std::string &receivedCommand, graphical::zappy &zappy)
            {
                graphical::PlayersInfosGUI &playersInfosGUI = zappy.getPlayersInfosGUI();
                playersInfosGUI.addNewInventoryInformations(receivedCommand);
            }}
    );
    spetialCase.insert(
            {"pgt", [](std::string &receivedCommand, graphical::zappy &zappy)
            {
                graphical::player::pgt(zappy.getMap(), receivedCommand);
            }}
    );
    spetialCase.insert(
            {"pdr", [](std::string &receivedCommand, graphical::zappy &zappy)
            {
                graphical::player::pdr(zappy.getMap(), receivedCommand);
            }}
    );
    spetialCase.insert(
            {"pwn", [](std::string &receivedCommand, graphical::zappy &zappy)
            {
                zappy.setPlayers({receivedCommand});
            }}
    );
    spetialCase.insert(
            {"chat", [](std::string &receivedCommand, graphical::zappy &zappy)
            {
                zappy.chat({receivedCommand});
            }}
            );
    spetialCase.insert(
            {"tg", [](std::string &receivedCommand, graphical::zappy &zappy)
            {
                zappy.tg({receivedCommand});
            }}
    );
    try {
        spetialCase.at(func)(receivedCommand, zappy);
        return;
    } catch (std::out_of_range &) {
        if (player.has_value()) {
            try {
                player.value()->addFunction(commandFunction.at(func), receivedCommand);
            } catch (std::out_of_range &) {

            }
        }

    }
}

/**
 * @brief Command getter
 * @param graphical::zappy
 */
void CommandHandler::getNewCommands(graphical::zappy &zappy)
{
    Communication.setReadTimeOut(0, 1000);
    while (Communication.updateReadAvailability()) {
        std::string tmp = Communication.get();
        std::vector<std::string> newCommands = stringManager::my_str_to_word_array(tmp, "\n");
        for (auto it = newCommands.begin(); it != newCommands.end(); it++) {
            setFunctionInPlayer(*it, zappy);
        }
    }
}