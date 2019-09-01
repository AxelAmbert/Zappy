cmake_minimum_required(VERSION 3.9)

project(PSU_zappy_2018 C CXX)

# Cmake helper booleans setup
# Build mode
if(CMAKE_BUILD_TYPE MATCHES Debug)
    set(MODE_DEBUG TRUE)
    set(MODE_RELEASE FALSE)
    set(MODE "debug")
else()
    set(MODE_DEBUG FALSE)
    set(MODE_RELEASE TRUE)
    set(MODE "release")
endif()
# End helpers

# CMake packages
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_LIST_DIR}/cmake_modules)
find_package(SFML 2 COMPONENTS system window graphics audio QUIET)
if (${SFML_FOUND})
    message(STATUS "Found installed SFML.")
else()
    message(FATAL_ERROR "No installation of SFML found, aborting.")
endif()

get_filename_component(SFML_SYSTEM_DIR ${SFML_SYSTEM_LIBRARY_RELEASE} DIRECTORY)
get_filename_component(SFML_WINDOW_DIR ${SFML_SYSTEM_LIBRARY_RELEASE} DIRECTORY)
get_filename_component(SFML_GRAPHICS_DIR ${SFML_GRAPHICS_LIBRARY_RELEASE} DIRECTORY)
get_filename_component(SFML_AUDIO_DIR ${SFML_AUDIO_LIBRARY_RELEASE} DIRECTORY)
set(SFML_DIR ${SFML_SYSTEM_DIR} ${SFML_WINDOW_DIR} ${SFML_GRAPHICS_DIR} ${SFML_AUDIO_DIR})
list(REMOVE_DUPLICATES SFML_DIR)
# End packages

# C CXX Zappy sources
file(GLOB_RECURSE SERVER_SOURCES "Server/*.c")
set(CLIENT_SOURCES
        Client/Src/Main.cpp
        Client/Class/Ai/Ai.cpp
        Client/Class/Socket.cpp
        Client/Parsing/Parsing.cpp
        Client/Class/Command.cpp
        Client/Class/Ai/AiServerAnswersManagement.cpp
        Client/Class/Ai/AiAlgoManagement.cpp
        Client/Class/Ai/AiSearchObject.cpp
        Client/Class/Ai/AiLevelUp.cpp
        Client/Class/Ai/AiMouvement.cpp Client/Class/Ai/AiBroadcast.cpp)

file(GLOB_RECURSE GRAPHICAL_SOURCES "Client/Graphical/*.cpp")
file(GLOB_RECURSE EZ_SFML_SOURCES "ezSFML/*.cpp")
# End sources


# Zappy targets
link_libraries(${SFML_DIR})

# Server
add_executable(zappy_server ${SERVER_SOURCES})
target_include_directories(zappy_server PRIVATE Server/Header Server/libc)
target_link_libraries(zappy_server PRIVATE m)
set_target_properties(zappy_server PROPERTIES C_STANDARD 99 C_STANDARD_REQUIRED ON RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})
target_compile_options(zappy_server PRIVATE "-Wall" "-Wextra" "-Wpedantic" "-Wunused")
if(MODE_DEBUG)
    target_compile_definitions(zappy_server PRIVATE "DEBUG=1")
    target_compile_options(zappy_server PRIVATE "-g" "-g3")
endif()

# AI Client
add_executable(zappy_ai ${CLIENT_SOURCES})
target_include_directories(zappy_ai PRIVATE Client/Header Client/Class)
target_link_libraries(zappy_ai PRIVATE pthread)
set_target_properties(zappy_ai PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})
target_compile_options(zappy_ai PRIVATE "-Wall" "-Wextra" "-Wpedantic" "-Wunused")
if(MODE_DEBUG)
    target_compile_definitions(zappy_ai PRIVATE "DEBUG=1")
    target_compile_options(zappy_ai PRIVATE "-g" "-g3")
endif()

# Graphical Client
add_executable(zappy_graphical ${GRAPHICAL_SOURCES} ${EZ_SFML_SOURCES})
target_include_directories(zappy_graphical PRIVATE ${SFML_INCLUDE_DIR} Client/Header Client/Class)
target_include_directories(zappy_graphical PRIVATE ${SFML_INCLUDE_DIR} ezSFML Client/Graphical)
target_link_libraries(zappy_graphical PRIVATE pthread m sfml-system sfml-window sfml-graphics sfml-audio)
set_target_properties(zappy_graphical PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})
target_compile_options(zappy_graphical PRIVATE "-Wall" "-Wextra" "-Wpedantic" "-Wunused")
if(MODE_DEBUG)
    target_compile_definitions(zappy_graphical PRIVATE "DEBUG=1")
    target_compile_options(zappy_graphical PRIVATE "-g" "-g3")
endif()
# End zappy
