#pragma once
#include <iostream>
#include <sstream>
#include <set>
#include <SDL3/SDL.h>
#include <vector>
#include <fstream>
#include "globals.hpp"
class Map{
    private:
        std::string buffer;
        std::string map_contents;
        std::vector<std::vector<std::string>> map_contents_2;
        SDL_FRect wall;
        std::fstream mapStream;
        mat::vector2f cellsize;
        std::vector<SDL_FRect> map;
        mat::vector2f pacman_pos;
        mat::vector2f blue_pos;
        mat::vector2f red_pos;
        mat::vector2f pink_pos;
        mat::vector2f orange_pos;
        int x_offset = 0, y_offset = 0;
        int count = 0;

    public:
        Map(std::string mapName) noexcept;
        void drawMap(SDL_Renderer* renderer) noexcept;
        std::vector<SDL_FRect> getMap() const;
        std::vector<std::vector<std::string>> getMapString() {return map_contents_2;};
        mat::vector2f& getPacman();
        mat::vector2f& getBlueGhost();
        mat::vector2f& getRedGhost();
        mat::vector2f& getPinkGhost();
        mat::vector2f& getOrangeGhost();

        void getRedGhostX(mat::vector2f& variant);
        //TODO return entity positions
};
