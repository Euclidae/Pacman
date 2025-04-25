#include "animation.hpp"
#include "entity.hpp"

class Pacman : public Entity{
    private:
    public:
        SDL_FRect get_pacman();
        bool trigger_death();
};
