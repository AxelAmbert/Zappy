#include "../include/animation.hpp"

/**
 * @brief Animation CTor
 * @param std::string
 * @param sf::IntRect
 * @param int
 */
graphical::animation::animation(std::string name, sf::IntRect _rect, int _nbrOfElements)
{
    texture.loadFromFile(name);
    rect = _rect;
    nbrOfElements = _nbrOfElements;
    frameRate = 100000;
    sprite.setTexture(texture);
    sprite.setTextureRect(rect);
    stop = false;
}

/**
 * @brief Allow to stop the animation
 * @param bool
 */
int graphical::animation::currentLine(int y)
{
     return rect.top / y;
}

/**
 * @brief Allow to stop the animation
 * @param bool
 */
void graphical::animation::stopTheAnimation(bool _stop)
{
    stop = _stop;
}

/**
 * @brief Allow to set the YPos
 * @param int
 */
void graphical::animation::setYPos(int newPos)
{
    rect.top = newPos;
    sprite.setTextureRect(rect);
}

/**
 * @brief set the nbr of elem in
 * @param std::string Path to texture
 */
void graphical::animation::setNbrOfElements(int _nbrOfElem)
{
    nbrOfElements = _nbrOfElem;
}

/**
 * @brief Allow to set a texture from a path
 * @param std::string Path to texture
 */
void graphical::animation::setTexture(std::string name)
{
    texture.loadFromFile(name);
}

/**
 * @brief Allow to set a texture from a texture
 * @param sf::Texture & Texture that you want to set
 */
void graphical::animation::setTexture(sf::Texture &_texture)
{
    texture = _texture;
}

/**
 * @brief Draw a sprite
 * @param sf::RenderWindow & Reference to the window where you want the sprite to be draw
 * @param sf::Vector2f Position where you want the sprite to be displayee
 */
void graphical::animation::draw(sf::RenderWindow &window, sf::Vector2f pos)
{
    sprite.setPosition(pos);
    window.draw(sprite);
    if (stop) {
        rect.left = 0;
        sprite.setTextureRect(rect);
        return;
    }
    if ((int)clock.getElapsedTime().asMicroseconds() >= frameRate) {
        rect.left += rect.width;
        if (rect.left >= rect.width * nbrOfElements)
            rect.left = 0;
        sprite.setTextureRect(rect);
        clock.restart();
    }
}

/**
 * @brief Framerate Ssetter
 * @param int Framerate
 */
void graphical::animation::setFrameRate(int _frameRate)
{
    frameRate = _frameRate;
}