#ifndef PSU_ZAPPY_2018_TILE_H
#define PSU_ZAPPY_2018_TILE_H

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <memory>
#include "../../../ezSFML/GUI.h"
#include "item.hpp"


/**
 * @struct rectangle_t
 * @brief rectangle_t struct
 */
struct rectangle_t {
    sf::Texture texture;
    sf::RectangleShape rectangle;
    sf::RectangleShape outline;
    sf::RectangleShape hovered;
    ~rectangle_t() {}
};

namespace graphical {
    class player;
    class animation;
    class item;
    /**
     * @class tile
     * @brief tile class
     */
    class tile : public ez::GUI {
    public:
        tile(std::vector<std::string>, sf::Texture&);
        void draw(sf::RenderWindow &window, sf::Vector2f, std::unique_ptr<rectangle_t>&);
        void deleteThisItem(std::string);
        std::vector<graphical::item> &getItem();
        void addItem(int type, std::string nb);
        void addItem(std::string type);
        void changeItemType(std::string, int);
        void deleteThisItemByNb(std::string);
        uint32_t getNbOfPlayersOnTile();
        void addPlayer();
        void delPlayer();
        void setSelectedState(bool);
        bool getSelectedState() const;
        void setHoveredState(bool);
        bool getHoveredState() const;
    private:
        sf::Texture &assetTexture;
    	std::vector<graphical::item> item;
        sf::Vector2f pos;
        bool isSelected;
        bool isHovered;
        uint32_t nbrOfPlayerInThisTile;
    };
}

#include "player.hpp"
#include "item.hpp"

#endif //PSU_ZAPPY_2018_TILE_H
