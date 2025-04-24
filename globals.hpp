#pragma once
#include <cmath>
#include <string>
#define SCREEN_WIDTH 608
#define SCREEN_HEIGHT 673
#define FPS 60
#define FRAME_TIME 1000/FPS
#define ROWS 21
#define COLUMNS 19

#define RED_GHOST_SPRITE "pacman sprites/red sprites"
#define BLUE_GHOST_SPRITE "pacman sprites/blue sprites"
#define ORANGE_GHOST_SPRITE "pacman sprites/orange sprites"
#define PINK_GHOST_SPRITE "pacman sprites/pink sprites"

namespace mat {
    struct vector2f {
        float x, y;

        void operator = (const vector2f& vec2){
            x = vec2.x;
            y = vec2.y;
        }
    };

    struct vector2i {
        int x, y;
    };
}

inline mat::vector2f operator * (mat::vector2f& vec1, mat::vector2f& vec2) {
    vec1 = {vec1.x * vec2.x, vec1.y * vec2.y};
    return vec1;
}

inline mat::vector2i operator * (mat::vector2i& vec1, mat::vector2i& vec2) {
    vec1 = {vec1.x * vec2.x, vec1.y * vec2.y};
    return vec1;
}

inline void operator += (mat::vector2i& vec1, mat::vector2i& vec2){
    vec1.x += vec2.x;
    vec1.y += vec2.y;
}


enum Direction{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

enum Ghost_Mode{
  FLEE,
  HUNT
};
