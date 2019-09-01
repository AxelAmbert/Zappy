#ifndef PSU_ZAPPY_2018_ITEM_H
#define PSU_ZAPPY_2018_ITEM_H

#include "tile.hpp"

namespace graphical {
    /**
	 * @class GuiManager
	 * @brief GuiManager class
	 */
    class item {
        public:
            item(int, sf::Texture &);
            item(std::string, sf::Texture &);
            item(int, sf::Texture &, std::string);
            void draw(sf::Vector2f, sf::RenderWindow &);
            std::string getType() const ;
            std::string getNb() const ;
            void changeType(int);
        private:
            sf::Sprite sprite;
            sf::Vector2f randVector;
            std::map<int, std::string> mapItem;
            std::string type;
            std::string nb;
    };
}


#endif //PSU_ZAPPY_2018_ITEM_H
