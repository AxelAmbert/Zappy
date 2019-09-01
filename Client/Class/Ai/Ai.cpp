#include "Ai.hpp"

/**
 * @brief Ai CTor
 * @param void
 */
clt::Ai::Ai()
{
    this->_port = 0;
    this->_unusedSlots = 0;
    this->_level = 1;
    this->_isAlive = true;
    this->_isEject = false;
    this->_evolve = false;
    this->_mapX = 0;
    this->_mapY = 0;
    this->_threadIsDone = false;

    this->_id = getpid();
    this->_direction = 0;
    this->_leader = false;
    this->_leaderId = 0;
    this->_nextLeaderId = 0;
    this->_inGroup = false;
    this->_ready = false;
    this->_dropCommand = false;
    this->_pinged = false;

    this->_inventory.emplace(std::pair<std::string, int>("food", 0));
    this->_inventory.emplace(std::pair<std::string, int>("linemate", 0));
    this->_inventory.emplace(std::pair<std::string, int>("deraumere", 0));
    this->_inventory.emplace(std::pair<std::string, int>("sibur", 0));
    this->_inventory.emplace(std::pair<std::string, int>("mendiane", 0));
    this->_inventory.emplace(std::pair<std::string, int>("phiras", 0));
    this->_inventory.emplace(std::pair<std::string, int>("thystame", 0));
    this->setUpLevelUpCondition();
}

/**
 * @brief Ai DTor
 * @param void
 */
clt::Ai::~Ai()
{
    this->clearCommandQueue();
}

/**
 * @brief Ai setUp level Up condition
 * @param void
 */
void clt::Ai::setUpLevelUpCondition()
{
    std::map<std::string, int> condition;

    condition.emplace(std::pair<std::string, int>("player", 1));
    condition.emplace(std::pair<std::string, int>("linemate", 1));
    this->_levelUpCondition.emplace(std::pair<int, std::map<std::string, int>>(1, condition));
    condition.clear();
    condition.emplace(std::pair<std::string, int>("player", 2));
    condition.emplace(std::pair<std::string, int>("linemate", 1));
    condition.emplace(std::pair<std::string, int>("deraumere", 1));
    condition.emplace(std::pair<std::string, int>("sibur", 1));
    this->_levelUpCondition.emplace(std::pair<int, std::map<std::string, int>>(2, condition));
    condition.clear();
    condition.emplace(std::pair<std::string, int>("player", 2));
    condition.emplace(std::pair<std::string, int>("linemate", 2));
    condition.emplace(std::pair<std::string, int>("sibur", 1));
    condition.emplace(std::pair<std::string, int>("phiras", 2));
    this->_levelUpCondition.emplace(std::pair<int, std::map<std::string, int>>(3, condition));
    condition.clear();
    condition.emplace(std::pair<std::string, int>("player", 4));
    condition.emplace(std::pair<std::string, int>("linemate", 1));
    condition.emplace(std::pair<std::string, int>("deraumere", 1));
    condition.emplace(std::pair<std::string, int>("sibur", 2));
    condition.emplace(std::pair<std::string, int>("phiras", 1));
    this->_levelUpCondition.emplace(std::pair<int, std::map<std::string, int>>(4, condition));
    condition.clear();
    condition.emplace(std::pair<std::string, int>("player", 4));
    condition.emplace(std::pair<std::string, int>("linemate", 1));
    condition.emplace(std::pair<std::string, int>("deraumere", 2));
    condition.emplace(std::pair<std::string, int>("sibur", 1));
    condition.emplace(std::pair<std::string, int>("mendiane", 3));
    this->_levelUpCondition.emplace(std::pair<int, std::map<std::string, int>>(5, condition));
    condition.clear();
    condition.emplace(std::pair<std::string, int>("player", 6));
    condition.emplace(std::pair<std::string, int>("linemate", 1));
    condition.emplace(std::pair<std::string, int>("deraumere", 2));
    condition.emplace(std::pair<std::string, int>("sibur", 3));
    condition.emplace(std::pair<std::string, int>("phiras", 1));
    this->_levelUpCondition.emplace(std::pair<int, std::map<std::string, int>>(6, condition));
    condition.clear();
    condition.emplace(std::pair<std::string, int>("player", 6));
    condition.emplace(std::pair<std::string, int>("linemate", 2));
    condition.emplace(std::pair<std::string, int>("deraumere", 2));
    condition.emplace(std::pair<std::string, int>("sibur", 2));
    condition.emplace(std::pair<std::string, int>("mendiane", 2));
    condition.emplace(std::pair<std::string, int>("phiras", 2));
    condition.emplace(std::pair<std::string, int>("thystame", 1));
    this->_levelUpCondition.emplace(std::pair<int, std::map<std::string, int>>(7, condition));
}

/**
 * @brief Clear ALL Commands In Queue
 * @param void
 */
void clt::Ai::clearCommandQueue()
{
    if (this->_commandQueue.empty())
        return;
    while (this->_isAlive && !this->_commandQueue[this->_commandQueue.size() - 1]->getIsDone())
        usleep(10);
    for (auto &it: this->_commandQueue)
        delete(it);
    this->_commandQueue.clear();
}

/**
 * @brief Get Usefull Info For Ai
 * @param int Number Of Args
 * @param char ** Array Containing The Args Passed To The Program
 */
void clt::Ai::getInfo(int ac, char **av)
{
    for (int i = 1; i < ac; i++) {
        if (av[i][1] == 'p')
            this->_port = static_cast<uint16_t >(std::atoi(av[i + 1]));
        if (av[i][1] == 'n')
            this->_team = av[i + 1];
        if (av[i][1] == 'h')
            this->_server = av[i + 1];
    }
}

/**
 * @brief Connect The Ai To The Server
 * @param void
 * @return bool
 */
bool clt::Ai::connectToServer()
{
    this->_server = this->_server.empty() ? std::string("127.0.0.1") : this->_server;
    auto addr = clt::Socket::Address{
        this->_server,
        this->_port
    };
    this->_socket = Socket();
    return !(!this->_socket.createSocket() || !this->_socket.connectTo(addr));
}

/**
 * @brief Send A Message From The Client/Ai To The Server
 * @param std::string Msg To Send
 */
void clt::Ai::sendMsg(std::string msg)
{
    std::cout << "\033[32msend message\033[0m '" << msg << "' to server '" << this->_server << "'." << std::endl;
    msg += "\n";
    this->_socket.send(msg);
}

/**
 * @brief Allow The Ai To Receive A Msg
 * @param void
 */
void clt::Ai::receiveMsg()
{
    this->_buffer.clear();
    this->_buffer = this->_socket.recive();
    this->_buffer.erase(this->_buffer.length() - 1);
//    std::cout << "\033[33mreceive message\033[0m '" << this->_buffer << "' from server '" << this->_server << "'." << std::endl;
}

/**
 * @brief Allow The Ai To Join A Game
 * @param void
 */
void clt::Ai::joinGame()
{
    this->receiveMsg();
    if (!this->sendTeamName()) {
        std::cout << "Ai: " << "Client rejected from server '" << this->_server << "'." << std::endl;
        return;
    }
    if (!this->getMapSize())
        return;
    this->startAiAlgo();
}

/**
 * @brief Send The Team Name To The Server
 * @param void
 * @return bool
 */
bool clt::Ai::sendTeamName()
{
    std::regex resp("^ko");

    this->sendMsg(this->_team);
    this->receiveMsg();
    if (std::regex_match(this->_buffer, resp))
        return false;
    this->_unusedSlots = std::atoi(this->_buffer.c_str());
    return true;
}

/**
 * @brief Allow The Ai To Get The Size Of The Map
 * @param void
 * @return bool
 */
bool clt::Ai::getMapSize()
{
    std::string tmp = this->_buffer;
    std::regex resp("^ko");
    size_t count = std::count(tmp.begin(), tmp.end(), '\n');
    size_t pos = tmp.find('\n');

    if (count == 0) {
        this->receiveMsg();
        tmp = this->_buffer;
        if (std::regex_match(this->_buffer, resp))
            return false;
    } else
        tmp.erase(0, pos);
    this->_mapX = std::atoi(tmp.c_str());
    pos = tmp.find(' ');
    tmp.erase(0, pos);
    this->_mapY = std::atoi(tmp.c_str());

    return true;
}

/**
 * @brief Move the Ai One Tile Ahead
 * @param void
 */
void clt::Ai::goForward()
{
    std::vector<std::regex> regex;
    std::string msg = "Forward";
    std::regex resp("^ok$");

    regex.push_back(resp);
    Command *command = new Command(msg, regex, false);
    this->_commandQueue.push_back(command);
    this->sendMsg(command->getMsg());
}

/**
 * @brief The Ai Rotate 90° To The Right
 * @param void
 */
void clt::Ai::turnRight()
{
    std::vector<std::regex> regex;
    std::string msg = "Right";
    std::regex resp("^ok$");

    regex.push_back(resp);
    Command *command = new Command(msg, regex, false);
    this->_commandQueue.push_back(command);
    this->sendMsg(command->getMsg());
}

/**
 * @brief The Ai Rotate 90° To The Left
 * @param void
 */
void clt::Ai::turnLeft()
{
    std::vector<std::regex> regex;
    std::string msg = "Left";
    std::regex resp("^ok$");

    regex.push_back(resp);
    Command *command = new Command(msg, regex, false);
    this->_commandQueue.push_back(command);
    this->sendMsg(command->getMsg());
}

/**
 * @brief The Ai Look The Tile Surrounding her
 * @param void
 */
void clt::Ai::lookAround()
{
    std::vector<std::regex> regex;
    std::string msg = "Look";
    std::regex resp("^\\[( ?(player|food|linemate|deraumere|sibur|mendiane|phiras|thystame)?,? ?)* ?\\]$");

    regex.push_back(resp);
    Command *command = new Command(msg, regex, true);
    this->_commandQueue.push_back(command);
    this->sendMsg(command->getMsg());
}

/**
 * @brief The Ai At Her Inventory
 * @param void
 */
void clt::Ai::lookInventory()
{
    std::vector<std::regex> regex;
    std::string msg = "Inventory";
    std::regex resp("^\\[( ?(food|linemate|deraumere|sibur|mendiane|phiras|thystame) [0-9]+,?){7} ?\\]$");

    regex.push_back(resp);
    Command *command = new Command(msg, regex, true);
    this->_commandQueue.push_back(command);
    this->sendMsg(command->getMsg());
}

/**
 * @brief The Ai Call The Method BroadCastText
 * @param void
 */
void clt::Ai::callBroadcastText(const std::string &sentence)
{
    std::vector<std::regex> regex;
    std::string msg = "Broadcast " + sentence;
    std::regex resp("^ok$");

    regex.push_back(resp);
    Command *command = new Command(msg, regex, false);
    this->_commandQueue.push_back(command);
    this->sendMsg(command->getMsg());
}

/**
 * @brief The Ai Get All Unused Slot In Her Team
 * @param void
 */
void clt::Ai::lookTeamUnusedSlots()
{
    std::vector<std::regex> regex;
    std::string msg = "Connect_nbr";
    std::regex resp("^[0-9]+$");

    regex.push_back(resp);
    Command *command = new Command(msg, regex, true);
    this->_commandQueue.push_back(command);
    this->sendMsg(command->getMsg());
}

/**
 * @brief The Ai Fork Herself
 * @param void
 */
void clt::Ai::forkPlayer()
{
    std::vector<std::regex> regex;
    std::string msg = "Fork";
    std::regex resp("^ok$");

    regex.push_back(resp);
    Command *command = new Command(msg, regex, false);
    this->_commandQueue.push_back(command);
    this->sendMsg(command->getMsg());
}

/**
 * @brief Eject All The Players On The Tile
 * @param void
 */
void clt::Ai::ejectPlayers()
{
    std::vector<std::regex> regex;
    std::string msg = "Eject";
    std::regex resp("^ok$");
    std::regex resp2("^ko$");

    regex.push_back(resp);
    regex.push_back(resp2);
    Command *command = new Command(msg, regex, false);
    this->_commandQueue.push_back(command);
    this->sendMsg(command->getMsg());
}

/**
 * @brief The Ai Retrieve An Object From The Tile
 * @param std::string Object To Retrieve
 */
void clt::Ai::takeObject(std::string &str)
{
    std::vector<std::regex> regex;
    std::string msg = "Take " + str;
    std::regex resp("^ok$");
    std::regex resp2("^ko$");

    regex.push_back(resp);
    regex.push_back(resp2);
    Command *command = new Command(msg, regex, false);
    this->_commandQueue.push_back(command);
    this->sendMsg(command->getMsg());
}

/**
 * @brief The Ai Put An Object On The Ground
 * @param std::string Object To Put Down
 */
void clt::Ai::setObjectDown(std::string &str)
{
    std::vector<std::regex> regex;
    std::string msg = "Set " + str;
    std::regex resp("^ok$");
    std::regex resp2("^ko$");

    regex.push_back(resp);
    regex.push_back(resp2);
    Command *command = new Command(msg, regex, false);
    this->_commandQueue.push_back(command);
    this->sendMsg(command->getMsg());
}

/**
 * @brief The Ai Start An Incatation
 * @param void
 */
void clt::Ai::startIncantation()
{
    std::vector<std::regex> regex;
    std::string msg = "Incantation";
    std::regex resp("^Elevation underway$");
    std::regex resp2("^Current level: [0-9]+$");
    std::regex resp3("^ko$");

    regex.push_back(resp);
    regex.push_back(resp2);
    Command *command = new Command(msg, regex, false);
    this->_commandQueue.push_back(command);
    this->sendMsg(command->getMsg());
}
