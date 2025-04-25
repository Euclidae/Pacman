#include "ghost.hpp"
#include "globals.hpp"
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_stdinc.h>


Ghost::Ghost(std::string image,SDL_Renderer* renderer, mat::vector2f pos,mat::vector2f move_speed, Direction def = Direction::UP) : sprite(image), position(pos), move_speed(move_speed){
    frames = Animation(sprite, renderer, mat::vector2f{CELL_SIZE,31}, position);
    destination = {position.x,position.y, SCREEN_WIDTH/COLUMNS - 2 , SCREEN_HEIGHT/ROWS - 2};
    direction = def;
}
void Ghost::draw(const float time){
    frames.change_sprite(direction);
    frames.draw_entity(destination);
}
void Ghost::change_mode(){

}
void Ghost::detect_collision(Pacman& pacman){}


void Ghost::flee(bool flee){}

void change_direction(Direction& dir){
    Direction compass [] = {UP,DOWN,LEFT,RIGHT};
    uint8_t index_skip = 0;
    if(dir == RIGHT){
        index_skip = 3;
    }else if(dir == LEFT){
        index_skip = 2;
    }else if(dir == DOWN){
        index_skip = 1;
    }else{
        index_skip = 0;
    }

    uint8_t new_dir = rand() % 4;
    while(compass[new_dir] == dir){
        new_dir = rand() % 4;
    }
    dir = compass[new_dir];
}

void Ghost::update(float delta_time, Map& map){
    std::cout<< "Move vector x :" << move_speed.x << std::endl;
    std::cout<< "Move vector y :" << move_speed.y << std::endl;
    SDL_FRect spider = destination;
    bool change_dir = false;

    if(direction == UP){
        spider.y -= CELL_SIZE;
        for(auto& content: map.getMap()){
            if(spider.x < content.x + spider.w && spider.x + spider.w > content.x && spider.y < content.y + content.h && spider.y + spider.h > content.y){
                change_dir = true;
                break;
            }
        }
        if(change_dir){
            change_direction(direction);
            change_dir = false;
        }else{
            destination = spider;
        }
    }else if(direction == DOWN){
        spider.y += CELL_SIZE;
        for(auto& content: map.getMap()){
            if(spider.x < content.x + spider.w && spider.x + spider.w > content.x && spider.y < content.y + content.h && spider.y + spider.h > content.y){
                change_dir = true;
                break;
            }
        }
        if(change_dir){
            change_direction(direction);
            change_dir = false;
        }else{
            destination = spider;
        }
    }else if(direction == LEFT){
        spider.x -= CELL_SIZE;
        for(auto& content: map.getMap()){
            if(spider.x < content.x + spider.w && spider.x + spider.w > content.x && spider.y < content.y + content.h && spider.y + spider.h > content.y){
                change_dir = true;
                break;
            }
        }
        if(change_dir){
            change_direction(direction);
            change_dir = false;
        }else{
            destination = spider;
        }
    }else if(direction == RIGHT){
        spider.x += CELL_SIZE;

        for(auto& content: map.getMap()){
            if(spider.x < content.x + spider.w && spider.x + spider.w > content.x && spider.y < content.y + content.h && spider.y + spider.h > content.y){
                change_dir = true;
                break;
            }
        }
        if(change_dir){
            change_direction(direction);
            change_dir = false;
        }else{
            destination = spider;
        }
        if(spider.x > SCREEN_WIDTH){
            spider.x = 0;
        }else if(spider.x < 0){
            spider.x = SCREEN_WIDTH - CELL_SIZE;
        }

        if(spider.y > SCREEN_HEIGHT){
            spider.y = 0;
        }else if(spider.x < 0){
            spider.y = SCREEN_HEIGHT;
        }
    }

    int random = rand() % 50;
    if(random == 5){
        change_direction(direction);
    }


}
