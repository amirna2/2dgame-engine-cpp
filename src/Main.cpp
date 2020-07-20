#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>

#include "./include/Constants.h"
#include "./include/Game.h"

int main(int argc, char* args[]) {
   Game* game = Game::getInstance();
   game->initialize(WINDOW_WIDTH, WINDOW_HEIGHT);

   while (game->isRunning()) {
      game->processInput();
      game->update();
      game->render();
   }

   game->destroy();

   return 0;
}
