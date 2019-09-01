#ifndef CHAT_GUI_HPP
#define CHAT_GUI_HPP

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string_view>
#include <vector>
#include <list>
#include "StackElements.h"
#include "ClassicButton.h"
#include "TextField.h"
#include "../tools/include/tcpCommunication.hpp"
#include "../../../ezSFML/Slider.h"

namespace graphical {

class ChatGUI {
public:
	ChatGUI() = delete;
	ChatGUI(sf::FloatRect shape, sf::RenderWindow &	w, std::size_t msgBufSize = 25);
	ChatGUI(const ChatGUI &) = delete;
	ChatGUI(ChatGUI &&) = delete;
	~ChatGUI() = default;

	void actualize(sf::Event &event, sf::RenderWindow &w, graphical::tcpCommunication &comm);
	void draw(sf::RenderWindow &w);
	void pushMsg(const std::string_view &msg, sf::RenderWindow &w);
	void addReceivedMsg(std::string);
	void Open();
	void Close();
	bool isGUIOpen();
private:
	uint32_t totalSize;
	bool isOpen;
	sf::Clock animationClock;
	const std::size_t m_msgBufSize;
	const sf::FloatRect m_shape;
	ez::StackPanel m_stackPanel;
	ez::ClassicButton m_sendButton;
	ez::TextField m_inputField;
    sf::RectangleShape backPanel;
    sf::Texture panelTexture;
    std::vector<std::string> _msg;
	std::vector<sf::Text> m_messages;
	sf::Font m_messageFont;
    sf::RenderWindow &_window;
    ez::ClassicButton openButton;
    ez::ClassicButton closeButton;
};

}

#endif