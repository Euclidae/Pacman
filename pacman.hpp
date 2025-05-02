#ifndef PACMAN_HPP
#define PACMAN_HPP
#include "animation.hpp"
#include "entity.hpp"
#include "globals.hpp"
#include "map.hpp"

class Pacman{
    private:
        std::string image;
        mat::vector2f move_speed;
        Direction direction;
        bool is_alive;
        mat::vector2f position;
        int power_time_limit;
        //Pacman_Mode pacman_mode;
        SDL_Renderer* renderer = nullptr;
        SDL_Texture* pac_texture = nullptr;
        SDL_FRect destination;
        Animation animation;
    public:
        Pacman() = default;
        Pacman(std::string im, Direction dir, mat::vector2f pos, mat::vector2f dimensions, SDL_Renderer* rend, mat::vector2f vel);
        SDL_FRect get_pacman();
        void draw(float times);
        void update(float delta_time, Map& map);
        void kill_pacman(bool& death);
        bool detect_collision(SDL_FRect& entity);
        bool detect_collision(Map& map, SDL_FRect& spider);
        void change_direction(Direction dir);
        bool detect_collision(std::vector<SDL_Point>& pellets, SDL_FRect& spider);
        Animation get_animator() const{
            return animation;
        }
};
#endif
