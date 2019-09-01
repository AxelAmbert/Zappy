#include "../include/partOfPlayersInfosGUI.hpp"

/**
 * @brief Method to actualize the graphical information of the player
 * @param std::vector<std::string> &
 */
void graphical::PartOfPlayersInfosGUI::actualizeInventory(std::vector<std::string> &resources)
{
    int result = 0;
    std::string validString;
    uint32_t inventoryCounter = 1;

    for (uint32_t i = 0; i < resourcesText.size(); i++, inventoryCounter += 2) {
        try {
            result = std::stoi(resources.at(inventoryCounter));
            if (result < 0)
                return;
            else if (result > 99)
                validString = "9+";
            else
                validString = resources.at(inventoryCounter);
            resourcesText[i].setString(validString + "");
        } catch (...) {
            return;
        }
    }
}

/**
 * @brief Method to update the attached player
 * @param graphical::player &
 */
void graphical::PartOfPlayersInfosGUI::updateAttachedPlayer(
        graphical::player &player)
{
    attachedPlayerNb = player.getNb();
}

/**
 * @brief Attached player getter
 * @param void
 * @return graphical::player
 */
graphical::player &graphical::PartOfPlayersInfosGUI::getAttachedPlayer()
{
    return (attachedPlayer);
}

/**
 * @brief Attached player number getter
 * @param void
 * @return std::string
 */
std::string graphical::PartOfPlayersInfosGUI::getAttachedPlayerNb()
{
    return (attachedPlayerNb);
}

/**
 * @brief Method to init player panel
 * @param void
 */
void graphical::PartOfPlayersInfosGUI::initThePanels()
{
    for (int i = 0; i < 7; i++) {
        resourcesText[i] = sf::Text();
        if (i < 2)
            partOneText[i] = sf::Text();
        if (i < 4)
            panels[i].setOrientation(ez::Orientation::HORIZONTAL);
    }
}

/**
 * @brief Method to init variables in the player panel
 * @param void
 */
void graphical::PartOfPlayersInfosGUI::initPanelsVariables()
{
    font.loadFromFile("Client/Graphical/Assets/bebas.otf");
    partOneText[0].setFont(font);
    partOneText[0].setFillColor(sf::Color::Black);
    partOneText[1].setFillColor(sf::Color::Black);
    partOneText[0].setCharacterSize(35);
    partOneText[1].setCharacterSize(35);
    partOneText[1].setFont(font);
    partOneText[0].setString("Player Number : " + attachedPlayer.getNb());
    partOneText[1].setString("Player Team : " + attachedPlayer.getTeamName());
    for (auto i = 0; i < 7; i++) {
        resourcesText[i].setCharacterSize(35);
        resourcesText[i].setFont(font);
        resourcesText[i].setString("0");
    }
}

/**
 * @brief Method to add the first player panel
 * @param void
 */
void graphical::PartOfPlayersInfosGUI::addFirstPanel()
{
    panels[0].Add(&partOneText[0]);
    panels[0].Add(&partOneText[1], {25, 0});
}

/**
 * @brief Method to add the second player panel
 * @param std::array<sf::RectangleShape> &
 */
void graphical::PartOfPlayersInfosGUI::addSecondPanel(std::array<sf::RectangleShape, 7> &rectangle)
{
    panels[1].Add(&resourcesText[0], {25, 0});
    panels[1].Add(&rectangle[0]);
    panels[1].Add(&resourcesText[1], {25, 0});
    panels[1].Add(&rectangle[1]);
    panels[1].Add(&resourcesText[2], {25, 0});
    panels[1].Add(&rectangle[2]);
    panels[1].Add(&resourcesText[3], {50, 0});
    panels[1].Add(&rectangle[3]);
}

/**
 * @brief Method to add the third player panel
 * @param std::array<sf::RectangleShape> &
 */
void graphical::PartOfPlayersInfosGUI::addThirdPanel(
        std::array<sf::RectangleShape, 7> &rectangle)
{
    panels[2].Add(&resourcesText[4], {25, 0});
    panels[2].Add(&rectangle[4]);
    panels[2].Add(&resourcesText[5], {25, 0});
    panels[2].Add(&rectangle[5]);
    panels[2].Add(&resourcesText[6], {25, 0});
    panels[2].Add(&rectangle[6]);
    panels[2].Add(&viewMode, {25, 0});
}

/**
 * @brief Method to add the fourth player panel
 * @param void
 */
void graphical::PartOfPlayersInfosGUI::addFourthPanel()
{
    separation.setSize({400, 10});
    separation.setFillColor(sf::Color::Black);
    panels[3].Add(&separation, {30, 0});
}

/**
 * @brief PartOfPlayersInfoGUI CTor
 * @param graphical::player &
 * @param std::array<sf::RectangleShape> &
 */
graphical::PartOfPlayersInfosGUI::PartOfPlayersInfosGUI(
        graphical::player &player, std::array<sf::RectangleShape, 7> &rect,
        std::vector<graphical::player> &_vectorPlayer) :
        viewMode(CHECK_BOX, {83, 83}, {0, 0}, {0, 0}),
        attachedPlayer(player),
        vectorPlayer(_vectorPlayer),
        principalPanel(ez::Orientation::VERTICAL)
{
    attachedPlayerNb = player.getNb();
    viewMode.addOneElementInEventList(ez::GuiState::RELEASED, [](std::string attachedPlayerNb, std::vector<graphical::player> &vectorPlayer, ez::Checkbox &viewMode) {
        for (auto it = vectorPlayer.begin(); it != vectorPlayer.end(); it++) {
            if (attachedPlayerNb == it->getNb()) {
                it->setViewObfuscation(viewMode.getChecked());
            }
        }
    }, attachedPlayerNb, vectorPlayer, viewMode);
    rectangle = rect;
    this->initThePanels();
    this->initPanelsVariables();
    this->addFirstPanel();
    this->addSecondPanel(rectangle);
    this->addThirdPanel(rectangle);
    this->addFourthPanel();
    principalPanel.Add(&panels[0], {0, 20});
    principalPanel.Add(&panels[1], {0, 20});
    principalPanel.Add(&panels[2], {0, 20});
    principalPanel.Add(&panels[3], {0, 20});
}