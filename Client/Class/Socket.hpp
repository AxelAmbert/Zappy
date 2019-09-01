#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <string_view>
#include <algorithm>
#include <optional>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <string>
#include <iostream>
#include <sys/select.h>

extern "C" {

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <strings.h>

}
typedef struct in_addr IN_ADDR;

namespace clt {
   /**
	* @class Socket
	* @brief Socket class
	*/
    class Socket {
        public:
            struct Address {
                std::string_view ip;
                std::uint16_t port;
            };

            using OptionalAddress = std::optional<Address>;
            static constexpr auto noAddress = std::nullopt;
        private:
            union SocketAddr {
                struct sockaddr raw;
                struct sockaddr_in ip4;
                struct sockaddr_in6 ip6;
            };

            static inline struct sockaddr toRaw(const Address &a)
            {
				auto addr = SocketAddr{};

				addr.ip4.sin_family = AF_INET;
				addr.ip4.sin_addr = in_addr{inet_addr(a.ip.data())};
				addr.ip4.sin_port = htons(a.port);

				return addr.raw;
            }
        public:
            explicit Socket(std::size_t bufferSize = 2048);
            explicit Socket(const OptionalAddress &a, std::size_t bufferSize = 2048);
            explicit Socket(const Socket &s) = delete;
            Socket(Socket &&s) noexcept;
            ~Socket();

            Socket &operator =(const Socket &s) = delete;
            Socket &operator =(Socket &&s) noexcept;

            bool createSocket();
            bool connectTo(const OptionalAddress &a);
            OptionalAddress getConnectedTo() const noexcept;

            void setBufferSize(std::size_t s);
            std::size_t getBufferSize() const noexcept;

            std::string recive();
            void send(const std::string_view &msg);

            Socket &operator >>(std::string &msg);
            Socket &operator <<(const std::string_view &msg);
        private:
            int m_fd;
            std::string m_buffer;
            OptionalAddress m_addr = noAddress;
        };
}

#endif