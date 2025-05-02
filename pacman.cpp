#include "pacman.hpp"
#include "globals.hpp"

#include <SDL3/SDL_image.h>

Pacman::Pacman(std::string im, Direction dir, mat::vector2f pos, mat::vector2f dimensions, SDL_Renderer* rend, mat::vector2f vel){
    renderer = rend;
    direction = dir;
    image = im;
    pac_texture = IMG_LoadTexture(renderer, image.c_str());
    position = pos;
    dimensions = dimensions;
    is_alive = true;
    animation = Animation(image, renderer, dimensions, position);
    move_speed = vel;
    destination.w = CELL_SIZE - 4;
    destination.h = CELL_SIZE - 4;
    destination.x = position.x;
    destination.y = position.y;
}

SDL_FRect Pacman::get_pacman(){
    return destination;
}

void Pacman::draw(float time){
    animation.change_sprite(direction);
    animation.animate(time);
    animation.draw_entity(destination);

}

bool Pacman::detect_collision(Map& map, SDL_FRect& spider) {
    for(auto& content: map.getMap()) {
        if(spider.x < content.x + content.w && spider.x + spider.w > content.x &&
           spider.y < content.y + content.h && spider.y + spider.h > content.y) {
            return true;
        }
    }
    return false;
}

bool Pacman::detect_collision(std::vector<SDL_Point>& pellets, SDL_FRect& spider) {
    for(auto& content: pellets) {
        if(spider.x < content.x && spider.x + spider.w > content.x &&
           spider.y < content.y && spider.y + spider.h > content.y) {
            return true;
        }
    }
    return false;
}
void Pacman::update(float delta_time, Map& map){
    float x_move_speed = (move_speed.x * delta_time);
    float y_move_speed = (move_speed.y * delta_time);
    SDL_FRect spider = destination;

    switch(direction){
        case UP:
            spider.y -= y_move_speed;
            break;
        case DOWN:
            spider.y += y_move_speed;
            break;
        case LEFT:
            spider.x -= x_move_speed;
            break;
        case RIGHT:
            spider.x += x_move_speed;
            break;

        default:
            break;
    }

    if(detect_collision(map, spider)) spider = destination;
    if(detect_collision(map.get_pellets(),destination)) std::cout << "Place holder, removed pellet x : \n";

    destination = spider;
}

void Pacman::kill_pacman(bool& death){
    is_alive = false;
}

bool Pacman::detect_collision(SDL_FRect& entity){

}

void Pacman::change_direction(Direction dir){
    Direction opposite;
    switch(dir){
        case RIGHT:
            opposite = LEFT;
            break;
        case LEFT:
            opposite = RIGHT;
            break;
        case UP:
            opposite = DOWN;
            break;
        case DOWN:
            opposite = UP;
            break;
    }
    if(!(direction == opposite)){
        direction = dir;
    }
}
