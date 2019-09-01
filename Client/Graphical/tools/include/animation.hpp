//
// Created by akacprzak on 5/30/19.
//

#ifndef PSU_ZAPPY_2018_ANIMATION_H
#define PSU_ZAPPY_2018_ANIMATION_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <list>

namespace graphical {
       /**
		* @class animation
		* @brief animation class
		*/
        class animation {
            public:
                animation(std::string _name, sf::IntRect _rect, int _nbrOfElements);
                void setTexture(std::string);
                void setYPos(int);
                void setTexture(sf::Texture &);
                void draw(sf::RenderWindow &, sf::Vector2f);
                void setFrameRate(int);
                void stopTheAnimation(bool = true);
                void setNbrOfElements(int);
                int currentLine(int);

            private:
                bool stop;
                sf::IntRect rect;
                sf::Texture texture;
                int nbrOfElements;
                sf::Clock clock;
                int frameRate;
                sf::Sprite sprite;
        };
}


#endif //PSU_ZAPPY_2018_ANIMATION_H
