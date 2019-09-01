#include "../include/player.hpp"
#include "../include/zappy.hpp"

/**
 * @brief Team name getter
 * @param void
 * @return std::string
 */
std::string graphical::player::getTeamName()
{
    return (teamName);
}

/**
 * @brief Method to add the value contained by two pair
 * @param std::pair<T, T> &
 * @param std::pair<T, T> &
 * @return std::pair<T, T>
 */
template <typename T>
std::pair<T, T> addTwoPair(const std::pair<T, T> &one, const std::pair<T, T> &two)
{
    std::pair<T, T> tmpPair = {one.first + two.first, one.second + two.second};

    return (tmpPair);
}

/**
 * @brief player CTor
 * @param std::vector <std::string>
 * @param graphical::animation *
 * @param int
 * @param int
 * @param sf::RectangleShape &
 * @param sf::Font &
 */
graphical::player::player(std::vector<std::string> info, graphical::animation *_playerAsset, int _posX, int _posY, sf::RectangleShape &_broadcast, sf::Font &_fontLvl) : playerAsset(_playerAsset), broadcast(&_broadcast), obfuscation(false)
{
    nb = info[0];
    orientation = info[3];
    orientation = info[3];
    teamName = info[5];
    level = atoi(info[4].c_str());

    position.first = _posX * TILE_X;
    textLvl.setFont(_fontLvl);
    textLvl.setFillColor(sf::Color::Red);
    textLvl.setCharacterSize(35);
    textLvl.setString(std::to_string(level));
    position.second = _posY * TILE_Y;
    tilePosition.first = _posX;
    tilePosition.second = _posY;
    positionDestination = 0;
    playerAsset->stopTheAnimation(true);
    firstCall = true;
    orientationMap.insert(std::pair<std::string, int>("UP", 0));
    orientationMap.insert(std::pair<std::string, int>("LEFT", 1));
    orientationMap.insert(std::pair<std::string, int>("DOWN", 2));
    orientationMap.insert(std::pair<std::string, int>("RIGHT", 3));
}

/**
 * @brief Method to set view obfuscation
 * @param bool
 */
void graphical::player::setViewObfuscation(bool _obfuscation)
{
    obfuscation = _obfuscation;
}

bool graphical::player::getObfuscation()
{
    return obfuscation;
}

bool graphical::player::noPlayerObfuscated(std::vector<graphical::player> &list)
{
    for (auto it = list.begin(); it != list.end();it++) {
        if (it->getObfuscation())
            return false;
    }
    return true;
}

/**
 * @brief Method to draw the player
 * @param sf::RenderWindow &
 * @param std::vector<std::vector<graphical::tile>> &
 * @param sf::vector2f
 * @param graphical::tcpCommunication &
 * @param graphical::zappy &
 */
void graphical::player::draw(sf::RenderWindow &window, std::vector<std::vector<graphical::tile>> &map, sf::Vector2f boardPos, graphical::tcpCommunication &communication, graphical::zappy &zappy)
{
    truePosition = boardPos;
    if (playerAsset->currentLine(90) != 4)
        playerAsset->setYPos(90 * orientationMap[orientation]);
    if (!functionList.empty()) {
        if ((*this.*functionList[0].first)(map, functionList[0].second, zappy))
            return;
    }
    if (obfuscation || noPlayerObfuscated(zappy.getPlayers())) {
        playerAsset->draw(window, boardPos);
        textLvl.setPosition(boardPos);
        window.draw(textLvl);
    }

    if ((int)clock.getElapsedTime().asMicroseconds() >= 1000000 / frequency) {
        std::string send = "ppo ";
        send += nb;
        send += "\n";
        communication.send(send);
        clock.restart();
    }
}

/**
 * @brief Position getter
 * @param void
 * @return std::pair<int,int>
 */
std::pair<int, int> graphical::player::getPosition()
{
    return position;
}

/**
 * @brief Method to ma<ke the player go forward
 * @param std::vector<std::vector<graphical::tile>> &
 * @param std::string
 * @param graphical::zappy &
 * @return bool
 */
bool graphical::player::forward(std::vector<std::vector<graphical::tile>> &map, [[maybe_unused]]std::string arg, [[maybe_unused]]graphical::zappy &zappy)
{
    std::pair<int, int> tileDirection;
    std::vector<std::string> nextPosition = stringManager::my_str_to_word_array(arg, " ");
    int x = atoi(nextPosition[1].c_str());
    int y = atoi(nextPosition[2].c_str());

    tileDirection.first = 0;
    tileDirection.second = 0;
    if (tilePosition.first > x)
        tileDirection.first = -1 * frequency;
    if (tilePosition.first < x || (x == 0 &&
            static_cast<size_t>(tilePosition.first) == map[0].size() - 1))
        tileDirection.first = 1 * frequency;
    if (static_cast<size_t>(x) == map[0].size() - 1 && tilePosition.first == 0)
        tileDirection.first = -1 * frequency;
    if (tilePosition.second > y)
        tileDirection.second = -1 * frequency;
    if (tilePosition.second < y || (y == 0 && static_cast<size_t>(tilePosition.second) == map.size() - 1))
        tileDirection.second = 1 * frequency;
    if (static_cast<size_t>(y) == map.size() - 1 && tilePosition.second == 0)
        tileDirection.second = -1 * frequency;
    std::pair<int, int> direction(tileDirection);

    if (positionDestination == 0) {
        forwardClock.restart();
        playerAsset->stopTheAnimation(false);
        if (tileDirection.first == 0)
            positionDestination = TILE_Y - 2;
        else
            positionDestination = TILE_X - 2;
    }
    if ((int)forwardClock.getElapsedTime().asMicroseconds() >= 1000) {
        position = addTwoPair(position, direction);
        forwardClock.restart();
    }
    if (direction.first == 0)
        positionDestination -= std::abs(direction.second);
    else
        positionDestination -= std::abs(direction.first);
    if (positionDestination <= 0) {
        map[tilePosition.second][tilePosition.first].delPlayer();
        tilePosition = addTwoPair(tilePosition, {tileDirection.first / frequency, tileDirection.second / frequency});
        tilePosition.first = mathematicalOperations::safeModulo(tilePosition.first, map[0].size());
        tilePosition.second = mathematicalOperations::safeModulo(tilePosition.second, map.size());
        positionDestination = 0;
        map[tilePosition.second][tilePosition.first].addPlayer();
        functionList.erase(functionList.begin());
        playerAsset->stopTheAnimation(true);
    }
    return false;
}

/**
 * @brief Method to get player position
 * @param std::vector<std::vector<graphical::tile>> &
 * @param std::string
 * @param graphical::zappy &
 * @return bool
 */
bool graphical::player::ppo([[maybe_unused]]std::vector<std::vector<graphical::tile>> &map,
                            std::string arg, [[maybe_unused]]graphical::zappy &zappy)
{
    std::vector<std::string> splitedArg = stringManager::my_str_to_word_array(arg, " ");
    orientation = splitedArg[3];
    functionList.erase(functionList.begin());
    return false;
}

/**
 * @brief Number getter
 * @param void
 * @return std::string
 */
std::string &graphical::player::getNb()
{
    return nb;
}

/**
 * @brief Method to add a function to a function list
 * @param bool(graphical::player::*func)(std::vector<std::vector<graphical::tile>> &, std::string, graphical::zappy &)
 * @param std::string
 */
void graphical::player::addFunction(bool(graphical::player::*func)(std::vector<std::vector<graphical::tile>> &, std::string, graphical::zappy &), std::string arg)
{
    functionList.push_back({func, arg});

}

/**
 * @brief Method for ressource collecting
 * @param std::vector<std::vector<graphical::tile>> &
 * @param std::string
 * @param graphical::zappy &
 * @return bool
 */
void graphical::player::pgt(std::vector<std::vector<graphical::tile>> &map,
                            std::string arg)
{
    std::vector<std::string> tmp = stringManager::my_str_to_word_array(arg, "\n");
    std::vector<std::string> pos = stringManager::my_str_to_word_array(tmp[0], " ");
    int x = atoi(pos[0].c_str());
    int y = atoi(pos[1].c_str());
    map[y][x].deleteThisItem(pos[2]);
}

/**
 * @brief Method to expulse a player from a tile
 * @param std::vector<std::vector<graphical::tile>> &
 * @param std::string
 * @param graphical::zappy &
 * @return bool
 */
bool graphical::player::pex(std::vector<std::vector<graphical::tile>> &,
                            std::string arg, [[maybe_unused]]graphical::zappy &zappy)
{
    std::vector<std::string> pos = stringManager::my_str_to_word_array(stringManager::my_str_to_word_array(arg, "\n")[0], " ");
    std::vector<std::string> positionBegin = stringManager::my_str_to_word_array(pos[2], "-");
    std::vector<std::string> positionEnd = stringManager::my_str_to_word_array(pos[3], "-");
    std::pair<int, int> pairEndPos = {atoi(positionEnd[0].c_str()), atoi(positionEnd[1].c_str())};

    tilePosition = pairEndPos;
    position.first = tilePosition.first * TILE_X;
    position.second = tilePosition.second * TILE_Y;
    functionList.erase(functionList.begin());
    return false;
}

/**
 * @brief Method for player death
 * @param std::vector<std::vector<graphical::tile>> &
 * @param std::string
 * @param graphical::zappy &
 * @return bool
 */
bool graphical::player::pdi(std::vector<std::vector<graphical::tile>> &map,
                            std::string arg, graphical::zappy &zappy)
{
    stringManager::clearStr(arg, '\n');
    map[tilePosition.second][tilePosition.first].delPlayer();
    zappy.deleteThisPlayer(arg);
    return true;
}

/**
 * @brief Method for egg laying by the player
 * @param std::vector<std::vector<graphical::tile>> &
 * @param std::string
 * @param graphical::zappy &
 * @return bool
 */
bool graphical::player::pfk(std::vector<std::vector<graphical::tile>> &map,
        std::string arg, graphical::zappy &)
{
    stringManager::clearStr(arg, '\n');
    std::vector<std::string> position = stringManager::my_str_to_word_array(arg, " ");
    map[atoi(position[3].c_str())][atoi(position[2].c_str())].addItem(7, position[1]);
    functionList.erase(functionList.begin());
    return false;
}

/**
 * @brief Method for broadcast
 * @param std::vector<std::vector<graphical::tile>> &
 * @param std::string
 * @param graphical::zappy &
 * @return bool
 */
bool graphical::player::pbc(std::vector<std::vector<graphical::tile>> &,
                            std::string, graphical::zappy &zappy)
{
    if (firstCall)
        broadClock.restart();
    firstCall = false;
    sf::RenderWindow &tmp = zappy.getWindow();
    broadcast->setPosition({truePosition.x + 50, truePosition.y - 50});
    tmp.draw(*broadcast);
    if ((int)broadClock.getElapsedTime().asSeconds() >= 2 / frequency) {
        functionList.erase(functionList.begin());
        firstCall = true;
    }
    return false;
}

/**
 * @brief Frequency setter
 * @param int
 */
void graphical::player::setFrequency(int _frequency)
{
    frequency = _frequency;
}

/**
 * @brief Method for ressource collecting
 * @param std::vector<std::vector<graphical::tile>> &
 * @param std::string
 * @param graphical::zappy &
 * @return bool
 */
void graphical::player::pdr(std::vector<std::vector<graphical::tile>> &map,
                            std::string arg)
{
    std::vector<std::string> tmp = stringManager::my_str_to_word_array(arg, "\n");
    std::vector<std::string> pos = stringManager::my_str_to_word_array(tmp[0], " ");
    int x = atoi(pos[0].c_str());
    int y = atoi(pos[1].c_str());
    map[y][x].addItem(pos[2]);
}

/**
 * @brief Method for ressource collecting
 * @param std::vector<std::vector<graphical::tile>> &
 * @param std::string
 * @param graphical::zappy &
 * @return bool
 */
bool graphical::player::pie(std::vector<std::vector<graphical::tile>> &,
                            std::string, [[maybe_unused]]graphical::zappy &zappy)
{
    playerAsset->setYPos(0);
    playerAsset->setNbrOfElements(9);
    playerAsset->stopTheAnimation(true);
    level += 1;
    textLvl.setString(std::to_string(level));
    functionList.erase(functionList.begin());
    return false;

}

/**
 * @brief Method for ressource collecting
 * @param std::vector<std::vector<graphical::tile>> &
 * @param std::string
 * @param graphical::zappy &
 * @return bool
 */
bool graphical::player::pic(std::vector<std::vector<graphical::tile>> &,
                           std::string, [[maybe_unused]]graphical::zappy &zappy)
{
    playerAsset->setYPos(90 * 4);
    playerAsset->stopTheAnimation(false);
    playerAsset->setNbrOfElements(7);
    functionList.erase(functionList.begin());
    return false;
}

void graphical::player::iDrawLookedTile(std::vector<std::vector<graphical::tile>> &map, sf::RenderWindow &window, std::unique_ptr<rectangle_t> &tileCase, sf::Vector2f &position)
{
    int tmpLevel = 1;
    int idx = mathematicalOperations::safeModulo(((int) position.x / TILE_X + (tilePosition.first)), map[0].size());
    int idy = mathematicalOperations::safeModulo(((int) position.y / TILE_Y + (tilePosition.second)), map.size());

    map[tilePosition.second][tilePosition.first].draw(window, sf::Vector2f((idx * (TILE_X) + (((int) position.x) % TILE_X)) - 200, ((idy * (TILE_Y)) + ((int) position.y) % TILE_Y) - 100), tileCase);
    while (tmpLevel <= level) {
        if (orientation == "UP") {
            idy = mathematicalOperations::safeModulo(((int) position.y / TILE_Y + (mathematicalOperations::safeModulo(tilePosition.second - tmpLevel, map.size()))), map.size());
            for (int i = 0 - tmpLevel; i <= tmpLevel; i++) {
                idx = mathematicalOperations::safeModulo(((int) position.x / TILE_X + (mathematicalOperations::safeModulo(tilePosition.first + i, map[0].size()))), map[0].size());
                map[mathematicalOperations::safeModulo(tilePosition.second - tmpLevel, map.size())][mathematicalOperations::safeModulo(tilePosition.first + i, map[0].size())].draw(window, sf::Vector2f((idx * (TILE_X) + (((int) position.x) % TILE_X)) - 200, ((idy * (TILE_Y)) + ((int) position.y) % TILE_Y) - 100), tileCase);
            }
        }
        if (orientation == "DOWN") {
            idy = mathematicalOperations::safeModulo(((int) position.y / TILE_Y + (mathematicalOperations::safeModulo(tilePosition.second + tmpLevel, map.size()))), map.size());
            for (int i = 0 - tmpLevel; i <= tmpLevel; i++) {
                idx = mathematicalOperations::safeModulo(((int) position.x / TILE_X + (mathematicalOperations::safeModulo(tilePosition.first + i, map[0].size()))), map[0].size());
                map[mathematicalOperations::safeModulo(tilePosition.second + tmpLevel, map.size())][mathematicalOperations::safeModulo(tilePosition.first + i, map[0].size())].draw(window, sf::Vector2f((idx * (TILE_X) + (((int) position.x) % TILE_X)) - 200, ((idy * (TILE_Y)) + ((int) position.y) % TILE_Y) - 100), tileCase);
            }
        }
        if (orientation == "LEFT") {
            idx = mathematicalOperations::safeModulo(((int) position.x / TILE_X + (mathematicalOperations::safeModulo(tilePosition.first - tmpLevel, map[0].size()))), map[0].size());
            for (int i = 0 - tmpLevel; i <= tmpLevel; i++) {
                idy = mathematicalOperations::safeModulo(((int) position.y / TILE_Y + (mathematicalOperations::safeModulo(tilePosition.second + i, map.size()))), map.size());
                map[mathematicalOperations::safeModulo(tilePosition.second + i, map.size())][mathematicalOperations::safeModulo(tilePosition.first - tmpLevel, map[0].size())].draw(window, sf::Vector2f((idx * (TILE_X) + (((int) position.x) % TILE_X)) - 200, ((idy * (TILE_Y)) + ((int) position.y) % TILE_Y) - 100), tileCase);
            }
        }
        if (orientation == "RIGHT") {
            idx = mathematicalOperations::safeModulo(((int) position.x / TILE_X + (mathematicalOperations::safeModulo(tilePosition.first + tmpLevel, map[0].size()))), map[0].size());
            for (int i = 0 - tmpLevel; i <= tmpLevel; i++) {
                idy = mathematicalOperations::safeModulo(((int) position.y / TILE_Y + (mathematicalOperations::safeModulo(tilePosition.second + i, map.size()))), map.size());
                map[mathematicalOperations::safeModulo(tilePosition.second + i, map.size())][mathematicalOperations::safeModulo(tilePosition.first + tmpLevel, map[0].size())].draw(window, sf::Vector2f((idx * (TILE_X) + (((int) position.x) % TILE_X)) - 200, ((idy * (TILE_Y)) + ((int) position.y) % TILE_Y) - 100), tileCase);
            }
        }
        tmpLevel++;
    }
}