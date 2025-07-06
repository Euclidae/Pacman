#pragma once
#include <SDL3/SDL_oldnames.h>
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
        std::vector<SDL_Point> pellets;
        std::vector<SDL_Point> power_pellets;
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
        std::vector<SDL_Point>& get_pellets();
        std::vector<SDL_Point>& get_power_pellets();
        void getRedGhostX(mat::vector2f& variant);
        bool isWallAt(float x, float y);
        bool isWallAt(SDL_FRect& rect);
        void draw_pellets(SDL_Renderer* renderer){
            SDL_SetRenderDrawColor(renderer, 255,255,255,255);
            for(auto pellet: pellets){
                SDL_RenderPoint(renderer,pellet.x,pellet.y);
            }
        }
        void draw_power_pellets(SDL_Renderer* renderer){
            SDL_SetRenderDrawColor(renderer, 255,255,0,255);
            for(auto power_pellet: power_pellets){
                SDL_FRect big_pellet;
                big_pellet.x = power_pellet.x - 3;
                big_pellet.y = power_pellet.y - 3;
                big_pellet.w = 6;
                big_pellet.h = 6;
                SDL_RenderFillRect(renderer, &big_pellet);
            }
        }
        //TODO return entity positions
};
