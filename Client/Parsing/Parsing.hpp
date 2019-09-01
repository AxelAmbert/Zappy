#ifndef PSU_ZAPPY_2018_PARSING_HPP
#define PSU_ZAPPY_2018_PARSING_HPP

#include <iostream>
#include <string>
#include <cstring>
#include <map>

namespace clt {
   /**
    * @class Parsing
    * @brief Parsing class
    */
    class Parsing {
        public:
        static void printUsage();
        static bool checkArgsNumber(int ac);
        static bool checkPortValidity(std::string str);
        static bool checkFlagsValidity(int ac, char **av);
    };
}

#endif //PSU_ZAPPY_2018_PARSING_HPP
