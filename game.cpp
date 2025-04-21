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
                case SDL_SCANCODE_RIGHT:
                    //TODO
                
                case SDL_SCANCODE_UP:
                    //TODO
                
                case SDL_SCANCODE_DOWN:
                    //TODO
                
                case SDL_SCANCODE_ESCAPE:
                    isRunning = false;
                    std::cout << "Game instance killed\n";
                default:
                    break;
            }

        }
    }
}

void Game::update(float dt){
    //TODO    
    SDL_Delay(FRAME_TIME);
}

void Game::draw(){
    //TODO
    SDL_SetRenderDrawColor(renderer,02,25,25,255);
    SDL_RenderClear(renderer);

    map.drawMap(renderer);
    SDL_SetRenderDrawColor(renderer,0, 219,219,255);
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
  }

}

Game::~Game(){
    SDL_DestroyRenderer(renderer); 
    SDL_DestroyWindow(window);
    renderer = nullptr;
    window = nullptr;
}
