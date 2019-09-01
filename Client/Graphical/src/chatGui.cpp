#include "../include/chatGui.hpp"

namespace graphical {

bool ChatGUI::isGUIOpen()
{
	return (isOpen);
}

ChatGUI::ChatGUI(sf::FloatRect shape, sf::RenderWindow &w, std::size_t msgBufSize)
	: m_msgBufSize(msgBufSize),
	m_shape(shape),
	m_stackPanel(ez::Orientation::VERTICAL),
	m_sendButton("Client/Graphical/Assets/button_120x40_40x40_right.png", {83, 83}, {395, 997}, {0, 0}),
	m_inputField(TextFieldInitStruct{{400, 83}, {0, 997}, -1, w.getSize().x, w.getSize().y, "Message"}),
	m_messages(0),
	_window(w),
	openButton({"Client/Graphical/Assets/button_120x40_40x40_right.png", {83, 83}, {478, 997}, {0, 0}}),
	closeButton({"Client/Graphical/Assets/button_120x40_40x40_left.png", {83, 83}, {478, 997}, {0, 0}})
{
    backPanel.setSize({500, 200});
    backPanel.setPosition({-95, 800});
    panelTexture.loadFromFile("Client/Graphical/Assets/backpanelclean.png");
    backPanel.setTexture(&panelTexture);
	this->m_messageFont = sf::Font();
	m_messageFont.loadFromFile("Client/Graphical/Assets/bebas.otf");
	m_stackPanel.staticIt(
		{500, 190},
		{8, 797},
		w
	);
	isOpen = true;
}

void ChatGUI::actualize(sf::Event &event, sf::RenderWindow &w, graphical::tcpCommunication &comm)
{
	m_inputField.Actualize(event, w);
	m_stackPanel.Actualize(event, w);
	m_sendButton.Actualize(event, w);
    std::list<std::string>::iterator it;
    if (isOpen == true) {
    	closeButton.Actualize(event, w);
    	if (closeButton.getState() == ez::GuiState::RELEASED) {
    		Close();
    	}
    } else {
    	openButton.Actualize(event, w);
		if (openButton.getState() == ez::GuiState::RELEASED) {
			Open();
		}
    }
	if (m_sendButton.getState() == ez::GuiState::RELEASED && m_inputField.GetKeyboardText().length() != 0) {
		std::string msg = "chat ";
		msg += m_inputField.GetKeyboardText();
		try {
			if (msg.at(6) != '/') {
				_msg.push_back(m_inputField.GetKeyboardText());
			}
		} catch (...) {

		}
		comm.send(msg);
		m_inputField.clear(w);
	}
}

void ChatGUI::draw(sf::RenderWindow &w)
{
	if (animationClock.getElapsedTime().asMilliseconds() >= 0.016f) {
		animationClock.restart();
		if (isOpen == true && m_inputField.getPosition().x < 0) {
			backPanel.move({10, 0});
			m_sendButton.setPosition((int) m_sendButton.getPosition().x + 10,
					(int) m_sendButton.getPosition().y);
			closeButton.setPosition((int) closeButton.getPosition().x + 10,
					(int) closeButton.getPosition().y);
			openButton.setPosition(closeButton.getPosition());
			m_inputField.setPosition({m_inputField.getPosition().x + 10, m_inputField.getPosition().y});
            m_stackPanel.staticIt(
                    {500, 200},
                    {m_inputField.getPosition().x + 8, backPanel.getPosition().y + 3},
                    w
            );
		} else if (isOpen == false && openButton.getPosition().x > 0) {
			backPanel.move({-10, 0});
			m_sendButton.setPosition((int) m_sendButton.getPosition().x - 10,
					(int) m_sendButton.getPosition().y);
			closeButton.setPosition((int) closeButton.getPosition().x - 10,
					(int) closeButton.getPosition().y);
			openButton.setPosition(closeButton.getPosition());
			m_inputField.setPosition({m_inputField.getPosition().x - 10, m_inputField.getPosition().y});
			m_stackPanel.staticIt(
                    {500, 190},
                    {m_inputField.getPosition().x + 8, backPanel.getPosition().y + 3},
                    w
            );
		}
	}
    w.draw(backPanel);
    m_sendButton.Draw(w);
	m_stackPanel.Draw(w);
	m_inputField.Draw(w);
	if (isOpen == true) {
		closeButton.Draw(w);
	} else {
		openButton.Draw(w);
	}
}

void ChatGUI::pushMsg(const std::string_view &, sf::RenderWindow &w)
{
    m_stackPanel.clear();
    m_stackPanel.setOrientation(ez::Orientation::VERTICAL);
	for (uint8_t i = 0; i < m_messages.size(); i++)
        m_stackPanel.Add(&m_messages[i], {0, 7.5});
	m_stackPanel.staticIt(
		{500, 190},
		{8, 800},
		w
	);
}

void ChatGUI::addReceivedMsg(std::string msg)
{
    _msg.push_back(msg);
    if (m_messages.size() > 5) {
    	_msg.erase(_msg.begin());
    	m_messages.erase(m_messages.begin());
    }
    m_messages.push_back(sf::Text(msg, m_messageFont, 30));
    pushMsg(msg, _window);
}


void ChatGUI::Open()
{
	isOpen = true;
}

void ChatGUI::Close()
{
	isOpen = false;
}

}