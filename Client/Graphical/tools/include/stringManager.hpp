#ifndef PSU_ZAPPY_2018_STRINGMANAGER_H
#define PSU_ZAPPY_2018_STRINGMANAGER_H

#include <vector>
#include <string>

/**
 * @class StringManager
 * @brief StringManager class
 */
class stringManager {
public:
    static std::vector<std::string> my_str_to_word_array(std::string str, std::string delimiter);
    static void clearStr(std::string &str, char c);
};


#endif //PSU_ZAPPY_2018_STRINGMANAGER_H
