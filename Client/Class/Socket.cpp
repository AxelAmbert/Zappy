#include "Socket.hpp"

#include <iostream>

namespace clt {

/**
 * @brief Socket Ctor
 * @param std::size_t
 */
Socket::Socket(std::size_t bufferSize)
{
    m_fd = -1;
	m_buffer.resize(bufferSize);
}

/**
 * @brief Socket copy Ctor
 * @param const Socket::OptionalAddress &
 * @param std::size_t
 */
Socket::Socket(const Socket::OptionalAddress &a, std::size_t bufferSize)
	: m_addr(a)
{
    m_fd = -1;
	m_buffer.resize(bufferSize);
}

/**
 * @brief Socket copy  Ctor
 * @param clt::Socket &&
 */
Socket::Socket(clt::Socket &&s) noexcept
	: m_fd(s.m_fd), m_addr(s.m_addr)
{
}

/**
 * @brief Socket Dtor
 * @param void
 */
Socket::~Socket()
{
    if (m_fd != -1)
    	close(m_fd);
}

/**
 * @brief Operator overload for =
 * @param Socket &&
 * @return Socket &
 */
Socket &Socket::operator=(Socket &&s) noexcept
{
	if (m_fd != s.m_fd) {
		close(m_fd);
		m_fd = s.m_fd;
	}
	m_addr = s.m_addr;

	return *this;
}

/**
 * @brief Socket Dtor
 * @param void
 * @return bool
 */
bool Socket::createSocket()
{
    m_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (this->m_fd == -1) {
        perror("socket");
        return false;
    }
    return true;
}

/**
 * @brief Connect to a socket
 * @param void
 * @return bool
 */
bool Socket::connectTo(const Socket::OptionalAddress &a)
{
	m_addr = a;
	struct sockaddr_in oui{};
    struct hostent *hostinfo = NULL;

    hostinfo = gethostbyname(a->ip.data());
    if (!hostinfo)
        return false;
    if (m_addr) {
        oui.sin_family = AF_INET;
        oui.sin_port = htons((uint16_t)a->port);
        oui.sin_addr = *(IN_ADDR *) hostinfo->h_addr;
//        auto addr = toRaw((a.value()));
		if (connect(m_fd, (struct sockaddr *)&oui, (socklen_t )sizeof(oui)) == -1) {
            perror("connect");
            return false;
        }
	} else
	    return false;

    return true;
}

/**
 * @brief Connection getter
 * @param void
 * @return Socket::OptionalAddress
 */
Socket::OptionalAddress Socket::getConnectedTo() const noexcept
{
	return m_addr;
}

/**
 * @brief Set the buffer size
 * @param std::size_t
 */
void Socket::setBufferSize(std::size_t s)
{
	m_buffer.resize(s);
	m_buffer.clear();
}

/**
 * @brief Buffer size getter
 * @param void
 * @return std::size_t
 */
std::size_t Socket::getBufferSize() const noexcept
{
	return m_buffer.max_size();
}

/**
 * @brief Allow the socket to receive info
 * @param void
 * @return std::string
 */
std::string Socket::recive()
{
//	m_buffer.clear();
    char buffer[65536];

    bzero(&buffer, 65536);
//    read(m_fd, &buffer, 2048);
	::recv(m_fd, &buffer, 65536, 0);
	return buffer;
}

/**
 * @brief Allow the socket to send info
 * @param const std::string_view &
 */
void Socket::send(const std::string_view &msg)
{
	//write(m_fd, msg.data(), msg.length());
	::send(m_fd, msg.data(), msg.length(), 0);
}

/**
 * @brief Operator overload for >>
 * @param std::string
 * @return Socket &
 */
Socket &Socket::operator>>(std::string &msg)
{
	msg.clear();
	msg = recive();

	return *this;
}

/**
 * @brief Operator overload <<
 * @param const std::string_view &
 * @return Socket &
 */
Socket &Socket::operator<<(const std::string_view &msg)
{
	send(msg);

	return *this;
}

}