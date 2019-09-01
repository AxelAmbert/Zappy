#include "../include/item.hpp"

/**
 * @brief Item CTor
 * @param int
 * @param sf::Texture &
 * @param std::string
 */
graphical::item::item(int _type, sf::Texture &assetTexture, std::string _nb)
{
    randVector = {(float)(std::rand() % (TILE_X - 23)), (float)(std::rand() % (TILE_Y - 34))};
    mapItem.insert({0, "food"});
    mapItem.insert({1, "linemate"});
    mapItem.insert({2, "deraumere"});
    mapItem.insert({3, "sibur"});
    mapItem.insert({4, "mendiane"});
    mapItem.insert({5, "phiras"});
    mapItem.insert({6, "thystame"});
    mapItem.insert({7, "egg"});
    mapItem.insert({8, "egg_h"});
    type = mapItem[_type];
    sprite.setTexture(assetTexture);
    sprite.setTextureRect(sf::IntRect(23 * _type, 0, 23, 34));
    nb = _nb;
}

/**
 * @brief Item copy CTor
 * @param int
 * @param sf::Texture &
 */
graphical::item::item(std::string _type, sf::Texture &assetTexture)
{
    randVector = {(float)(std::rand() % (TILE_X - 23)), (float)(std::rand() % (TILE_Y - 34))};
    type = _type;
    std::map<std::string, int> mapType;
    mapType.insert({"food", 0});
    mapType.insert({"linemate", 1});
    mapType.insert({"deraumere", 2});
    mapType.insert({"sibur", 3});
    mapType.insert({"mendiane", 4});
    mapType.insert({"phiras", 5});
    mapType.insert({"thystame", 6});
    mapType.insert({"egg", 7});
    mapType.insert({"egg_h", 8});
    sprite.setTexture(assetTexture);
    sprite.setTextureRect(sf::IntRect(23 * mapType[_type], 0, 23, 34));
}

/**
 * @brief Item copy CTor
 * @param int
 * @param sf::Texture &
 */
graphical::item::item(int _type, sf::Texture &assetTexture)
{
    randVector = {(float)(std::rand() % (TILE_X - 23)), (float)(std::rand() % (TILE_Y - 34))};
    mapItem.insert({0, "food"});
    mapItem.insert({1, "linemate"});
    mapItem.insert({2, "deraumere"});
    mapItem.insert({3, "sibur"});
    mapItem.insert({4, "mendiane"});
    mapItem.insert({5, "phiras"});
    mapItem.insert({6, "thystame"});
    mapItem.insert({7, "egg"});
    mapItem.insert({8, "egg_h"});
    type = mapItem[_type];
    sprite.setTexture(assetTexture);
    sprite.setTextureRect(sf::IntRect(23 * _type, 0, 23, 34));
}

/**
 * @brief Draw an item
 * @param sf::Vector2f Position where you want the item to be displayed
 * @param sf::RenderWindow & Window where you want to draw the item in
 */
void graphical::item::draw(sf::Vector2f position, sf::RenderWindow &window)
{
    sprite.setPosition(position + randVector);
    window.draw(sprite);
}

/**
 * @brief Type getter
 * @param void
 * @return std::string
 */
std::string graphical::item::getType() const
{
    return type;
}

/**
 * @brief Number of item getter
 * @param void
 * @return std::string
 */
std::string graphical::item::getNb() const
{
    return nb;
}

/**
 * @brief Type setter
 * @param int
 */
void graphical::item::changeType(int newType)
{
    type = mapItem[newType];
    sprite.setTextureRect(sf::IntRect(23 * newType, 0, 23, 34));
}