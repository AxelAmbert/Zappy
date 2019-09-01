#include "include/zappy.hpp"
#include "SFML/Audio.hpp"
#include "include/ServerChoosingScene.hpp"
#include <ctime>

int main(int argc, char **argv)
{
	std::srand(std::time(nullptr));
    std::vector<graphical::IScene*> scene;
    size_t sceneIndex = 0;
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "zappy", sf::Style::Fullscreen);

    if (argc <= 2) {
        graphical::ServerChoosingScene *choosingScene = new graphical::ServerChoosingScene(window, scene);
        scene.push_back(choosingScene);
    } else {
        graphical::zappy *z = new graphical::zappy(argv[1], atoi(argv[2]), window);
        scene.push_back(z);
    }


    while (window.isOpen()) {
        scene[sceneIndex]->run(sceneIndex);
    }
}