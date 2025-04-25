#pragma once
#include "globals.hpp"
#include <SDL3/SDL_image.h>
class Animation{
    private:
      std::string filename;
      mat::vector2f clip_size;
      mat::vector2i dst_size;
      mat::vector2i movement;
      mat::vector2f ent_position;
      uint64_t counter;
      SDL_Renderer* renderer;
      SDL_Surface* ent_surface = nullptr;
      SDL_Texture* ent_texture = nullptr;
      SDL_FRect clip;
      float clip_offset;

    public:

      Animation() = default;
      Animation(std::string file, SDL_Renderer* rend, mat::vector2f c_s, mat::vector2f pos);
      void move(mat::vector2f vec);
      void move(mat::vector2i vec);
      void animate(float time);
      void change_sprite(Direction dir);
      void draw_entity(SDL_FRect& dst);
      SDL_FRect& get_entity(){
      }
      ~Animation();

};
