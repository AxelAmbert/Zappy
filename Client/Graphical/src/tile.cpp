#include "../include/tile.hpp"

/**
 * @brief Number of player on tile getter
 * @param void
 * @return uint32_t
 */
uint32_t graphical::tile::getNbOfPlayersOnTile()
{
    return (nbrOfPlayerInThisTile);
}

/**
 * @brief Item getter
 * @param void
 * @return std::vector<graphical::item> &
 */
std::vector<graphical::item> &graphical::tile::getItem()
{
    return (item);
}

/**
 * @brief Tile CTor
 * @param std::vector<std::string>
 * @param sf::Texture &
 */
graphical::tile::tile(std::vector<std::string> tileContent, sf::Texture &_assetTexture) : GUI(), assetTexture(_assetTexture), nbrOfPlayerInThisTile(0)
{
    std::vector <std::string> stone = {"./Assets/food.png",
                                       "./Assets/linemate.png"};

    for (size_t n = 0; tileContent.size() != n; n++) {
        for (int i = 0; atoi(tileContent[n].c_str()) != i; i++) {
            item.push_back(graphical::item(n, assetTexture));
        }
    }
    pos.x = 0;
    pos.y = 0;
    this->isSelected = false;
    this->isHovered = false;
}

/**
 * @brief Method to draw the tile
 * @param sf::RendeWindow &
 * @param sf::Vector2f
 * @param std::unique_ptr<rectangle_t> &
 */
void graphical::tile::draw(sf::RenderWindow &window, sf::Vector2f position, std::unique_ptr<rectangle_t> &tileCase)
    {
    pos = position;
    this->setPosition(position);
    this->hitbox = {{1920, 1080}, pos.x, pos.x + TILE_X, pos.y, pos.y + TILE_Y};
    this->setPosition(position);
    if (position.x + TILE_X < 10) {
        return;
    }
    if (position.y + TILE_Y < 0) {
        return;
    }
    tileCase->outline.setPosition(position);
    tileCase->rectangle.setPosition(position);
    tileCase->hovered.setPosition(position);
    window.draw(tileCase->rectangle);
    if (this->isSelected)
        window.draw(tileCase->outline);
    if (this->isHovered && !this->isSelected)
        window.draw(tileCase->hovered);
    std::vector<std::string> itemDraw;
    for (size_t i = 0; i != item.size();i++) {
        if (std::find(itemDraw.begin(), itemDraw.end(), item[i].getType()) == itemDraw.end()) {
            item[i].draw(position, window);
            itemDraw.push_back(item[i].getType());
        }
    }
}

/**
 * @brief Method to add an item
 * @param int
 * @param std::string
 */
void graphical::tile::addItem(int type, std::string nb)
{
    item.push_back(graphical::item(type, assetTexture, nb));
}

/**
 * @brief Method to add an item
 * @param std::string
 */
void graphical::tile::addItem(std::string type)
{
    item.push_back(graphical::item(type, assetTexture));
}

/**
 * @brief Method to change an item type
 * @param std::string
 * @param int
 */
void graphical::tile::changeItemType(std::string nb, int newType)
{
    for (auto it = item.begin(); it != item.end(); it++) {
        if (it->getNb() == nb)
            it->changeType(newType);
    }
}

/**
 * @brief Method to delete an item depending on his number
 * @param std::string
 */
void graphical::tile::deleteThisItemByNb(std::string nb)
{
    for (auto it = item.begin(); it != item.end();it++) {
        if (nb == it->getNb()) {
            item.erase(it);
            return;
        }
    }
}

/**
 * @brief Method to delete an item
 * @param std::string
 */
void graphical::tile::deleteThisItem(std::string type)
{
    for (auto it = item.begin(); it != item.end();it++) {
        if (type == it->getType()) {
            item.erase(it);
            return;
        }
    }
}

/**
 * @brief Method to add a player
 * @param void
 */
void graphical::tile::addPlayer()
{
    nbrOfPlayerInThisTile += 1;
}

/**
 * @brief Method to remove a player
 * @param void
 */
void graphical::tile::delPlayer()
{
    nbrOfPlayerInThisTile -= 1;
}

void graphical::tile::setSelectedState(bool state) {
    this->isSelected = state;
}

bool graphical::tile::getSelectedState() const {
    return this->isSelected;
}

void graphical::tile::setHoveredState(bool state) {
    this->isHovered = state;
}

bool graphical::tile::getHoveredState() const {
    return this->isHovered;
}
