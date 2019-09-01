#include "../include/playersInfosGUI.hpp"

/**
 * @brief Method to add some player inventory information
 * @param std::string &
 */
void graphical::PlayersInfosGUI::addNewInventoryInformations(
        std::string &inventoryInformation)
{
    std::vector<std::string> splittedInventory = stringManager::my_str_to_word_array(inventoryInformation, " ");
    std::string validPlayer;

    if (splittedInventory.size() != 15)
        return;
    validPlayer = splittedInventory[0];
    splittedInventory.erase(splittedInventory.begin());
    for (uint32_t i = 0; i < panels.size(); i++) {
        if (panels[i]->getAttachedPlayerNb() == validPlayer) {
            panels[i]->actualizeInventory(splittedInventory);
            return;
        }
    }
}

/**
 * @brief Method to remove a player
 * @param std::string
 */
void graphical::PlayersInfosGUI::removeAPlayer(std::string playerNb)
{
    for (uint32_t i = 0; i < panels.size(); i++) {
        if (playerNb == panels[i]->getAttachedPlayerNb()) {
            panels.erase(panels.begin() + i);
            this->rebuildAllPanels();
            return;
        }
    }
}

/**
 * @brief Method to draw the elements
 * @param sf::RenderWindow &
 */
void graphical::PlayersInfosGUI::Draw(sf::RenderWindow &window)
{
    if (move_clock.getElapsedTime().asMilliseconds() >= 0.016f) {
        if (isOpen == true && backPanel.getPosition().x > WINDOW_WIDTH - 700) {
            backPanel.setPosition(backPanel.getPosition().x - 10,
                    backPanel.getPosition().y);
            playersPanel.staticIt({570, 800},
                    {backPanel.getPosition().x + 150, 10}, window);
            closeButton.setPosition((int) closeButton.getPosition().x - 10,
                    (int) closeButton.getPosition().y);
            openButton.setPosition(closeButton.getPosition());
            slider.setPosition({slider.getPosition().x - 10, slider.getPosition().y});
        } else if (isOpen == false &&
                   closeButton.getPosition().x + closeButton.getSize().x <
                   WINDOW_WIDTH) {
            backPanel.setPosition(backPanel.getPosition().x + 10,
                    backPanel.getPosition().y);
            playersPanel.staticIt({570, 800},
                    {backPanel.getPosition().x + 150, 10}, window);
            closeButton.setPosition((int) closeButton.getPosition().x + 10,
                    (int) closeButton.getPosition().y);
            openButton.setPosition(closeButton.getPosition());
            slider.setPosition({slider.getPosition().x + 10, slider.getPosition().y});
        }
        move_clock.restart();
    }
    window.draw(backPanel);
    if (isOpen) {
        closeButton.Draw(window);
    } else {
        openButton.Draw(window);
    }
    playersPanel.Draw(window);
    slider.setPosition({1875, 35});
    if (this->panels.size() > 3) {
        slider.Draw(window);
    }
}

/**
 * @brief Method to actualize player reference panel
 * @param graphical::player &
 */
void graphical::PlayersInfosGUI::ActualizeAPanelPlayerReference(
        graphical::player &player)
{
    for (uint32_t i = 0; i < panels.size(); i++) {
        if (player.getNb() == panels[i]->getAttachedPlayerNb()) {
            panels[i]->updateAttachedPlayer(player);
            return;
        }
    }
}

/**
 * @brief Methos to actualize player inventory
 * @param std::vector<graphical::player> &
 */
void graphical::PlayersInfosGUI::ActualizeInventory(std::vector<graphical::player> &players)
{
    clock_t actualTime = clock();
    bool sendRequest = false;
    std::string buffer;

    if (1000 * (actualTime - actualizationClock) / CLOCKS_PER_SEC >= 1000) {
        sendRequest = true;
        actualizationClock = clock();
    }
    try {
        for (uint32_t i = 0; i < players.size(); i++) {
            ActualizeAPanelPlayerReference(players[i]);
            if (sendRequest == true) {
                buffer += "pin " + players[i].getNb() + "\n";
            }
        }
    } catch (const std::out_of_range &) {}
    if (sendRequest == true)
        communication.send(buffer);
}

/**
 * @brief Method to actualize the information
 * @param sf::Event &
 * @param sf::RenderWindow &
 */
void graphical::PlayersInfosGUI::Actualize(sf::Event &event,
        sf::RenderWindow &window)
{
    double value = 0;

    playersPanel.Actualize(event, window);
    if (isOpen) {
        closeButton.Actualize(event, window);
    } else {
        openButton.Actualize(event, window);
    }
    if (this->panels.size() > 3) {
        value = slider.getValue();
        slider.Actualize(event, window);
        if (this->panels.size() != 0) {
            if (std::abs(lastSliderValue - value) > 1) {
                playersPanel.setViewPercent(0, value);
                lastSliderValue = value;
            }
        }
    } else if (slider.getValue() != 0) {
        slider.setValue(0);
    }
}

/**
 * @brief Team player getter
 * @param uint32_t
 * @return std::optional<std::string>
 */
std::optional<std::string> graphical::PlayersInfosGUI::getPlayerTeamName(uint32_t playerNb)
{
    std::string tmpPlayerNbString = std::to_string(playerNb);

    for (auto &player : this->playersList) {
        if (player.getNb() == tmpPlayerNbString) {
            return (std::make_optional(player.getTeamName()));
        }
    }
    return (std::nullopt);
}
/**
 * @brief Method to add a new player in the list
 * @param uint32_t
 */
void graphical::PlayersInfosGUI::addAPlayerInList(uint32_t playerNb)
{
    std::string tmpNb = std::to_string(playerNb);

    for (auto &player : playersList) {
        if (player.getNb() == tmpNb) {
            auto part = new PartOfPlayersInfosGUI(player, sprites, playersList);
            panels.push_back(part);
        }
    }
    this->rebuildAllPanels();
    actualizationClock = 1;

}

/**
 * @brief Method to init the principal panel
 * @param void
 */
void graphical::PlayersInfosGUI::initThePrincipalPanel()
{
    //this->playersPanel = std::make_unique<ez::StackPanel>(ez::StackPanel(ez::Orientation::VERTICAL));

    for (uint32_t i = 0; i < panels.size(); i++) {
        playersPanel.Add(panels[i]->getPrincipalPanel());
    }
   // playersPanel.staticIt({570, 1080}, {300, 0}, window);

}

/**
 * @brief Method to rebuild all panel
 * @param void
 */
void graphical::PlayersInfosGUI::rebuildAllPanels()
{
    playersPanel.clear();
    playersPanel.setOrientation(ez::Orientation::VERTICAL);
    for (uint32_t i = 0; i < panels.size(); i++) {
        playersPanel.Add(panels[i]->getPrincipalPanel(), {0, 25});
    }
    playersPanel.staticIt({570, 800}, {backPanel.getPosition().x + 150, 10}, window);
}

/**
 * @brief Mehtod to Open the panel
 * @param void
 */
void graphical::PlayersInfosGUI::Open()
{
    isOpen = true;
}

/**
 * @brief Method to close the panel
 * @param void
 */
void graphical::PlayersInfosGUI::Close()
{
    isOpen = false;
}

/**
 * @brief State getter
 * @param void
 * @return bool
 */
bool graphical::PlayersInfosGUI::isGUIOpen()
{
    return (isOpen);
}

/**
 * @brief PlayerInfoGui CTor
 * @param std::vector<graphical::player> &
 * @param sf::Renderwindow &
 * @param graphical::tcpCommunication &
 */
graphical::PlayersInfosGUI::PlayersInfosGUI(std::vector<graphical::player> &players, sf::RenderWindow &currentWindow, graphical::tcpCommunication &communicationRef) :
        communication(communicationRef),
        window(currentWindow),
        playersPanel(ez::Orientation::VERTICAL),
        slider({"Client/Graphical/Assets/slider_vertical_348x28_40x40.png", {0, 0, 28, 798}, {300, 300}, {0, 798, 40, 40}, ez::SliderLimit::ABSOLUTEE}),
        playersList(players),
        openButton("Client/Graphical/Assets/button_250x84_40x40_left.png", {250.0f / 3, 84}, {1268, 0}, {0, 0}),
        closeButton("Client/Graphical/Assets/button_250x84_40x40_right.png", {250.0f / 3, 84}, {1268, 0}, {0, 0})
{
    sf::IntRect tmpSpriteSheet;

    this->actualizationClock = clock();
    tmpSpriteSheet.width = 23;
    tmpSpriteSheet.height = 34;
    tmpSpriteSheet.top = 0;
    backPanel.setSize({700, 1080});
    backPanel.setPosition({WINDOW_WIDTH - 700, 0});
    panelTexture.loadFromFile("Client/Graphical/Assets/playerpanel.png");
    backPanel.setTexture(&panelTexture);
    spritesheet.loadFromFile("Client/Graphical/Assets/item.png");
    for (auto i = 0; i < 7; i++) {
        tmpSpriteSheet.left = 23 * i;
        sprites[i].setSize({75, 75});
        sprites[i].setTexture(&spritesheet);
        sprites[i].setTextureRect(tmpSpriteSheet);
    }
    openButton.addOneElementInEventList(ez::GuiState::RELEASED,
            [](graphical::PlayersInfosGUI &playersInfosGUI)
            {
                playersInfosGUI.Open();
            }, *this);
    closeButton.addOneElementInEventList(ez::GuiState::RELEASED,
            [](graphical::PlayersInfosGUI &playersInfosGUI)
            {
                playersInfosGUI.Close();
            }, *this);
    isOpen = true;
    lastSliderValue = 0;
   // playersPanel.staticIt({570, 1080}, {WINDOW_WIDTH - 570, 0}, window);
   // this->initThePrincipalPanel();
}