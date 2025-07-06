#ifndef PACMAN_HPP
#define PACMAN_HPP
#include "animation.hpp"
#include "entity.hpp"
#include "globals.hpp"
#include "map.hpp"
#include <algorithm>

class Pacman{
    private:
        std::string image;
        mat::vector2f move_speed;
        Direction direction;
        bool is_alive;
        mat::vector2f position;
        int power_time_limit;
        int power_pellet_timer;
        bool is_powered;
        int lives;
        //Pacman_Mode pacman_mode;
        SDL_Renderer* renderer = nullptr;
        SDL_Texture* pac_texture = nullptr;
        SDL_FRect destination;
        Animation animation;
    public:
        Pacman() = default;
        Pacman(std::string im, Direction dir, mat::vector2f pos, mat::vector2f dimensions, SDL_Renderer* rend, mat::vector2f vel);
        SDL_FRect& get_pacman();
        void draw(float times);
        void update(float delta_time, Map& map, int& score);
        void kill_pacman(bool& death);
        bool detect_collision(SDL_FRect& entity);
        bool detect_collision(Map& map, SDL_FRect& spider);
        void change_direction(Direction dir, Map& map);
        bool remove_pellets(std::vector<SDL_Point>& pellets, SDL_FRect& spider, int& score);
        bool remove_power_pellets(std::vector<SDL_Point>& power_pellets, SDL_FRect& spider);
        void lose_life();
        void reset_position(mat::vector2f spawn_pos);
        void restore_alive_status();
        mat::vector2f get_position() const{
            return position;
        }
        bool is_pacman_ok() const{
            return is_alive;
        }
        mat::vector2f get_velocity() const{
            return move_speed;
        }
        Animation get_animator() const{
            return animation;
        }
        int get_lives() const{
            return lives;
        }
        bool is_powered_up() const{
            return is_powered;
        }
        void set_lives(int new_lives){
            lives = new_lives;
        }
};
#endif
