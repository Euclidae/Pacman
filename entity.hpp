#pragma once
#include <string>
#include "animation.hpp"
#include "globals.hpp"
class Entity{
    public: 
        virtual inline void move() = 0;
        virtual SDL_FRect getEntityPos()const = 0;
};
