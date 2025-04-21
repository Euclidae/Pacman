#include "ghost.hpp"


Ghost::Ghost(std::string image,SDL_Renderer* renderer, mat::vector2f pos,mat::vector2f move_speed) : sprite(image), position(pos){
    frames = Animation(sprite, renderer, mat::vector2f{40,40}, position);
    destination = {position.x,position.y, SCREEN_WIDTH/COLUMNS -1, SCREEN_HEIGHT/ROWS -1};
}
void Ghost::draw(const float time){
    frames.change_sprite(time);
    frames.draw(destination);
}
void Ghost::change_mode(){
    
}
void Ghost::detect_collision(Pacman& pacman){}


void Ghost::flee(bool flee = false){}


void Ghost::update(float delta_time, Map& map){  
    SDL_FRect barrier;

    if(direction == UP){
        move_speed.y *= -1;
    }else if(direction == DOWN){
        move_speed.y = fabs(move_speed.y);
    }else if(direction == LEFT){
        move_speed.x *= -1;
    }else if(direction == RIGHT){
        move_speed.x = fabs(move_speed.x);
    }

    barrier = {destination.x + move_speed.x, destination.y + move_speed.y, destination.w,destination.y};
    
    for(auto& content: map.get)
    if(SDL_HasIntersection(barrier,) )
}
