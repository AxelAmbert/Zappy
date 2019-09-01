#include "../include/stringManager.hpp"

/**
 * @brief Method to convert a string into a string array
 * @param std::string
 * @param std::string
 * @return std::vector<std::string>
 */
std::vector<std::string> stringManager::my_str_to_word_array(std::string str,
            std::string delimiter)
{
    std::vector<std::string> result;
    size_t pos = 0;
    std::string token("");

    while ((pos = str.find(delimiter)) != std::string::npos) {
        token = str.substr(0, pos);
        if (token.size())
            result.push_back(token);
        str.erase(0, pos + delimiter.length());
    }
    if (str.size())
        result.push_back(str);
    return result;
}

/**
 * @brief Method to clean a string
 * @param std::string &
 * @param char
 */
void stringManager::clearStr(std::string &str, char c)
{
    for (auto it = str.begin(); it != str.end(); it++) {
        if (*it == c) {
            str.erase(it);
            return;
        }
    }
}