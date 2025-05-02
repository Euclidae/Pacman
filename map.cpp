#include "map.hpp"
#include "globals.hpp"
#include <SDL3/SDL_oldnames.h>



Map::Map(std::string mapName) noexcept{
    cellsize.x = (float)SCREEN_WIDTH/COLUMNS;//19 columns
    cellsize.y = (float)SCREEN_HEIGHT/ROWS;

    wall = {0,0,cellsize.x,cellsize.y};
    mapStream.open(mapName);

    while(std::getline(mapStream,buffer)){
       map_contents += (buffer + '\n');
       map_contents_2.push_back(std::vector<std::string>{buffer});

       for(int i = 0; i < buffer.length(); ++i){
           if(buffer[i] == 'P'){
               pacman_pos.x = x_offset;
               pacman_pos.y = y_offset;
           }

           else if(buffer[i] == 'r'){
               red_pos.x = x_offset;
               red_pos.y = y_offset;
               std::cout << "red x : " << x_offset << "\nred y : " << y_offset << '\n';
           }
           else if(buffer[i] == 'b'){
                   blue_pos.x = x_offset;
                   blue_pos.y = y_offset;
               }


           else if(buffer[i] == 'o'){
                   orange_pos.x = x_offset;
                   orange_pos.y = y_offset;
               }

           else if(buffer[i] == 'p'){
               pink_pos.x = x_offset;
               pink_pos.y = y_offset;
           }else{
               SDL_Point point;
               point.x = x_offset - (CELL_SIZE/2);
               point.y = y_offset - (CELL_SIZE/2);
               pellets.push_back(point);

           }
           x_offset += cellsize.x;
       }
       x_offset = 0;
       y_offset += (SCREEN_HEIGHT/ROWS);
    }
    y_offset = 0;
}

void Map::drawMap(SDL_Renderer* renderer) noexcept{

    std::stringstream map_sstream(map_contents);

    while(std::getline(map_sstream, buffer)){
        for(int i = 0; i < buffer.length(); ++i){
            if(buffer[i] == 'X'){
                wall = {static_cast<float>(x_offset), static_cast<float>(y_offset), static_cast<float>(cellsize.x), static_cast<float>(cellsize.y)};
                SDL_SetRenderDrawColor(renderer,122,213,234,255);
                SDL_RenderFillRect(renderer,&wall);
                if(count < 1)
                    map.push_back(wall);
            }
            else {

            }
            x_offset += cellsize.x;
        }
        x_offset = 0;
        y_offset += cellsize.y;
    }
    count++;
    y_offset = 0;

}

std::vector<SDL_FRect> Map::getMap() const{
    return map;
}


mat::vector2f& Map::getPacman() {return pacman_pos;}
mat::vector2f& Map::getBlueGhost() {return blue_pos;}
mat::vector2f& Map::getRedGhost() {return red_pos;}
mat::vector2f& Map::getPinkGhost() {return pink_pos;}
mat::vector2f& Map::getOrangeGhost() {return orange_pos;}
void Map::getRedGhostX(mat::vector2f& variant){variant = red_pos;}
        //TODO return entity positions

bool Map::isWallAt(float x, float y){
    for(auto& wall : map){
            if(wall.x <= x && x <= wall.x + wall.w && wall.y <= y && y <= wall.y + wall.h)
                return true;
        }
    return false;
}

bool Map::isWallAt(SDL_FRect& rect){
    for(auto& wall : map){
        if(SDL_HasRectIntersectionFloat(&wall,&rect))
            return true;
    }
    return false;
}

std::vector<SDL_Point>& Map::get_pellets(){
    return pellets;
}
