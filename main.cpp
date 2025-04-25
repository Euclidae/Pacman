#include "game.hpp"

int main(int argc, char** argv){
    Game game("Pacman", SCREEN_WIDTH,SCREEN_HEIGHT);
    game.loop();
    std::cout << "\033[031mThe game is over, thank you for your patronage\n";
    return 0;
}
