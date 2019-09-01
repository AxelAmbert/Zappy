#ifndef PSU_ZAPPY_2018_PLAYER_H
#define PSU_ZAPPY_2018_PLAYER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "../tools/include/tcpCommunication.hpp"
#include <memory>
#include <utility>
#include <functional>
#include "../tools/include/stringManager.hpp"

#define TILE_X 232
#define TILE_Y 129

struct rectangle_t;

namespace graphical {
    class tile;
    class animation;
    class zappy;
    /**
     * @class zappy
     * @brief zappy class
     */
    class player {
    public:
        player(std::vector<std::string>, graphical::animation*, int, int, sf::RectangleShape &, sf::Font &_fontLvl);
        void draw(sf::RenderWindow &window, std::vector<std::vector<graphical::tile>> &, sf::Vector2f, graphical::tcpCommunication &, graphical::zappy &);
        bool forward(std::vector<std::vector<graphical::tile>> &map, std::string arg, graphical::zappy &);
        bool ppo(std::vector<std::vector<graphical::tile>> &map, std::string arg, graphical::zappy &);
        static void pgt(std::vector<std::vector<graphical::tile>> &map, std::string arg);
        std::string &getNb();
        void addFunction(bool(graphical::player::*)(std::vector<std::vector<graphical::tile>> &, std::string, graphical::zappy &), std::string);
        std::pair<int, int> getPosition();
        void setFrequency(int _frequency);
        bool pex(std::vector<std::vector<graphical::tile>> &map, std::string arg, graphical::zappy &);
        bool pdi(std::vector<std::vector<graphical::tile>> &map, std::string arg, graphical::zappy &);
        bool pfk(std::vector<std::vector<graphical::tile>> &map, std::string arg, graphical::zappy &);
        bool pbc(std::vector<std::vector<graphical::tile>> &map, std::string arg, graphical::zappy &);
        static void pdr(std::vector<std::vector<graphical::tile>> &map, std::string arg);
        bool pie(std::vector<std::vector<graphical::tile>> &map, std::string arg, graphical::zappy &);
        bool pic(std::vector<std::vector<graphical::tile>> &map, std::string arg, graphical::zappy &);
        std::string getTeamName();
        void setViewObfuscation(bool _obfuscation);
        bool noPlayerObfuscated(std::vector<graphical::player> &list);
        bool getObfuscation();
        void iDrawLookedTile(std::vector<std::vector<graphical::tile>> &map, sf::RenderWindow &window, std::unique_ptr<rectangle_t> &tileCase, sf::Vector2f &position);

    private:
        graphical::animation *playerAsset;
        std::vector<std::pair<bool(graphical::player::*)(std::vector<std::vector<graphical::tile>> &, std::string, graphical::zappy &), std::string>> functionList;
        std::pair<int, int> position;
        sf::Vector2f truePosition;
        std::string nb;
        int frequency;
        std::string orientation;
        std::pair<int, int> tilePosition;
        std::map<std::string, int> orientationMap;
        int positionDestination;
        sf::Clock clock;
        std::string teamName;
        sf::RectangleShape *broadcast;
        sf::Clock broadClock;
        bool firstCall;
        bool obfuscation;
        int level;
        sf::Clock forwardClock;
        sf::Text textLvl;

    };
}

#include "tile.hpp"
#include "../tools/include/animation.hpp"

#endif //PSU_ZAPPY_2018_PLAYER_H
