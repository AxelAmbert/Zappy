#ifndef PSU_ZAPPY_2018_TCPCOMMUNICATION_H
#define PSU_ZAPPY_2018_TCPCOMMUNICATION_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <string>
#include <iostream>
#include <sys/select.h>

typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;

namespace graphical {
    /**
     * @class tcpCommunication
     * @brief tcpCommunication class
     */
    class tcpCommunication {
    public:
        tcpCommunication(std::string, int);
        std::string get();
        void send(std::string);
        bool updateReadAvailability();
        void addASocketToReadList(int socket);
        void removeASocketFromReadList(int socket);
        void clearReadList();
        bool socketIsReady(int socket);
        std::string getHostame() {return (hostname);}
        template <typename timeValue>
        void setReadTimeOut(timeValue seconds, timeValue microseconds)
        {
            saveTimeout.tv_sec = seconds;
            saveTimeout.tv_usec = microseconds;
        }
        int getSocket();
        struct timeval getTimeout();
        std::string waitThisFuction(std::string);
    private:
        struct timeval timeout;
        struct timeval saveTimeout;
        fd_set readList;
        fd_set saveReadList;
        std::string hostname;
        uint32_t maxfd;
        SOCKADDR_IN sin;
        int sock;
    };
}

#endif //PSU_ZAPPY_2018_TCPCOMMUNICATION_H
