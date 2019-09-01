#include "../include/tilesInfosGUI.hpp"

/**
 * @brief State getter
 * @param void
 * @return bool
 */
bool graphical::TilesInfosGUI::isGUIOpen()
{
    return (isOpen);
}

/**
 * @brief Method to open the Infos about the tile
 * @param graphical::tile &
 * @param graphical::board &
 */
void graphical::TilesInfosGUI::open(graphical::tile &tile, graphical::board &test)
{

    std::vector<graphical::item> &items = tile.getItem();
    std::array<std::string, 10> names = {"player", "food", "linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame", "egg", "egg_h"};
    unsigned int nbOfResources = 0;

    test.unselectOldTile();
    this->open();
    textArray[0].setString(std::to_string(tile.getNbOfPlayersOnTile()));
    for (int i = 1; i < 9; i++) {
        std::for_each(items.begin(), items.end(),
                [&i, &names, &nbOfResources](graphical::item &item)
                {
                    if (names[i] == item.getType()) {
                        nbOfResources += 1;
                    }
                }
        );
        textArray[i].setString(nbOfResources < 999 ? std::to_string(nbOfResources) : "99+");
        nbOfResources = 0;
    }
}

/**
 * @brief Set the isOpen boolean to true
 * @param void
 */
void graphical::TilesInfosGUI::open()
{
    this->isOpen = true;
}

/**
 * @brief Set the isOpen boolean to false
 * @param void
 */
void graphical::TilesInfosGUI::close()
{
    this->isOpen = false;
}

/**
 * @brief Method to focus on a given tile
 * @param graphical::tile *
 */
void graphical::TilesInfosGUI::focusOnATile(graphical::tile *tile)
{
    this->focusOn = tile;
}

/**
 * @brief Method to actualize a tile
 * @param sf::Event &
 * @param sf::RenderWindow &
 */
void graphical::TilesInfosGUI::Actualize(sf::Event &event, sf::RenderWindow &window)
{
    slider.Actualize(event, window);
    resourcesPanel.Actualize(event, window);
    float value = slider.getValue();
    if (value >= 0 && value <= 100) {
        resourcesPanel.setViewPercent(slider.getValue(), 0);
    }
    closeButton.Actualize(event, window);
    if (closeButton.getState() == ez::GuiState::RELEASED) {
        this->close();
    }
}

/**
 * @brief Method to draw a tile
 * @param sf::RenderWindow &
 */
void graphical::TilesInfosGUI::Draw(sf::RenderWindow &window)
{
    sf::Vector2f difference = {0, 0};

    if (isOpen == false && panel.getPosition().y < WINDOW_HEIGHT) {
        difference = {0, 10};
    } else if (isOpen == true && panel.getPosition().y > WINDOW_HEIGHT - panel.getSize().y) {
        difference = {0, -10};
    }
    if (difference.y != 0 && move_clock.getElapsedTime().asMilliseconds() > 0.016f) {
            panel.setPosition(panel.getPosition() + difference);
            slider.setPosition(slider.getPosition() + difference);
            closeButton.setPosition(closeButton.getPosition().x,
                    panel.getPosition().y + 10);
            resourcesPanel.staticIt({360, 100}, {panel.getPosition().x + 125,
                resourcesPanel.getPosition().y + difference.y}, window);
            move_clock.restart();
    }
    window.draw(panel);
    slider.Draw(window);
    closeButton.Draw(window);
    resourcesPanel.Draw(window);
}

/**
 * @brief Method to init a Gui Panel
 * @param void
 */
void graphical::TilesInfosGUI::initGUIPanel()
{
    font.loadFromFile("Client/Graphical/Assets/bebas.otf");
    playerTexture.loadFromFile("Client/Graphical/Assets/miniplayer.png");
    spritesheetRect.width = 23 * 3;
    spritesheetRect.height = 34 * 3;

    for (int i = 0; i < 10; i++) {
        spritesheetRect.left = (i - 1) * (23 * 3);
        rectArray[i] = sf::RectangleShape();
        rectArray[i].setSize({75, 75});
        //rectArray[i].setFillColor(sf::Color::Red);
        if (i == 0) {
            rectArray[i].setTexture(&playerTexture);
        } else {
            rectArray[i].setTexture(&spritesheet);
            rectArray[i].setTextureRect(spritesheetRect);
        }
        rectArray[i].setPosition(0, 0);
        textArray[i] = sf::Text();
        textArray[i].setCharacterSize(60);
        textArray[i].setFont(font);
        textArray[i].setFillColor(sf::Color::Black);
        textArray[i].setString("0");
        resourcesPanel.Add(&textArray[i], {50, 0});
        resourcesPanel.Add(&rectArray[i], {50, 0});
    }
}

/**
 * @brief TileInfosGUI CTor
 * @param sf::RenderWindow &
 */
graphical::TilesInfosGUI::TilesInfosGUI(sf::RenderWindow &window) :
        focusOn(nullptr),
        resourcesPanel(ez::Orientation::HORIZONTAL),
        isOpen(true)
{
    spritesheet.loadFromFile("Client/Graphical/Assets/item_larger.png");
    spritesheetRect = {};
    panel.setPosition((int)(WINDOW_WIDTH / 2) - 400, int(WINDOW_HEIGHT));
    panel.setSize({600, 200});
    panelTexture.loadFromFile("Client/Graphical/Assets/tilepanel.png");
    panel.setTexture(&panelTexture);
    slider.Create({"Client/Graphical/Assets/slider_348x28_40x40.png", {0, 0, 348, 28}, {panel.getPosition().x + 125, panel.getPosition().y + 150}, {0, 28, 40, 40}, ez::SliderLimit::ABSOLUTEE});
    closeButton.Create("Client/Graphical/Assets/button_120x40_40x40.png", {40, 40}, {panel.getPosition().x + panel.getSize().x - 140, panel.getPosition().y}, {0, 0});
    closeButton.setPosition(closeButton.getPosition().x - 10, panel.getPosition().y);
    this->initGUIPanel();
    resourcesPanel.staticIt({360, 100}, {panel.getPosition().x + 125, panel.getPosition().y + 50}, window);
}