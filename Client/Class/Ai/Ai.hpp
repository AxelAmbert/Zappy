#ifndef AI_HPP
#define AI_HPP

#include <iostream>
#include <string>
#include <cstring>
#include <map>
#include <chrono>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <zconf.h>
#include <regex>
#include <thread>
#include <Socket.hpp>
#include <atomic>

#include "Command.hpp"

namespace clt {
    /**
	* @class Ai
	* @brief Ai class
	*/
    class Ai {
        public:
            Ai();
            Ai(const Ai &) = delete;
            Ai(Ai &&) = delete;
            ~Ai();

            Ai &operator=(const Ai &) = delete;
            Ai &operator=(Ai &&) = delete;

            void clearCommandQueue();
            void getInfo(int ac, char **av);
            bool connectToServer();
            void sendMsg(std::string msg);
            void receiveMsg();
            void joinGame();
            bool sendTeamName();
            bool getMapSize();
            void setUpLevelUpCondition();

            void goForward();
            void turnRight();
            void turnLeft();
            void lookAround();
            void lookInventory();
            void callBroadcastText(const std::string &);
            void lookTeamUnusedSlots();
            void forkPlayer();
            void ejectPlayers();
            void takeObject(std::string &);
            void setObjectDown(std::string &);
            void startIncantation();

            void serverAnswersManagement();
            std::vector<std::string> fillCommandsSameReceive();
            bool receiveDead(std::string &);
            bool receiveEject(std::string &);
            bool receiveBroadcast(std::string &);
            bool receiveIncantation(std::string &);
            bool receiveCurrentLvl(std::string &);
            std::pair<Command *, bool> getTheLastCommand();
            void manageIncantation(std::pair<Command *, bool>, std::string &);
            void serverAnswersSpecialCase(std::pair<Command *, bool>, std::string &, std::string &);
            void parseInventory(std::string &);
            void parseLook(std::string &);

            bool queueIsFull();
            void startAiAlgo();
            void moveToRandomDirection();

            bool tryToLevelUp();
            void leaderLevelUp();
            void notLeaderLevelUp();
            bool hasEnoughStones();
            bool hasEnoughPlayers();
            bool verifEnoughPlayer();
            std::map<std::string, int> &getWhatAiNeedsToLevelUp();
            void takeAllObjectOnTheTile();
            void dropAllObjectToLevelUp();

            bool needFoods();
            void farmObject(const std::string &, int);
            void farmMultipleObjects(std::map<std::string, int> &);
            bool searchAnObject(const std::string &);
            bool searchMultipleObjects(std::map<std::string, int> &);
            bool findObject(std::string);
            int getObjectPos(std::string);

            bool groupCommunication();
            bool leaderGroupCommunication();
            bool notLeaderGroupCommunication();
            bool leaderNoGroupCommunication();
            bool notLeaderNoGroupCommunication();
            void moveToLeaderDirection();
            void sendRequest(std::string, int, int);
            void deleteGroup();

        private:
            Socket _socket;
            std::string _buffer;
            uint16_t _port;
            std::string _team;
            std::string _server;
            int _unusedSlots;
            int _mapX;
            int _mapY;
            bool _threadIsDone;

            std::vector<Command *> _commandQueue;

            std::map<int, std::map<std::string, int>> _levelUpCondition;
            std::atomic<bool> _isAlive;
            int _level;
            bool _evolve;
            std::map<std::string, int> _inventory;
            std::map<int, std::vector<std::string>> _look;
            bool _isEject;
            std::string _ejectFrom;
            std::map<std::string, int> _objects;

            int _id;
            int _direction;
            bool _leader;
            int _leaderId;
            int _nextLeaderId;
            bool _inGroup;
            bool _ready;
            bool _dropCommand;
            bool _pinged;
            std::vector<int> _members;
            std::vector<int> _pings;
            std::vector<int> _rejectedMembers;
    };
}

#endif