#include "../include/board.hpp"
#include <algorithm>
#include "../include/zappy.hpp"

/**
 * @brief Tiles indo getter
 * @param void
 * @return graphical::TileInfosGUI
 */
graphical::TilesInfosGUI &graphical::board::getTilesInfosGUI()
{
    return (this->tilesInfosGUI);
}

/**
 * @brief Lambda initializer
 * @param void
 */
void graphical::board::InitAllLambdaInBoard()
{

    int x = 0;
    for (auto &i : map) {
        for (auto &j: i) {
            j.addOneElementInEventList(ez::GuiState::RELEASED,
                    [](graphical::tile &tile, graphical::TilesInfosGUI &tilesInfosGUI, graphical::board &board) mutable
                    {
                        //tilesInfosGUI.getResources();
                        tilesInfosGUI.open(tile, board);
                        tile.setSelectedState(true);
                        //exit(0);
                }, j, this->getTilesInfosGUI(), *this);
        }
        x++;
    }
}

/**
 * @brief Actualise the tiles
 * @param sf::Event &
 * @param sf::RenderWindow &
 */
void graphical::board::Actualize(sf::Event &event, sf::RenderWindow &window,
        sf::FloatRect chatGUIHitbox, sf::FloatRect playersGUIHitbox)
{
    std::for_each(this->map.begin(), this->map.end(),
            [&](std::vector<graphical::tile> &tiles)
            {
                std::for_each(tiles.begin(), tiles.end(),
                        [&] (graphical::tile &tile)
                        {
                            if ( event.type == sf::Event::MouseButtonReleased) {
                                sf::Vector2i tmpPos = sf::Mouse::getPosition(window);
                                if (tilesInfosGUI.isGUIOpen() == true) {
                                    if (tmpPos.x >= 660 &&
                                        tmpPos.x <= 890 &&
                                        tmpPos.y >= 890 &&
                                        tmpPos.y <= (int) WINDOW_HEIGHT) {
                                        return;
                                    }
                                }
                                if (chatGUIHitbox.top != -1) {
                                    if (tmpPos.x >= chatGUIHitbox.left &&
                                        tmpPos.x <= chatGUIHitbox.width &&
                                        tmpPos.y >= chatGUIHitbox.top &&
                                        tmpPos.y <= chatGUIHitbox.height) {
                                        return;
                                    }
                                }
                                if (playersGUIHitbox.top != -1) {
                                    if (tmpPos.x >= playersGUIHitbox.left &&
                                        tmpPos.x <= playersGUIHitbox.width &&
                                        tmpPos.y >= playersGUIHitbox.top &&
                                        tmpPos.y <= playersGUIHitbox.height) {
                                        return;
                                    }
                                }
                            }
                            tile.Actualize(event, window);
                            if (tile.getState() == ez::GuiState::HOVERED) {
                                this->unhoverOldTile();
                                tile.setHoveredState(true);
                            }
                        }
                );
            }
    );
    tilesInfosGUI.Actualize(event, window);
}

/**
 * @brief Tiles indo getter
 * @param std::pair<int, int>
 * @param std::pair<int, int>
 * @param std::vector<std::vector<graphical::tile>> &
 * @param sf::RenderWindow
 * @return graphical::board
 */
graphical::board::board(std::pair<int, int> mapSize, std::pair<int, int> _tileSize, std::vector<std::vector<graphical::tile>> &_map, sf::RenderWindow &window) :
        map(_map),
        tilesInfosGUI(window)
{
    tileCase.push_back(std::unique_ptr<rectangle_t>(new rectangle_t));
    tileCase[0]->texture.loadFromFile(ASSET_GRASS);
    rect.width = mapSize.first;
    rect.height = mapSize.second;
    tileCase[0]->rectangle.setTexture(&tileCase[0]->texture);
    tileCase[0]->rectangle.setSize(sf::Vector2f(_tileSize.first, _tileSize.second));
    tileCase[0]->outline.setTexture(&tileCase[0]->texture);
    tileCase[0]->outline.setSize(sf::Vector2f(_tileSize.first, _tileSize.second));
    tileCase[0]->outline.setOutlineColor(sf::Color::Yellow);
    tileCase[0]->outline.setOutlineThickness(- 3.0);
    tileCase[0]->hovered.setTexture(&tileCase[0]->texture);
    tileCase[0]->hovered.setSize(sf::Vector2f(_tileSize.first, _tileSize.second));
    tileCase[0]->hovered.setOutlineColor(sf::Color::White);
    tileCase[0]->hovered.setOutlineThickness(- 3.0);

    tileSize = _tileSize;
    position.x = 0;
    position.y = 0;
    speed = 5;
    this->InitAllLambdaInBoard();
}

/**
 * @brief Draw function
 * @param sf::RenderWindow &
 */
void graphical::board::draw(sf::RenderWindow &window, graphical::zappy &zappy)
{
    position.x += speedX;
    position.y += speedY;

    if (zappy.IDrawAllTile(tileCase[std::rand() % NBR_OF_TILE], position)) {
        for (int x = 0; x < rect.height; x++) {
            int idx = mathematicalOperations::safeModulo(
                    ((int) position.x / TILE_X + (x)), rect.width);
            for (int y = 0; y < rect.width; y++) {
                int idy = mathematicalOperations::safeModulo(((int) position.y / TILE_Y + (y)), rect.height);
                map[y][x].draw(window, sf::Vector2f((idx * (tileSize.first) + (((int) position.x) % TILE_X)) - 200, ((idy * (tileSize.second)) + ((int) position.y) % TILE_Y) - 100), tileCase[std::rand() % NBR_OF_TILE]);
            }
        }
    }
    zappy.drawPlayer();
    tilesInfosGUI.Draw(window);
}

/**
 * @brief Position getter
 * @param void
 * @param sf::Vector2f
 */
sf::Vector2f graphical::board::getPosition()
{
    return position;
}

/**
 * @brief Handle the movement on the map
 * @param sf::Event &
 */
void graphical::board::moveAllTheBoard(sf::Event &event)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        speedX = speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        speedX = -1 * speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        speedY = speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        speedY = -1 * speed;
    switch (event.type) {
        case sf::Event::KeyReleased:
            if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Right)
                speedX = 0;
            if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Down)
                speedY = 0;
            if (event.key.code == sf::Keyboard::LShift)
                speed = 5;
            break;
        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::LShift)
                speed = 10;
            break;
        default:
            break;
    }
}

void graphical::board::unselectOldTile() {
    uint32_t i = 0;
    uint32_t j = 0;

    while (i < this->map.size()) {
        while (j < this->map[i].size()) {
            if (this->map[i][j].getSelectedState()) {
                this->map[i][j].setSelectedState(false);
                return;
            }
            j++;
        }
        j = 0;
        i++;
    }
}

void graphical::board::unhoverOldTile()
{
    size_t i = 0;
    size_t j = 0;

    while (i < this->map.size()) {
        while (j < this->map[i].size()) {
            if (this->map[i][j].getHoveredState()) {
                this->map[i][j].setHoveredState(false);
                return;
            }
            j++;
        }
        j = 0;
        i++;
    }
}
