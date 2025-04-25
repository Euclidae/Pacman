#include "animation.hpp"
#include "globals.hpp"
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_timer.h>
#include <SDL3_image/SDL_image.h>
#include <iostream>

Animation::Animation(std::string file, SDL_Renderer* rend, mat::vector2f c_s, mat::vector2f pos){
    filename = file;
    renderer = rend;
    clip_size = c_s;
    ent_position = pos;
    clip.x = 0.0f;
    clip.y = 0.0f;
    clip.w = clip_size.x; //32
    clip.h = clip_size.y; //31

}

void Animation::animate(float time){
//TODO figure out what the hell I want to do with time.
    if(floor(time/FPS) == 2){
        clip.x += 32;
    }else{
        clip.x = 0;
    }
}
void Animation::change_sprite(Direction dir){
    if(dir == Direction::RIGHT){
        clip.y = 0;
    }else if(dir == Direction::LEFT){
        clip.y = 32;
    }else if(dir == Direction::UP){
        clip.y = 64;
    }else{
        clip.y = 96;
    }

    //int time = 0;
    //if(trigger){
    //   if(clip.x > (4*clip_offset)){
    //        clip.x = 0;
    //        return;
    //   }
    //    clip.x += clip_offset;
    //}
}


void Animation::draw_entity(SDL_FRect& dst){
    ent_texture = IMG_LoadTexture(renderer, filename.c_str());
    SDL_RenderTexture(renderer,ent_texture,&clip,&dst);
}

Animation::~Animation(){
    SDL_DestroyTexture(ent_texture);
    SDL_DestroySurface(ent_surface);
}
