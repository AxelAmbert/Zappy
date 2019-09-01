#ifndef PSU_ZAPPY_2018_PARTOFPLAYERSINFOSGUI_HPP
#define PSU_ZAPPY_2018_PARTOFPLAYERSINFOSGUI_HPP

#include <StackElements.h>
#include <ClassicButton.h>
#include "player.hpp"
#include "Checkbox.hpp"

#define CHECK_BOX "./Client/Graphical/Assets/checkbox_visible.png"

namespace graphical {
    /**
     * @class PartOfPlayersInfoGUI
     * @brief PartOfPlayersInfoGUI Class
     */
    class PartOfPlayersInfosGUI {
    public:
        PartOfPlayersInfosGUI(graphical::player &player, std::array<sf::RectangleShape, 7> &rectangle, std::vector<graphical::player> &_vectorPlayer);
        ~PartOfPlayersInfosGUI(){}

        ez::StackPanel *getPrincipalPanel() {return (&principalPanel);}
        void initThePanels();
        void addFirstPanel();
        void addSecondPanel(std::array<sf::RectangleShape, 7> &rectangle);
        void addThirdPanel(std::array<sf::RectangleShape, 7> &rectangle);
        void addFourthPanel();
        void initPanelsVariables();
        graphical::player &getAttachedPlayer();
        std::string getAttachedPlayerNb();
        void updateAttachedPlayer(graphical::player &player);
        void actualizeInventory(std::vector<std::string> &resources);
    private:
        std::array<sf::RectangleShape, 7> rectangle;
        sf::RectangleShape separation;
        inline static int ok = 4;
        sf::RectangleShape mor;
        ez::Checkbox viewMode;
        graphical::player &attachedPlayer;
        std::string attachedPlayerNb;
        std::vector<graphical::player> &vectorPlayer;
        std::array<sf::Text, 2> partOneText;
        std::array<sf::Text, 7> resourcesText;
        std::array<ez::StackPanel, 4> panels;
        ez::StackPanel principalPanel;
        sf::Font font;
    };
}


#endif //PSU_ZAPPY_2018_PARTOFPLAYERSINFOSGUI_HPP
