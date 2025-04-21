#pragma once
#include "globals.hpp"
#include <SDL3_image/SDL_image.h>
class Animation{
    private:
      std::string filename;
      mat::vector2i clip_size;
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
  

      Animation(std::string file, SDL_Renderer* rend, mat::vector2i c_s, mat::vector2f pos);
      void move(mat::vector2f vec);
      void move(mat::vector2i vec);
      void change_sprite(bool trigger);
      void draw_entity(SDL_FRect& dst);
      SDL_FRect& get_entity(){
          return dst;
      }
      ~Animation();

};
