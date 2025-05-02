#include "game.hpp"
#include "globals.hpp"

Game::Game(const char* title,int x_size, int y_size): screen_width(x_size), screen_height(y_size), map("map.txt"){
    window = SDL_CreateWindow(title,SCREEN_WIDTH,SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);

    if(window == nullptr){
        std::cerr << "SDL Failed to Create Window: " << SDL_GetError();
        return;
    }

    renderer = SDL_CreateRenderer(window,nullptr);

    if(renderer == nullptr){
        std::cerr << "SDL Failed to Create Renderer: " << SDL_GetError();
        SDL_DestroyWindow(window);
        window = nullptr;
        return;
    }
    isRunning = true;
    r_ghost = Ghost("pacman sprites/red sprites.png",renderer,map.getRedGhost(),mat::vector2f{32.0,32.0}, Direction::UP,std::string{"Blinky"});
    b_ghost = Ghost("pacman sprites/blue sprites.png",renderer,map.getBlueGhost(),mat::vector2f{32.0,32.0}, Direction::LEFT,std::string{"Inky"});
    p_ghost = Ghost("pacman sprites/pink sprites.png",renderer,map.getPinkGhost(),mat::vector2f{32.0,32.0}, Direction::DOWN,std::string{"Pinky"});
    o_ghost = Ghost("pacman sprites/orange sprites.png",renderer,map.getOrangeGhost(),mat::vector2f{32.0,32.0}, Direction::RIGHT,std::string{"Clyde"});
    pacman = Pacman("pacman sprites/pacman sprites.png", RIGHT, map.getPacman(), mat::vector2f{32.0f,32.5f}, renderer, mat::vector2f{32.0f,32.0f});
}

void Game::processInput(){
    while(SDL_PollEvent(&event)){
        if(event.type == SDL_EVENT_QUIT){
            isRunning = false;
            std::cout << "Game instance terminated\n";
        }

        if(event.type == SDL_EVENT_KEY_DOWN){
            switch(event.key.scancode){
                case SDL_SCANCODE_LEFT:
                    //TODO
                    pacman.change_direction(Direction::LEFT);
                    break;
                case SDL_SCANCODE_RIGHT:
                    //TODO
                    pacman.change_direction(Direction::RIGHT);
                    break;

                case SDL_SCANCODE_UP:
                    //TODO
                    pacman.change_direction(Direction::UP);
                    break;

                case SDL_SCANCODE_DOWN:
                    //TODO
                    pacman.change_direction(Direction::DOWN);
                    break;

                case SDL_SCANCODE_ESCAPE:
                    isRunning = false;
                    std::cout << "Game instance killed\n";
                    break;
                default:
                    break;
            }

        }
    }
}

void Game::update(float dt){
    //TODO
    count++; //counts frame. change animation every FPS/2;
    r_ghost.update(dt, map);
    pacman.update(dt,map);
    b_ghost.update(dt, map);
    p_ghost.update(dt, map);
    o_ghost.update(dt, map);
    if(count == FPS){
        count = 0;
    }
    SDL_Delay(FRAME_TIME);

}

void Game::draw(){
    //TODO
    SDL_SetRenderDrawColor(renderer,02,25,25,255);
    SDL_RenderClear(renderer);
    map.drawMap(renderer);
    map.draw_pellets(renderer);
    SDL_SetRenderDrawColor(renderer,0, 219,219,255);
    r_ghost.draw(count);
    b_ghost.draw(count);
    p_ghost.draw(count);
    o_ghost.draw(count);
    pacman.draw(count);
    SDL_RenderPresent(renderer);
}

void Game::loop(){
  float previousTime = static_cast<float>(SDL_GetTicks()/1000.0f);
  float currentTime = 0.0;
  float deltaTime = 0.0;

  while(isRunning){
      currentTime = (static_cast<float>(SDL_GetTicks())/1000.0f);
      deltaTime = currentTime - previousTime;
      processInput();
      update(deltaTime);
      draw();
      previousTime = currentTime;
      SDL_Delay(FRAME_TIME);
  }

}

Game::~Game(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    renderer = nullptr;
    window = nullptr;
    std::cout << "\033[033mThe game is over, thank you for your patronage\033[00m\n";
}
