#include "Client.hpp"
#include "../Parsing/Parsing.hpp"
#include "Ai/Ai.hpp"

int main(int ac, char **av)
{
    clt::Ai bot;

    if (ac == 2 && strcmp(av[1], "-help") == 0) {
        clt::Parsing::printUsage();
        return 0;
    }
    if (!clt::Parsing::checkArgsNumber(ac) || !clt::Parsing::checkFlagsValidity(ac, av)) {
        clt::Parsing::printUsage();
        return 84;
    }
	if (clt::debug)
		std::cout << "Hello zappy client debug" << std::endl;
	else
		std::cout << "Hello zappy client release" << std::endl;
    bot.getInfo(ac, av);
    if (!bot.connectToServer()) {
        clt::Parsing::printUsage();
        return 84;
    }
    bot.joinGame();

	return 0;
}