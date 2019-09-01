##
## EPITECH PROJECT, 2018
## Zappy
## File description:
## Makefile
##

.PHONY: doc

## Release targets

all: zappy_ai zappy_server zappy_graphical

doc:
	rm -rf doc/oxygen
	doxygen doc/doxygen.conf

zappy_ai: cmake
	cmake --build build --target zappy_ai --config Release

zappy_server: cmake
	cmake --build build --target zappy_server --config Release

zappy_graphical: cmake
	cmake --build build --target zappy_graphical --config Release

cmake:
	mkdir -p build && cd build && cmake -DCMAKE_BUILD_TYPE=Release ..

clean:
	rm -rf build/*

fclean: clean
	rm -f zappy_server
	rm -f zappy_ai
	rm -f zappy_graphical

re: fclean all

## Debug target

debug: zappy_ai_debug zappy_server_debug

zappy_ai_debug: cmake_debug
	cmake --build build --target zappy_ai --config Debug

zappy_server_debug: cmake_debug
	cmake --build build --target zappy_server --config Debug

zappy_graphical_debug: cmake_debug
	cmake --build build --target zappy_graphical --config Debug

cmake_debug:
	mkdir -p build && cd build && cmake -DCMAKE_BUILD_TYPE=Debug ..

re_debug: fclean debug
