#include "Parsing.hpp"

/**
 * @brief Method to print usage
 * @param void
 */
void clt::Parsing::printUsage()
{
    std::cout << "USAGE: ./zappy_ai -p port -n name -h machine" << std::endl;
    std::cout << "\tport\t is the port number" << std::endl;
    std::cout << "\tname\t is the name of the team" << std::endl;
    std::cout << "\tmachine\t is the name of the machine; localhost by default" << std::endl;
}

/**
 * @brief Method to check if the number of argument passed to the program is correct
 * @param int
 * @return bool
 */
bool clt::Parsing::checkArgsNumber(int ac)
{
    if (ac != 5 && ac != 7) {
        std::cerr << "Invalid number of arguments !" << std::endl;
        return false;
    }
    return true;
}

/**
 * @brief Method to check if the flags passed to the program are correct
 * @param int
 * @param char **
 * @return bool
 */
bool clt::Parsing::checkFlagsValidity(int ac, char **av)
{
    std::map<char, bool> flag;

    flag.insert(std::pair<char, bool>('p', false));
    flag.insert(std::pair<char, bool>('n', false));
    flag.insert(std::pair<char, bool>('h', false));

    for (int i = 1; i < ac; i += 2) {
        if(av[i][0] != '-' || strlen(av[i]) != 2) {
            std::cerr << "Invalid flag : '" << av[i] << "' is not a flag !" << std::endl;
            return false;
        }
        if (av[i][1] != 'p' && av[i][1] != 'n' && av[i][1] != 'h') {
            std::cerr << "Invalid flag : '" << av[i][1] << "' !" << std::endl;
            return false;
        }
        if (!flag[av[i][1]])
            flag[av[i][1]] = true;
        else {
            std::cerr << "Invalid flag : '" << av[i][1] << "' already found !" << std::endl;
            return false;
        }
        if (av[i][1] == 'p' && !checkPortValidity(av[i + 1]))
            return false;
    }
    return true;
}

/**
 * @brief Method to check if the asked port is available
 * @param std::string
 * @return bool
 */
bool clt::Parsing::checkPortValidity(std::string str)
{
    for (int i = 0; str[i]; i++) {
        if (!isdigit(str[i])) {
            std::cerr << "Invalid Port: '"<< str << "' !" << std::endl;
            return false;
        }
    }
    return true;
}
