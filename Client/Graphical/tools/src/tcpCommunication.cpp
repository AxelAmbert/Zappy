#include <strings.h>
#include "../include/tcpCommunication.hpp"

/**
 * @brief tcpCommunication CTor
 * @param std::string
 * @param int
 */

graphical::tcpCommunication::tcpCommunication(std::string hostname, int port)
{
    this->hostname = hostname;
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock == -1)
    {
        perror("socket()");
        exit(errno);
    }
    struct hostent *hostinfo = NULL;
    bzero(&sin, sizeof(sin));

    hostinfo = gethostbyname(hostname.c_str());
    if (hostinfo == NULL)
    {
        std::cerr << "Unknown host " << hostname << ".\n";
        exit(84);
    }

    sin.sin_addr = *(IN_ADDR *) hostinfo->h_addr;
    sin.sin_port = htons(port);
    sin.sin_family = AF_INET;

    if(connect(sock,(SOCKADDR *) &sin, sizeof(SOCKADDR)) == -1)
    {
        perror("connect()");
        exit(errno);
    }
    FD_ZERO(&readList);
    FD_ZERO(&saveReadList);
    FD_SET(sock, &saveReadList);
    maxfd = sock;
}

/**
 * @brief Method to receive via tcp communication
 * @param void
 * @return std::string
 */
std::string graphical::tcpCommunication::get()
{
    char buffer[65000];
    int n = 0;

    if((n = recv(sock, buffer, sizeof buffer - 1, 0)) < 0)
    {
        perror("recv()");
        exit(errno);
    }
    buffer[n] = '\0';
    std::string buffer_string(buffer);
    return buffer_string;
}

/**
 * @brief Method to send via txp communication
 * @param std::string
 */
void graphical::tcpCommunication::send(std::string data)
{
    if(sendto(sock, data.c_str(), data.size(), 0, (SOCKADDR *)&sin, sizeof(sin)) < 0)
    {
        perror("sendto()");
        exit(errno);
    }
}

/**
 * @brief Method to update the availability of the socket to read
 * @param void
 * @return bool
 */
bool graphical::tcpCommunication::updateReadAvailability()
{
    timeout = saveTimeout;
    readList = saveReadList;
    if (select(maxfd + 1, &readList, NULL, NULL, &timeout) == 0) {
        return false;
    }
    return true;
}

/**
 * @brief Method to add a socket to the read list
 * @param int
 */
void graphical::tcpCommunication::addASocketToReadList(int socket)
{
    FD_SET(socket, &readList);
    FD_SET(socket, &saveReadList);
    if ((uint32_t)socket > maxfd)
        maxfd = socket;
}

/**
 * @brief Method to remove a socket from the read list
 * @param int
 */
void graphical::tcpCommunication::removeASocketFromReadList(int socket)
{
    FD_CLR(socket, &readList);
}

/**
 * @brief Method to clear the read list
 * @param void
 */
void graphical::tcpCommunication::clearReadList()
{
    FD_ZERO(&readList);
}

/**
 * @brief Socket getter
 * @param void
 * @return int
 */
int graphical::tcpCommunication::getSocket()
{
    return (sock);
}

/**
 * @brief Socket status getter
 * @param int
 * @return bool
 */
bool graphical::tcpCommunication::socketIsReady(int socket)
{
    return (FD_ISSET(socket, &readList));
}

/**
 * @brief Timeout getter
 * @param void
 * @return struct timeval
 */
struct timeval graphical::tcpCommunication::getTimeout()
{
    return (timeout);
}

std::string graphical::tcpCommunication::waitThisFuction(std::string functionName)
{
    while (1) {
        std::string tmp = get();
        if (tmp.find(functionName) != std::string::npos) {
            return tmp;
        }
    }
}