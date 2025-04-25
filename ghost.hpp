#include "entity.hpp"
#include "globals.hpp"
#include "pacman.hpp"
#include "map.hpp"
#include "animation.hpp"
#include <cwchar>
class Ghost: public Entity{
    private:
        mat::vector2f position;
        mat::vector2f move_speed;
        std::string sprite;
        Animation frames;
        Ghost_Mode mode;
        SDL_FRect destination;
        Direction direction;
    public:
      Ghost() = default;
      Ghost(std::string image, SDL_Renderer* renderer, mat::vector2f pos, mat::vector2f move_speed, Direction def);
      void draw(float time);
      void update(float delta_time, Map& map);
      void change_mode();
      void detect_collision(Pacman& pacman);
      void flee(bool flee = false);
      void get_pos(mat::vector2f& new_pos);

      inline void move(){

      }
      SDL_FRect getEntityPos()const{
          return destination;
      }
};
