#include "animation.hpp"
#include "globals.hpp"

Animation::Animation(std::string file, SDL_Renderer* rend, mat::vector2f c_s, mat::vector2f pos){
    filename = file;
    renderer = rend;
    clip_size = c_s;
    ent_position = pos;
    clip.w = clip_size.x; //32
    clip.h = clip_size.y; //31
    ent_surface = IMG_Load(file.c_str());
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
        clip.y += 32.0f;
    }else if(dir == Direction::UP){
        clip.y += 64.0f;
    }else{
        clip.y += 96.0f;
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
    ent_texture = SDL_CreateTextureFromSurface(renderer, ent_surface);
    SDL_RenderTexture(renderer,ent_texture,&clip,&dst);
}
