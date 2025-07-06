#include "game.hpp"
#include "globals.hpp"
#include <SDL3/SDL_init.h>
#include <SDL3_ttf/SDL_ttf.h>
// TODO add text

Game::Game(const char* title,int x_size, int y_size, char* map_name): screen_width(x_size), screen_height(y_size), map(map_name){
    window = SDL_CreateWindow(title,SCREEN_WIDTH,SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);
    TTF_Init();

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
    game_state = MENU;
    lives = 3;
    score = 0;
    show_menu = true;
    r_ghost = Ghost("assets/pacman sprites/red sprites.png",renderer,map.getRedGhost(),mat::vector2f{32.0,32.0}, Direction::UP,std::string{"Blinky"});
    b_ghost = Ghost("assets/pacman sprites/blue sprites.png",renderer,map.getBlueGhost(),mat::vector2f{32.0,32.0}, Direction::LEFT,std::string{"Inky"});
    p_ghost = Ghost("assets/pacman sprites/pink sprites.png",renderer,map.getPinkGhost(),mat::vector2f{32.0,32.0}, Direction::DOWN,std::string{"Pinky"});
    o_ghost = Ghost("assets/pacman sprites/orange sprites.png",renderer,map.getOrangeGhost(),mat::vector2f{32.0,32.0}, Direction::RIGHT,std::string{"Clyde"});
    pacman = Pacman("assets/pacman sprites/pacman sprites.png", RIGHT, map.getPacman(), mat::vector2f{32.0f,32.5f}, renderer, mat::vector2f{32.0f,32.0f});
    pacman.set_lives(lives);
}

void Game::processInput(){
    while(SDL_PollEvent(&event)){
        if(event.type == SDL_EVENT_QUIT){
            isRunning = false;
            std::cout << "Game instance terminated\n";
        }

        if(event.type == SDL_EVENT_KEY_DOWN){
            if(game_state == MENU){
                switch(event.key.scancode){
                    case SDL_SCANCODE_RETURN:
                        game_state = PLAYING;
                        show_menu = false;
                        break;
                    case SDL_SCANCODE_ESCAPE:
                        isRunning = false;
                        std::cout << "Game instance killed\n";
                        break;
                    default:
                        break;
                }
            } else if(game_state == PLAYING){
                switch(event.key.scancode){
                    case SDL_SCANCODE_LEFT:
                        //TODO
                        pacman.change_direction(Direction::LEFT, map);
                        break;
                    case SDL_SCANCODE_RIGHT:
                        //TODO
                        pacman.change_direction(Direction::RIGHT, map);
                        break;

                    case SDL_SCANCODE_UP:
                        //TODO
                        pacman.change_direction(Direction::UP, map);
                        break;

                    case SDL_SCANCODE_DOWN:
                        //TODO
                        pacman.change_direction(Direction::DOWN, map);
                        break;

                    case SDL_SCANCODE_ESCAPE:
                        isRunning = false;
                        std::cout << "Game instance killed\n";
                        break;
                    default:
                        break;
                }
            } else if(game_state == GAME_OVER){
                switch(event.key.scancode){
                    case SDL_SCANCODE_RETURN:
                        resetGame();
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
}

void Game::update(float dt){
    if(game_state == PLAYING){
        //TODO
        count++; //counts frame. change animation every FPS/2;
        pacman.update(dt,map,score);
        r_ghost.update(dt, map,pacman);
        b_ghost.update(dt, map,pacman);
        p_ghost.update(dt, map,pacman);
        o_ghost.update(dt, map,pacman);

        if(!pacman.is_pacman_ok()){
            lives = pacman.get_lives();
            if(lives <= 0){
                game_state = GAME_OVER;
                std::cout << "\033[033mGame Over! Final Score: " << score << "\n";
            } else {
                // Reset pacman position and restore alive status
                pacman.reset_position(map.getPacman());
                pacman.restore_alive_status();
                pacman.set_lives(lives);
                std::cout << "\033[033mPacman died! Lives remaining: " << lives << "\n";
            }
        }

        if(count == FPS){
            count = 0;
        }
    }
    SDL_Delay(FRAME_TIME);
}

void Game::draw(){
    //TODO
    SDL_SetRenderDrawColor(renderer,02,25,25,255);
    SDL_RenderClear(renderer);

    if(game_state == MENU){
        drawMenu();
    } else if(game_state == PLAYING){
        map.drawMap(renderer);
        map.draw_pellets(renderer);
        map.draw_power_pellets(renderer);
        pacman.draw(count);
        r_ghost.draw(count);
        b_ghost.draw(count);
        p_ghost.draw(count);
        o_ghost.draw(count);
        drawHUD();
    } else if(game_state == GAME_OVER){
        drawGameOver();
    }

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

void Game::drawMenu(){
    // Load font once for all text
    TTF_Font* font = TTF_OpenFont("assets/fonts/arial.ttf", 24);
    if (!font) {
        printf("Font loading failed: %s\n", SDL_GetError());
        return;
    }

    // Draw title "Play Pacman"
    char* menu_title = "Play Pacman";
    SDL_Color title_color = {255, 255, 0, 255}; // Yellow text
    SDL_Surface* title_surface = TTF_RenderText_Solid(font, menu_title, strlen(menu_title), title_color);
    if (title_surface) {
        SDL_Texture* title_texture = SDL_CreateTextureFromSurface(renderer, title_surface);
        SDL_FRect title_rect = {SCREEN_WIDTH/2 - 100, 150, 200, 50};
        SDL_RenderTexture(renderer, title_texture, NULL, &title_rect);
        SDL_DestroyTexture(title_texture);
        SDL_DestroySurface(title_surface);
    }

    // Draw menu instructions
    char* instruction1 = "Press ENTER to Start";
    SDL_Color instruction_color = {255, 255, 255, 255}; // White text
    SDL_Surface* instruction1_surface = TTF_RenderText_Solid(font, instruction1, strlen(instruction1), instruction_color);
    if (instruction1_surface) {
        SDL_Texture* instruction1_texture = SDL_CreateTextureFromSurface(renderer, instruction1_surface);
        SDL_FRect instruction1_rect = {SCREEN_WIDTH/2 - 150, 300, 300, 30};
        SDL_RenderTexture(renderer, instruction1_texture, NULL, &instruction1_rect);
        SDL_DestroyTexture(instruction1_texture);
        SDL_DestroySurface(instruction1_surface);
    }

    char* instruction2 = "ESC to Quit";
    SDL_Surface* instruction2_surface = TTF_RenderText_Solid(font, instruction2, strlen(instruction2), instruction_color);
    if (instruction2_surface) {
        SDL_Texture* instruction2_texture = SDL_CreateTextureFromSurface(renderer, instruction2_surface);
        SDL_FRect instruction2_rect = {SCREEN_WIDTH/2 - 100, 350, 200, 30};
        SDL_RenderTexture(renderer, instruction2_texture, NULL, &instruction2_rect);
        SDL_DestroyTexture(instruction2_texture);
        SDL_DestroySurface(instruction2_surface);
    }

    TTF_CloseFont(font);
}

void Game::drawGameOver(){
    // Load font
    TTF_Font* font = TTF_OpenFont("assets/fonts/arial.ttf", 32);
    if (!font) {
        printf("Font loading failed: %s\n", SDL_GetError());
        return;
    }

    // Draw "GAME OVER" text
    char* game_over_text = "GAME OVER";
    SDL_Color game_over_color = {255, 0, 0, 255}; // Red text
    SDL_Surface* game_over_surface = TTF_RenderText_Solid(font, game_over_text, strlen(game_over_text), game_over_color);
    if (game_over_surface) {
        SDL_Texture* game_over_texture = SDL_CreateTextureFromSurface(renderer, game_over_surface);
        SDL_FRect game_over_rect = {SCREEN_WIDTH/2 - 100, 200, 200, 50};
        SDL_RenderTexture(renderer, game_over_texture, NULL, &game_over_rect);
        SDL_DestroyTexture(game_over_texture);
        SDL_DestroySurface(game_over_surface);
    }

    // Draw restart instruction
    char* restart_text = "Press ENTER to Restart";
    SDL_Color restart_color = {255, 255, 255, 255}; // White text
    SDL_Surface* restart_surface = TTF_RenderText_Solid(font, restart_text, strlen(restart_text), restart_color);
    if (restart_surface) {
        SDL_Texture* restart_texture = SDL_CreateTextureFromSurface(renderer, restart_surface);
        SDL_FRect restart_rect = {SCREEN_WIDTH/2 - 120, 300, 240, 30};
        SDL_RenderTexture(renderer, restart_texture, NULL, &restart_rect);
        SDL_DestroyTexture(restart_texture);
        SDL_DestroySurface(restart_surface);
    }

    TTF_CloseFont(font);
}

void Game::drawHUD(){
    // Load font for HUD text
    TTF_Font* font = TTF_OpenFont("assets/fonts/arial.ttf", 18);
    if (!font) {
        printf("Font loading failed: %s\n", SDL_GetError());
        return;
    }

    // Draw lives counter with text
    char lives_text[32];
    snprintf(lives_text, sizeof(lives_text), "Lives: %d", pacman.get_lives());
    SDL_Color lives_color = {255, 255, 255, 255}; // White text
    SDL_Surface* lives_surface = TTF_RenderText_Solid(font, lives_text, strlen(lives_text), lives_color);
    if (lives_surface) {
        SDL_Texture* lives_texture = SDL_CreateTextureFromSurface(renderer, lives_surface);
        SDL_FRect lives_rect = {10, 10, 100, 20};
        SDL_RenderTexture(renderer, lives_texture, NULL, &lives_rect);
        SDL_DestroyTexture(lives_texture);
        SDL_DestroySurface(lives_surface);
    }

    // Draw score with text
    char score_text[32];
    snprintf(score_text, sizeof(score_text), "Score: %d", score);
    SDL_Color score_color = {255, 255, 0, 255};
    SDL_Surface* score_surface = TTF_RenderText_Solid(font, score_text, strlen(score_text), score_color);
    if (score_surface) {
        SDL_Texture* score_texture = SDL_CreateTextureFromSurface(renderer, score_surface);
        SDL_FRect score_rect = {SCREEN_WIDTH - 150, 10, 140, 20};
        SDL_RenderTexture(renderer, score_texture, NULL, &score_rect);
        SDL_DestroyTexture(score_texture);
        SDL_DestroySurface(score_surface);
    }

    TTF_CloseFont(font);
}

void Game::resetGame(){
    game_state = MENU;
    show_menu = true;
    lives = 3;
    score = 0;
    pacman.set_lives(lives);
    pacman.reset_position(map.getPacman());
    pacman.restore_alive_status();
    // Reset ghosts to their starting positions
    r_ghost = Ghost("pacman sprites/red sprites.png",renderer,map.getRedGhost(),mat::vector2f{32.0,32.0}, Direction::UP,std::string{"Blinky"});
    b_ghost = Ghost("pacman sprites/blue sprites.png",renderer,map.getBlueGhost(),mat::vector2f{32.0,32.0}, Direction::LEFT,std::string{"Inky"});
    p_ghost = Ghost("pacman sprites/pink sprites.png",renderer,map.getPinkGhost(),mat::vector2f{32.0,32.0}, Direction::DOWN,std::string{"Pinky"});
    o_ghost = Ghost("pacman sprites/orange sprites.png",renderer,map.getOrangeGhost(),mat::vector2f{32.0,32.0}, Direction::RIGHT,std::string{"Clyde"});
}

Game::~Game(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    renderer = nullptr;
    window = nullptr;
    TTF_Quit();
    SDL_Quit();
    std::cout << "\033[033mThe game is over, thank you for your patronage\033[00m\n";
}
