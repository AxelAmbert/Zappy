#ifndef PSU_ZAPPY_2018_ZAPPY_H
#define PSU_ZAPPY_2018_ZAPPY_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdio.h>
#include <string>
#include <exception>
#include <vector>
#include <list>
#include <memory>
#include "board.hpp"
#include "../tools/include/stringManager.hpp"
#include "../tools/include/tcpCommunication.hpp"
#include "../tools/include/animation.hpp"
#include "../tools/include/mathematicalOperations.hpp"
#include "playersInfosGUI.hpp"
#include "IScene.hpp"
#include "chatGui.hpp"
#include <SFML/Audio.hpp>

#define ASSET_PLAYER "./Client/Graphical/Assets/player"
#define ASSET_ITEM "./Client/Graphical/Assets/item.png"
#define ASSET_BACK "./Client/Graphical/Assets/herbe.png"
#define BROADCAST "./Client/Graphical/Assets/broadCast.png"
#define TEAMN_NBR 5

class CommandHandler;

namespace graphical {

    /**
     * @class zappy
     * @brief zappy class
     * @inherit Scene
     */
    class zappy : public IScene {
    public:
        zappy(std::string ip, int port, sf::RenderWindow &_window);
        ~zappy();
        std::pair<int, int> getMapSize(graphical::tcpCommunication communication);
        void run(size_t &sceneIndex) override;
        void createTheMap(graphical::tcpCommunication, sf::Texture &, std::string);
        void setPlayers(std::vector<std::string>);
        void hatchingOfAnEgg(std::string);
        void chat(std::string message);
        std::optional<graphical::player*> findAPlayer(std::string nb);
        void drawPlayer();
        void deleteThisPlayer(std::string nb);
        void setEggs(std::string);
        void deleteThisEgg(std::string);
        void tg(std::string);
        sf::RenderWindow &getWindow();
        graphical::PlayersInfosGUI &getPlayersInfosGUI();
        std::vector<graphical::player> &getPlayers();
        std::vector<std::vector<graphical::tile>> &getMap();
        bool IDrawAllTile(std::unique_ptr<rectangle_t> &tileCase, sf::Vector2f &position);
        bool isAPlayerObfuscated();
        void setUsername(std::string username);
    private:
        sf::Music background;
        sf::RenderWindow& window;
        sf::Event event;
        std::unique_ptr<graphical::board> board;
        graphical::tcpCommunication communication;
        sf::RectangleShape backGroundRect;
        std::vector<graphical::player> players;
        std::vector<std::vector<graphical::tile>> map;
        sf::Texture backGroundTexture;
        sf::Texture assetTexture;
        int frequency;
        std::map<std::string, graphical::animation*> teamAnimation;
        int teamAnimationIndex;
        rectangle_t broadcast;
        graphical::PlayersInfosGUI playersInfosGUI;
        graphical::ChatGUI chatGUI;
        sf::Font fontLvlPlayer;
    };
}

#endif //PSU_ZAPPY_2018_ZAPPY_H
