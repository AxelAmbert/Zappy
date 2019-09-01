#ifndef PSU_ZAPPY_2018_PLAYERSINFOSGUI_HPP
#define PSU_ZAPPY_2018_PLAYERSINFOSGUI_HPP

#include <vector>
#include <list>
#include "player.hpp"
#include "../../../ezSFML/StackElements.h"
#include "../../../ezSFML/Slider.h"
#include <memory.h>
#include "../tools/include/tcpCommunication.hpp"
#include "partOfPlayersInfosGUI.hpp"
#include "Slider.h"
#include "../tools/include/stringManager.hpp"
#include "../../../ezSFML/ClassicButton.h"

namespace graphical {
    /**
     * @class PlayerInfosGUI
     * @brief PlayerInfosGUI class
     */
    class PlayersInfosGUI {
    public:
        explicit PlayersInfosGUI(std::vector<graphical::player> &players, sf::RenderWindow &currentWindow, graphical::tcpCommunication &communication);
        ~PlayersInfosGUI() {};
        PlayersInfosGUI(PlayersInfosGUI &player) = delete;
        void rebuildAllPanels();
        void addAPlayerInList(uint32_t playerNb);
        void removeAPlayer(std::string nb);
        void ActualizeInventory(std::vector<graphical::player> &players);
        void Actualize(sf::Event &event, sf::RenderWindow &window);
        void Draw(sf::RenderWindow &window);
        void addNewInventoryInformations(std::string &inventoryInformation);
        void Open();
        void Close();
        bool isGUIOpen();
    private:
        bool isOpen;
        sf::Texture panelTexture;
        graphical::tcpCommunication &communication;
        void initThePrincipalPanel();
        void ActualizeAPanelPlayerReference(graphical::player &player);
        std::optional<std::string> getPlayerTeamName(uint32_t playerNb);
        std::array<sf::RectangleShape, 7> sprites;
        sf::Texture spritesheet;
        sf::RenderWindow &window;
        sf::RectangleShape backPanel;
        ez::StackPanel playersPanel;
        std::vector<graphical::PartOfPlayersInfosGUI *> panels;
        ez::Slider slider;
        sf::RectangleShape m;
        std::vector<graphical::player> &playersList;
        clock_t actualizationClock;
        ez::ClassicButton openButton;
        ez::ClassicButton closeButton;
        sf::Clock move_clock;
        double lastSliderValue;
    };
}

#endif //PSU_ZAPPY_2018_PLAYERSINFOSGUI_HPP
