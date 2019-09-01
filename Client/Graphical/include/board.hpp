#ifndef PSU_ZAPPY_2018_BOARD_H
#define PSU_ZAPPY_2018_BOARD_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdio.h>
#include <string>
#include "tile.hpp"
#include <memory>
#include <math.h>
#include "../tools/include/mathematicalOperations.hpp"
#include <vector>
#include <list>
#include <algorithm>
#include <utility>
#include <optional>
#define NBR_OF_TILE 1
#define ASSET_GRASS "./Client/Graphical/Assets/tile.png"
#include "tilesInfosGUI.hpp"
#include "chatGui.hpp"
#include "playersInfosGUI.hpp"

namespace graphical {
    class TilesInfosGUI;
    class zappy;
    /**
	 * @class TilesInfosGUI
	 * @brief TilesInfosGUI class
	 */
    class board {
        public:
            board(std::pair<int, int>, std::pair<int, int>, std::vector<std::vector<graphical::tile>>&, sf::RenderWindow &);
            void draw(sf::RenderWindow &, graphical::zappy &zappy);
            void moveAllTheBoard(sf::Event &event);
            sf::Vector2f getPosition();
            void Actualize(sf::Event &event, sf::RenderWindow &window, sf::FloatRect chatGUIHitbox, sf::FloatRect playersGUIHitbox);
            void InitAllLambdaInBoard();
            void unselectOldTile();
            void unhoverOldTile();
            graphical::TilesInfosGUI &getTilesInfosGUI();
        private:
            sf::IntRect rect;
            std::vector<std::unique_ptr<rectangle_t>> tileCase;
            std::pair<int, int> tileSize;
            sf::Vector2f position;
            int speedX = 0;
            int speedY = 0;
            size_t speed;
            std::vector<std::vector<graphical::tile>> &map;
            graphical::TilesInfosGUI tilesInfosGUI;
    };
}

#endif //PSU_ZAPPY_2018_BOARD_H
