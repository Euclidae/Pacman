#include "animation.hpp"
#include "globals.hpp"

Animation::Animation(std::string file, SDL_Renderer* rend, mat::vector2i c_s, mat::vector2f pos){
    filename = file;
    renderer = rend;
    clip_size = c_s;
    ent_position = pos;
    clip.w = clip_size.x;
    clip.h = clip_size.y;
    ent_surface = IMG_Load(file.c_str());
}


void Animation::change_sprite(bool trigger){
    int time = 0;
    if(trigger){
        if(clip.x > (4*clip_offset)){
            clip.x = 0;
            return;
        }
        clip.x += clip_offset;
    }
}


void Animation::draw_entity(SDL_FRect& dst){
    ent_texture = SDL_CreateTextureFromSurface(renderer, ent_surface);
    SDL_RenderTexture(renderer,ent_texture,&clip,&dst);
}


