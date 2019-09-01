#include "../include/zappy.hpp"
#include "../include/commandHandler.hpp"
#include "../include/tilesInfosGUI.hpp"
#include <thread>
#include <mutex>
#include <atomic>

void graphical::zappy::tg(std::string)
{
    background.stop();
}

void graphical::zappy::setUsername(std::string username)
{
    communication.send("chat /setuser " + username + "\n");
}

/**
 * @brief Player info getter
 * @param void
 */
graphical::PlayersInfosGUI &graphical::zappy::getPlayersInfosGUI()
{
    return (playersInfosGUI);
}

/**
 * @brief Map size getter
 * @param graphical::tcpCommunication
 * @return std::pair<int, int>
 */
std::pair<int, int> graphical::zappy::getMapSize(graphical::tcpCommunication communication)
{
    communication.send("msz\n");
    std::string mapSize;
    do {
        mapSize = communication.get();
    } while (mapSize.find("msz") == std::string::npos);
    std::vector<std::string> vec = stringManager::my_str_to_word_array(mapSize, " ");
    return {atoi(vec[1].c_str()), atoi(vec[2].c_str())};
}

/**
 * @brief Players setter
 * @param std::vector<std::string>
 */
void graphical::zappy::setPlayers(std::vector<std::string> data)
{
    broadcast.texture.loadFromFile(BROADCAST);
    broadcast.rectangle.setTexture(&broadcast.texture);
    broadcast.rectangle.setSize(sf::Vector2f(100, 100));
    fontLvlPlayer.loadFromFile("Client/Graphical/Assets/bebas.otf");
    for (size_t i = 0; i != data.size(); i++) {
        try {
            std::vector<std::string> player = stringManager::my_str_to_word_array(data.at(i), " ");
            try {
                teamAnimation.at(player[5]);
            } catch (std::out_of_range) {
                std::string assetName = ASSET_PLAYER;
                assetName += std::to_string((teamAnimationIndex % TEAMN_NBR) + 1);
                assetName += ".png";
                teamAnimation.insert({player[5], new graphical::animation(assetName, sf::IntRect(0, 0, 91, 91), 9)});
                teamAnimation[player[5]]->setFrameRate(50000);
                teamAnimationIndex++;
            }
            int x = atoi(player.at(1).c_str());
            int y = atoi(player.at(2).c_str());
            graphical::player tmp(player, teamAnimation[player[5]], x, y, broadcast.rectangle, fontLvlPlayer);
            tmp.setFrequency(frequency);
            players.push_back(tmp);
            map.at(y).at(x).addPlayer();
            playersInfosGUI.addAPlayerInList((uint32_t)atoi(player[0].c_str()));
        } catch (std::out_of_range &e) {
            exit(84);
        }
    }
}

void graphical::zappy::chat(std::string message)
{
    this->chatGUI.addReceivedMsg(message);
}

/**
 * @brief Eggs setter
 * @param std::string
 */
void graphical::zappy::setEggs(std::string eggs)
{
    std::vector<std::string> egg = stringManager::my_str_to_word_array(eggs, "\n");

    for (auto it = egg.begin(); it != egg.end(); it++) {
        std::vector<std::string> position = stringManager::my_str_to_word_array(
                *it, " ");
        if (atoi(position[3].c_str()) == 0)
            map[atoi(position[2].c_str())][atoi(position[1].c_str())].addItem(7, position[0]);
        else
            map[atoi(position[2].c_str())][atoi(position[1].c_str())].addItem(8, position[0]);
    }
}

/**
 * @brief Method to delete an egg
 * @param std::string
 */
void graphical::zappy::deleteThisEgg(std::string egg)
{
    stringManager::clearStr(egg, '\n');
    std::vector<std::string> position = stringManager::my_str_to_word_array(egg, " ");

    map[atoi(position[2].c_str())][atoi(position[1].c_str())].deleteThisItemByNb(position[0]);
}

/**
 * @brief Method to handle egg hatching
 * @param std::string
 */
void graphical::zappy::hatchingOfAnEgg(std::string egg)
{
    stringManager::clearStr(egg, '\n');
    std::vector<std::string> position = stringManager::my_str_to_word_array(egg, " ");

    map[atoi(position[2].c_str())][atoi(position[1].c_str())].changeItemType(position[0], 8);
}

/**
 * @brief Method to create the map
 * @param graphical::tcpCommunication
 * @param sf::Texture &
 * @param std::string
 */
void graphical::zappy::createTheMap(
        graphical::tcpCommunication communication, sf::Texture &assetTexture, std::string mapEggPlayer)
{
    std::pair<int, int> mapSize = getMapSize(communication);

    std::vector<std::string> mapPlayer = stringManager::my_str_to_word_array(mapEggPlayer, "EGGS :\n");
    std::vector<std::string> data = stringManager::my_str_to_word_array(mapPlayer[0], "\n");
    std::vector<std::string> dataMap = stringManager::my_str_to_word_array(data[0], "-");
    map.reserve(mapSize.second);
    int i = 0;
    for(int y = 0; y != mapSize.second;y++) {
        map.emplace_back(std::vector<graphical::tile>());
        for (int x = 0; x != mapSize.first; x++) {
            std::vector <std::string> tileContent = stringManager::my_str_to_word_array(
                    dataMap[i], " ");

            if (tileContent.size() != 7) {
                std::cerr<< "ERROR";
                exit(84);
            }
            map[y].push_back(graphical::tile(tileContent, assetTexture));
            i++;
        }
    }
    data.erase(data.begin());
    setPlayers(data);
    if (mapPlayer.size() != 1)
        setEggs(mapPlayer[1]);
}

/**
 * @brief Method to handle player drawing
 * @param void
 */
void graphical::zappy::drawPlayer()
{
    sf::Vector2f boardPosition = board->getPosition();

    for (size_t i = 0; i < players.size();i++) {
        std::pair<int, int> playerPosition = players[i].getPosition();
        players[i].draw(window, map, {(float)mathematicalOperations::safeModulo(((int)boardPosition.x + playerPosition.first), (TILE_X * map[0].size())) - 73, (float)mathematicalOperations::safeModulo(((int)boardPosition.y + playerPosition.second), (TILE_Y * map.size())) - 100}, communication, *this);
    }
}

/**
 * @brief Zappy CTor
 * @param char **
 * @param sf::RenderWindow &
 */
graphical::zappy::zappy(std::string ip, int port, sf::RenderWindow &_window) :
        window(_window),
        communication(ip, port),
        teamAnimationIndex(0),
        playersInfosGUI(players, _window, communication),
        chatGUI({100,  800, 200, 200}, window)

{
    background.openFromFile("Client/Graphical/Assets/background.ogg");
    background.setLoop(true);
    background.play();
    communication.get();
    communication.send("GRAPHIC\n");
    communication.send("usf\n");

    std::string m = communication.waitThisFuction("EGGS");

    communication.send("sgt\n");
    std::string frec = communication.waitThisFuction("sgt");
    std::vector<std::string> vectorFrec = stringManager::my_str_to_word_array(frec, " ");
    frequency = atoi(vectorFrec[1].c_str());
    if (frequency > 10) {
        frequency = 10;
        communication.send("sst 10\n");
        communication.get();
    }
    assetTexture.loadFromFile(ASSET_ITEM);
    createTheMap(communication, assetTexture, m);
    backGroundTexture.loadFromFile(ASSET_BACK);

    backGroundRect.setTexture(&backGroundTexture);
    backGroundRect.setSize(sf::Vector2f(1920, 1080));
    backGroundRect.setPosition(sf::Vector2f(0, 0));

    board = std::make_unique<graphical::board>(std::pair<int,int>(map.size(), map.at(0).size()),
                                               std::pair<int, int>(232, 129), map, window);
    window.setFramerateLimit(60);
    communication.send("chat has joined the chat.");
}

graphical::zappy::~zappy()
{
    background.stop();
}

/**
 * @brief Method to run the zappy
 * @param size_t
 */
void graphical::zappy::run(size_t &sceneIndex)
{
    sf::FloatRect chatGUIHitbox = {0, 720, 420, 1080};
    sf::FloatRect playersGUIHitbox = {1270, 0, 1920, 1080};

    try {
        CommandHandler commandHandler(communication, sceneIndex);

        window.clear();
        if (isAPlayerObfuscated())
            window.draw(backGroundRect);
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                sceneIndex = 0;
            board->moveAllTheBoard(event);
            playersInfosGUI.Actualize(event, window);
            chatGUI.actualize(event, window, communication);
            if (playersInfosGUI.isGUIOpen() == false) {
                playersGUIHitbox.top = -1;
            }
            if (chatGUI.isGUIOpen() == false) {
                chatGUIHitbox.top = -1;
            }
            board->Actualize(event, window, chatGUIHitbox, playersGUIHitbox);
        }
        playersInfosGUI.ActualizeInventory(players);
        board->draw(window, *this);
        playersInfosGUI.Draw(window);
        chatGUI.draw(window);
        window.display();
        commandHandler.getNewCommands(*this);
    } catch (std::exception &e) {
        std::cerr << "Window Error\n";
        exit(84);
    }
}

std::vector<std::vector<graphical::tile>> &graphical::zappy::getMap()
{
    return map;
}

std::vector<graphical::player>& graphical::zappy::getPlayers()
{
    return players;
}

bool graphical::zappy::isAPlayerObfuscated()
{
    for (auto it = players.begin(); it != players.end(); it++) {
        if (it->getObfuscation()) {
            return false;
        }
    }
    return true;
}

bool graphical::zappy::IDrawAllTile(std::unique_ptr<rectangle_t> &tileCase, sf::Vector2f &position)
{
    bool tmp = true;
    std::vector<std::vector<graphical::player>::iterator> playerObfuscated;

    for (auto it = players.begin(); it != players.end(); it++) {
        if (it->getObfuscation()) {
            playerObfuscated.push_back(it);
            tmp = false;
        }
    }
    if (tmp)
        return true;
    for (auto it = playerObfuscated.begin(); it != playerObfuscated.end(); it++) {
        (*it)->iDrawLookedTile(map, window, tileCase, position);
    }
    return false;
}

/**
 * @brief Method to find a player on the map
 * @param std::string
 * @return std::optional<graphical::player>
 */
std::optional<graphical::player*> graphical::zappy::findAPlayer(std::string nb)
{
    size_t p = 0;

    stringManager::clearStr(nb, '\n');
    while (players.size() != p) {
        if (players[p].getNb() == nb)
            return (std::make_optional(&players[p]));
        p++;
    }
    return std::nullopt;
}

/**
 * @brief Method to delete a player
 * @param std::string
 */
void graphical::zappy::deleteThisPlayer(std::string nb)
{
    for (auto it = players.begin(); it != players.end(); it++) {
        if (it->getNb() == nb) {
            this->playersInfosGUI.removeAPlayer(nb);
            players.erase(it);
            return;
        }
    }
}

/**
 * @brief Window getter
 * @param void
 * @return sf::RenderWindow &
 */
sf::RenderWindow &graphical::zappy::getWindow()
{
    return window;
}