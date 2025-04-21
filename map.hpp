#pragma once
#include <iostream>
#include <sstream>
#include <set>
#include <SDL3/SDL.h>
#include <glm/glm.hpp>
#include <vector>
#include <fstream>
#include "globals.hpp"
class Map{
    private:
        std::string buffer;
        SDL_FRect wall;
        std::fstream mapStream;
        mat::vector2f cellsize;
        std::vector<SDL_FRect> map;
        mat::vector2i pacman_pos;
        mat::vector2i blue_pos;
        mat::vector2i red_pos;
        mat::vector2i pink_pos;
        mat::vector2i orange_pos;

    public:
        Map(std::string mapName) noexcept;
        void drawMap(SDL_Renderer* renderer) noexcept;
        std::vector<SDL_FRect> getMap() const;
        inline mat::vector2i getPacman() const;
        inline mat::vector2i getBlueGhost() const;
        inline mat::vector2i getRedGhost() const;
        inline mat::vector2i getPinkGhost() const;
        inline mat::vector2i getOrangeGhost() const;
        //TODO return entity positions
};
