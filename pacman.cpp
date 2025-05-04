#include "pacman.hpp"
#include "globals.hpp"
#include "map.hpp"

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

SDL_FRect& Pacman::get_pacman(){
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

bool Pacman::remove_pellets(std::vector<SDL_Point>& pellets, SDL_FRect& spider) {
    for (auto it = pellets.begin(); it != pellets.end();) {
        // Compute distances between pellet center and pacman center
        float pacmanCenterX = spider.x + (spider.w / 2);
        float pacmanCenterY = spider.y + (spider.h / 2);
        float pelletX = static_cast<float>(it->x);
        float pelletY = static_cast<float>(it->y);

        // Use distance-based collision with a reasonable radius
        float distance = std::sqrt(
            std::pow(pacmanCenterX - pelletX, 2) +
            std::pow(pacmanCenterY - pelletY, 2)
        );

        // If distance is less than collision radius, remove the pellet
        if (distance < (spider.w / 2)) {
            it = pellets.erase(it);
            std::cout << "Pellet eaten!" << std::endl;
            return true;
        } else {
            ++it;
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
    remove_pellets(map.get_pellets(), spider);
    destination = spider;
}

void Pacman::kill_pacman(bool& death){
    is_alive = false;
}

bool Pacman::detect_collision(SDL_FRect& entity){

}

void Pacman::change_direction(Direction dir,Map& map){
    Direction opposite;
    float increment = 1.0f; //just checking if walls are touched
    bool allow_dir_change = false;
    SDL_FRect spider = destination;
    switch(dir){
        case RIGHT:
            spider.x += increment;
            opposite = LEFT;
            break;
        case LEFT:
            spider.x -= increment;
            opposite = RIGHT;
            break;
        case UP:
            spider.y -= increment;
            opposite = DOWN;
            break;
        case DOWN:
            spider.y += increment;
            opposite = UP;
            break;
    }

    allow_dir_change = !(detect_collision(map, spider));
    spider = destination;

    if(!(direction == opposite) && allow_dir_change){
        //TODO stop pacman from facing to the left if there is wall on left, for example
        direction = dir;
    }
}
