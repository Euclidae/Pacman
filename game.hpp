#pragma once
#define SDL_MAIN_HANDLED

#include <SDL3/SDL.h>
#include <iostream>
#include "globals.hpp"
#include "map.hpp"
class Game{
    private:
        int screen_width, screen_height = 0;
        SDL_Renderer* renderer = nullptr;
        SDL_Window* window = nullptr;
        SDL_Event event;
        bool isRunning;
        Map map;

    public:
        explicit Game(const char* title,int x_size, int y_size);
        void processInput();
        void update(float dt);
        void draw();
        void loop();
        ~Game();
};
