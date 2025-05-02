#ifndef GLOBALS_HPP
#define GLOBALS_HPP
#include <cmath>
#include <string>
#include <iostream>
#define SCREEN_WIDTH 608
#define SCREEN_HEIGHT 672
#define FPS 60
#define FRAME_TIME 1000/FPS
#define ROWS 21
#define COLUMNS 19
#define CELL_SIZE 32

namespace mat {
    struct vector2f {
        float x = 0.0f, y = 0.0f;

        vector2f& operator = (const vector2f& vec2){
            x = vec2.x;
            y = vec2.y;
            return *this;
        }
    };

    struct vector2i {
        int x = 0, y = 0;
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




#endif
