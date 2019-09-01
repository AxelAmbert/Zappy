#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include "../include/ServerChoosingScene.hpp"
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include "../tools/include/stringManager.hpp"
#include "../include/zappy.hpp"

/**
 * @brief Method to scan and find available server
 * @param std::string
 */

void graphical::ServerChoosingScene::addNewReceivedData(uint32_t port, std::string buffer)
{
    std::vector<std::string> data = stringManager::my_str_to_word_array(buffer, " ");
    std::string nb;
    std::string time;
    int time_double = 0;

    if (data.size() != 3)
        return;
    nb += "NB of player = ";
    nb += data[1];
    nb += " ";
    time += "Time alive = ";
    time_double = std::atoi(data[2].c_str());
    time += std::to_string((time_double / 3600));
    time += " Hours ";
    time += std::to_string((time_double / 60));
    time += " Minutes ";
    time += std::to_string((time_double % 60));
    time += " Seconds ";

    for (auto &array : this->textList) {
        if (array[0].getString() == std::to_string(port)) {
            array[1].setString(nb);
            array[2].setString(time);
            return;
        }
    }
}

void graphical::ServerChoosingScene::receiveScanData()
{
    ssize_t response = 0;
    char buffer[1024];

    for (const auto &data : this->socketFound) {
        auto [tsocket, tport] = data;
        response = recv(tsocket, buffer, 1023, MSG_DONTWAIT);
        if (response > 0) {
            buffer[response] = '\0';
            this->addNewReceivedData(tport, buffer);
            this->socketFound.remove(data);
            this->socketToRemove.push_back(tsocket);
            return;
        }
    }
}

void graphical::ServerChoosingScene::addValidServersToStackPanel()
{
    this->serversFound.clear();
    this->miniStack.clear();
    this->textList.clear();
    this->serversFound.setOrientation(ez::Orientation::VERTICAL);
    for (const auto &value : this->socketFound) {
        auto &[socket, port] = value;
        (void)socket;
        textList.emplace_back(std::array<sf::Text, 3>());
        for (int i = 0; i < 3; i++) {
            textList.back()[i].setCharacterSize(20);
            textList.back()[i].setFont(basicFont);
        }
        textList.back()[0].setString(std::to_string(port));
        miniStack.emplace_back(ez::StackPanel(ez::Orientation::HORIZONTAL));
        miniStack.back().Add(&textList.back()[0], {0, 0});
        miniStack.back().Add(&textList.back()[1], {150, 0});
        miniStack.back().Add(&textList.back()[2], {150, 0});
        goButton.emplace_back(std::pair<ez::ClassicButton, int>(ez::ClassicButton(
                    "Client/Graphical/Assets/button_120x40_40x40.png", {40, 40},
                {0, 0}, {0, 0}), port));
        miniStack.back().Add(&goButton.back().first, {375, 0});
        serversFound.Add(&miniStack.back(), {0, 30});
    }
    serversFound.staticIt({1000, 500}, {300, 300}, window);
}

void graphical::ServerChoosingScene::checkServersValidity()
{
    char buffer[1024] = {0};
    ssize_t response = 0;
    std::list<std::pair<int, int>> validSocket;

    for (const auto &serverFound : socketFound) {
        auto [tsocket, tport] = serverFound;
        response = recv(tsocket, buffer, 10, MSG_DONTWAIT);
        if (response == 8) {
            buffer[response] = '\0';
            if (std::string(buffer) == std::string("WELCOME\n")) {
                memset(buffer, 0, 11);
                buffer[response] = '\0';
                send(tsocket, "GRAPHIC\nscan\n", strlen("GRAPHIC\nscan\n"), 0);
                validSocket.push_back({tsocket, tport});
            }
        }
    }
    socketFound = validSocket;
}

void graphical::ServerChoosingScene::scanForServers(std::string ip)
{
    int tmpSocket = 0;
    struct sockaddr_in dummy = {};
    struct sockaddr_in sockaddr;
    int connectTry = 0;

    for (const auto &data : this->socketToRemove) {
        shutdown(data, SHUT_RDWR);
        close(data);
    }
    socketFound.clear();
    socketToRemove.clear();
    tmpSocket = socket(AF_INET, SOCK_STREAM, 0);
    dummy.sin_family = AF_INET;
    struct hostent *hostinfo = NULL;
    hostinfo = gethostbyname(ip.c_str());
    if (hostinfo == NULL)
    {
        return;
    }
    dummy.sin_addr = *(struct in_addr *) hostinfo->h_addr;
    dummy.sin_port = htons(0);
    for (uint16_t i = 0; i < 65535; i++) {
        sockaddr = dummy;
        sockaddr.sin_port = htons(i);
        connectTry = connect(tmpSocket, (struct sockaddr *) &sockaddr,
                sizeof(sockaddr));
        if (connectTry == 0) {
            socketFound.push_back({tmpSocket, i});
            tmpSocket = socket(AF_INET, SOCK_STREAM, 0);
        }
    }
    this->checkServersValidity();
    this->addValidServersToStackPanel();
}
/**
 * @brief Method to run the scene
 * @param size_t &
 */
void graphical::ServerChoosingScene::run(size_t &sceneIndex)
{
    window.clear();
    while (window.pollEvent(event)) {
        ip.Actualize(event, window);
        okButton.Actualize(event, window);
        serversFound.Actualize(event, window);
        for (auto it = this->goButton.begin(); it != this->goButton.end(); it++) {
            auto &[button, port] = *it;
            if (button.getState() == ez::GuiState::RELEASED) {
                graphical::zappy *z = new graphical::zappy(ipAddr, port, window);
                if (scene.size() == 2)
                    scene.erase(scene.end() - 1);
                scene.push_back(z);
                sceneIndex = 1;
            }
        }
        if (event.type == sf::Event::Closed)
            window.close();
    }
    this->receiveScanData();
    window.draw(background);
    ip.Draw(window);
    okButton.Draw(window);
    serversFound.Draw(window);
    window.display();
}

/**
 * @brief ServerChoosingScene CTor
 * @param sf::RenderWindow &
 */
graphical::ServerChoosingScene::ServerChoosingScene(sf::RenderWindow &_window, std::vector<graphical::IScene*> &_scene) :
    window(_window),
    ip({{300, 200}, {700, 800}, -1, WINDOW_WIDTH, WINDOW_HEIGHT, "Enter IP address"}),
    serversFound(ez::Orientation::VERTICAL),
    okButton({"Client/Graphical/Assets/button_250x84_40x40_right.png", {84, 84}, {1565, 225}, {0, 0}}),
    scene(_scene)
{
    okButton.addOneElementInEventList(ez::GuiState::RELEASED,
            [](graphical::ServerChoosingScene &serverChoosingScene, std::string &ipAddr)
            {
                serverChoosingScene.scanForServers(serverChoosingScene.ip.GetKeyboardText());
                ipAddr = serverChoosingScene.ip.GetKeyboardText();
            }, *this, ipAddr);
    texture.loadFromFile("Client/Graphical/Assets/server-background.png");
    background.setSize({1920, 1080});
    background.setPosition({0, 0});
    background.setTexture(&texture);
    window.setFramerateLimit(60);
    basicFont.loadFromFile("Client/Graphical/Assets/bebas.otf");
}
