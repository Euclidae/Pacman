#include "game.hpp"

int main(int argc, char** argv){
    Game game("Pacman", SCREEN_WIDTH,SCREEN_HEIGHT);
    game.loop();
    return 0;
}
