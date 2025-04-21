#include "map.hpp"
#include "globals.hpp"

Map::Map(std::string mapName) noexcept{
    cellsize.x = SCREEN_WIDTH/COLUMNS;//19 columns
    cellsize.y = SCREEN_HEIGHT/ROWS;

    wall = {0,0,cellsize.x,cellsize.y};
    mapStream.open(mapName);
}

void Map::drawMap(SDL_Renderer* renderer) noexcept{
    int x_offset = 0, y_offset = 0;
    mapStream.clear();
    mapStream.seekg(0);

    while(std::getline(mapStream,buffer)){
       std::cout << buffer << std::endl;
       for(int i = 0; i < buffer.size(); ++i){
          if(buffer[i] == 'X'){
              wall = {static_cast<float>(x_offset), static_cast<float>(y_offset), static_cast<float>(cellsize.x), static_cast<float>(cellsize.y)};
              SDL_SetRenderDrawColor(renderer,122,213,234,255);
              SDL_RenderFillRect(renderer,&wall);
          }
          else if(buffer[i] == 'P'){
              pacman_pos.x = x_offset;
              pacman_pos.y = y_offset;
          }


          else if(buffer[i] == 'r'){
              red_pos.x = x_offset;
              red_pos.y = y_offset;
          }


          else if(buffer[i] == 'b'){
              blue_pos.x = x_offset;
              blue_pos.y = y_offset;
          }


          else if(buffer[i] == 'o'){
              orange_pos.x = x_offset;
              orange_pos.y = y_offset;
          }

          else if(buffer[i] = 'p'){
              pink_pos.x = x_offset;
              pink_pos.y = y_offset;
          }
          x_offset += cellsize.x;
       }
       x_offset = 0;
       y_offset += cellsize.y;
    }

}

std::vector<SDL_FRect> Map::getMap() const{
    return map;
}


inline mat::vector2i Map::getPacman() const{return pacman_pos;}
inline mat::vector2i Map::getBlueGhost() const{return blue_pos;}
inline mat::vector2i Map::getRedGhost() const{return red_pos;}
inline mat::vector2i Map::getPinkGhost() const{return pink_pos;}
inline mat::vector2i Map::getOrangeGhost() const{return orange_pos;}
        //TODO return entity positions
