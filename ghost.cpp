#include "ghost.hpp"
#include "globals.hpp"
#include <SDL3/SDL_rect.h>


Ghost::Ghost(std::string image,SDL_Renderer* renderer, mat::vector2f pos,mat::vector2f move_speed) : sprite(image), position(pos){
    frames = Animation(sprite, renderer, mat::vector2f{32,31}, position);
    destination = {position.x,position.y, SCREEN_WIDTH/COLUMNS -1, SCREEN_HEIGHT/ROWS -1};
}
void Ghost::draw(const float time){
    frames.change_sprite(direction);
    frames.draw_entity(destination);
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

    barrier = {destination.x + move_speed.x, destination.y + move_speed.y, destination.w,destination.h};

    for(auto content : map.getMap()){
        if(SDL_HasRectIntersectionFloat(&barrier,&content)){
            uint8_t new_direction = rand() % 4;

            if(new_direction == 0){
                direction = Direction::UP;
            }else if(new_direction == 1){
                direction = Direction::DOWN;
            }else if(new_direction == 2){
                direction = Direction::LEFT;
            }else{
                direction = Direction::RIGHT;
            }
            break;
        }
    }

    if(barrier.y > SCREEN_HEIGHT){
        barrier.y = 0;
    }else if(barrier.y < 0){
        barrier.y = SCREEN_HEIGHT;
    }
    if(barrier.x > SCREEN_WIDTH){
        barrier.x = 0;
    }else if(barrier.x < 0){
        barrier.x = SCREEN_WIDTH;
    }
    destination = barrier;
}
