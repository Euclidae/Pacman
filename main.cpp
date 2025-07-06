
#ifdef _WIN32
#define SDL_MAIN_HANDLED
#endif
#include <iostream>
#include <string>
#include <regex>
#include "game.hpp"

int main(int argc, char** argv){
    std::string map_name;
    std::regex map_regex("^map[0-9]+$");
    std::cout << "Enter Map Name (format: mapNUMBER, e.g., map1) or default for default map: ";
    std::cin >> map_name;
    if(map_name == "default") {
        map_name = "map"; // Default map if user enters 'default'
    }
    else if (!std::regex_match(map_name, map_regex)) {
        std::cerr << "Invalid map name. Must be in format mapNUMBER (e.g., map1).\n";
        return 1;
    }

    std::string map_path = "assets/maps/" + map_name + ".txt";
    char* map_cstr = const_cast<char*>(map_path.c_str());
    Game game("Pacman", SCREEN_WIDTH, SCREEN_HEIGHT, map_cstr);
    game.loop();
    return 0;
}