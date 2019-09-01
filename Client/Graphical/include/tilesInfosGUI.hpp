#ifndef MYARPSPOOF_TILESINFOSGUI_HPP
#define MYARPSPOOF_TILESINFOSGUI_HPP
#include "../../../ezSFML/StackElements.h"
#include "../../../ezSFML/Slider.h"
#include "tilesInfosGUI.hpp"
#include "../tools/include/tcpCommunication.hpp"
#include "../../../ezSFML/ClassicButton.h"
#include <array>
#include "tile.hpp"

/**
 * @struct resources_s
 * @brief resources_s struct
 */
typedef struct resources_s {
    uint32_t food;
    uint32_t linemate;
    uint32_t deraumere;
    uint32_t sibur;
    uint32_t mendiane;
    uint32_t phiras;
    uint32_t thystame;
} resources_s;

/**
 * @union resources_t
 * @brief resources_t union
 */
union resources_t {
    resources_s resources;
    uint32_t resources_tab[7];
};

namespace graphical {
    class board;
    /**
     * @class TileInfosGUI
     * @brief TileInfosGUI class
     */
    class TilesInfosGUI {
    public:
        TilesInfosGUI(sf::RenderWindow &window);
        void Draw(sf::RenderWindow &window);
        void Actualize(sf::Event &event, sf::RenderWindow &window);
        void focusOnATile(graphical::tile *tile);
        void open();
        void open(graphical::tile &tile, graphical::board &board);
        void close();
        bool isGUIOpen();
    private:
        sf::Texture panelTexture;
        sf::Texture playerTexture;
        graphical::tile *focusOn;
        void initGUIPanel();
        ez::StackPanel resourcesPanel;
        ez::Slider slider;
        ez::ClassicButton closeButton;
        sf::RectangleShape panel;
        union resources_t resources;
        std::array<sf::RectangleShape, 10> rectArray;
        std::array<sf::Text, 10> textArray;
        sf::Font font;
        bool isOpen;
        sf::IntRect spritesheetRect;
        sf::Texture spritesheet;
        sf::Clock move_clock;
    };
}
#include "board.hpp"

#endif //MYARPSPOOF_TILESINFOSGUI_HPP
