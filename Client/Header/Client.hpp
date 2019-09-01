#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>

namespace clt {

#ifndef DEBUG
#define DEBUG 0
#endif

#if DEBUG == 1
static constexpr bool debug = true;
#else
static constexpr bool debug = false;
#endif

}

#endif