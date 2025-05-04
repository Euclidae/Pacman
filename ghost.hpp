#include "entity.hpp"
#include "globals.hpp"
#include "pacman.hpp"
#include "map.hpp"
#include "animation.hpp"
#include <cwchar>
#include <ctime>
#include <random>
#include <algorithm>
#include <cstdlib>

class Pacman;
class Ghost: public Entity{
    private:
        mat::vector2f position;
        mat::vector2f move_speed;
        std::string sprite;
        Animation frames;
        Ghost_Mode mode;
        SDL_FRect destination;
        SDL_FRect vessel;
        Direction direction;
        float last_direction_change;
        std::vector<Direction> possible_directions;
        void change_direction(Map& map);
        void get_possible_directions(Map& map, SDL_FRect& spider,float delta_time);
        void detect_collision(Pacman& pacman);
        bool detect_collision(Map& map, SDL_FRect& spider);
        std::string name;
    public:
      Ghost() = default;
      Ghost(std::string image, SDL_Renderer* renderer, mat::vector2f pos, mat::vector2f move_speed, Direction def, std::string n);
      void draw(float time);
      void update(float delta_time, Map& map, Pacman& pacman);
      void change_mode();
      void flee(bool flee = false);
      void get_pos(mat::vector2f& new_pos);


      inline void move(){

      }
      SDL_FRect getEntityPos()const{
          return destination;
      }
};
