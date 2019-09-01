#ifndef PSU_ZAPPY_2018_SERVERCHOOSING_HPP
#define PSU_ZAPPY_2018_SERVERCHOOSING_HPP

#include <StackElements.h>
#include <ClassicButton.h>
#include "GUI.h"
#include "TextField.h"
#include "IScene.hpp"
#include "../tools/include/tcpCommunication.hpp"
#include <thread>
#include <mutex>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>

namespace graphical {
   /**
    * @class ServerChoosingScene
    * @brief ServerChoosingScene class
    * @inherit Scene
    */
    class ServerChoosingScene : public IScene {
        public:
            ServerChoosingScene(sf::RenderWindow &_window, std::vector<graphical::IScene*> &);
            void run(size_t &sceneIndex) override;
    private:
            sf::Texture texture;
            sf::RectangleShape background;
            sf::Font basicFont;
            void checkServersValidity();
            void scanForServers(std::string port);
            void addValidServersToStackPanel();
            void receiveScanData();
            void addNewReceivedData(uint32_t socket, std::string buffer);
            void goAway();
            std::list<std::array<sf::Text, 3>> textList;
            std::list<ez::StackPanel> miniStack;
            sf::RenderWindow &window;
            sf::Event event;
            ez::TextField ip;
            ez::StackPanel serversFound;
            ez::ClassicButton okButton;
            std::list<std::pair<int, int>> socketFound;
            std::list<int> socketToRemove;
            std::list<std::pair<ez::ClassicButton, int>> goButton;
            std::string ipAddr;
            std::vector<graphical::IScene*> &scene;
    };
}


#endif //PSU_ZAPPY_2018_SERVERCHOOSING_HPP
