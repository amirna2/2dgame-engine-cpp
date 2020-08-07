#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "../lib/glm/glm.hpp"
#include "./components/include/KeyboardControlComponent.h"
#include "./components/include/SpriteComponent.h"
#include "./components/include/TransformComponent.h"
#include "./include/AssetManager.h"
#include "./include/Constants.h"
#include "./include/EntityManager.h"
#include "./include/Game.h"

EntityManager manager;

Game* Game::instance = 0;

Game* Game::getInstance() {
   if (instance == 0) {
      instance = new Game();
   }
   return instance;
}

Game::Game() { this->running = false; }

Game::~Game() {}

void Game::initialize(int width, int height) {
   if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
      std::cerr << "Error initializing SDL" << std::endl;
      return;
   }

   window =
       SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                        width, height, SDL_WINDOW_BORDERLESS);
   if (!window) {
      std::cerr << "Error creating SDL window" << std::endl;
      return;
   }

   renderer = SDL_CreateRenderer(window, -1, 0);
   if (!renderer) {
      std::cerr << "Error creating SDL renderer" << std::endl;
      return;
   }

   assetManager = new AssetManager(&manager);

   event = SDL_Event();

   loadLevel(0);

   running = true;
}

void Game::loadLevel(int level) {
   /* Start including new assets to the assetmanager list */
   assetManager->addTexture(
       "tank-image", std::string("./assets/images/tank-big-right.png").c_str());
   assetManager->addTexture(
       "chopper-image",
       std::string("./assets/images/chopper-spritesheet.png").c_str());
   assetManager->addTexture("radar-image",
                            std::string("./assets/images/radar.png").c_str());

   /* Start including entities and also components to them */
   Entity& chopperEntity(manager.addEntity("chopper"));
   chopperEntity.addComponent<TransformComponent>(240, 106, 0, 0, 32, 32, 1);
   chopperEntity.addComponent<SpriteComponent>("chopper-image", 2, 90, true,
                                               false);

   chopperEntity.addComponent<KeyboardControlComponent>("up", "right", "down",
                                                        "left", "space");

   Entity& tankEntity(manager.addEntity("tank"));
   tankEntity.addComponent<TransformComponent>(0, 0, 20, 20, 32, 32, 1);
   tankEntity.addComponent<SpriteComponent>("tank-image");

   Entity& radarEntity(manager.addEntity("Radar"));
   radarEntity.addComponent<TransformComponent>(720, 15, 0, 0, 64, 64, 1);
   radarEntity.addComponent<SpriteComponent>("radar-image", 8, 150, false,
                                             true);
}

void Game::update() {
   // delay update until we have reached our frame update target time
   int timeToWaitMs = FRAME_TARGET_TIME_MS - ticksLastFrame;
   if (timeToWaitMs > 0 && timeToWaitMs < FRAME_TARGET_TIME_MS) {
      SDL_Delay(timeToWaitMs);
   }

   float deltaTime = SDL_GetTicks() - ticksLastFrame / 1000;
   deltaTime = (deltaTime > 0.05f) ? 0.05f : deltaTime;

   ticksLastFrame = SDL_GetTicks();

   // update all our entities
   manager.update(deltaTime);
}

void Game::render() {
   // we draw in the back buffer after clearing it
   SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
   SDL_RenderClear(renderer);

   if (manager.hasNoEntities()) {
      return;
   }
   manager.render();

   // Now we flip the buffers
   SDL_RenderPresent(renderer);
}

void Game::destroy() {
   SDL_DestroyRenderer(renderer);
   SDL_DestroyWindow(window);
   SDL_Quit();

   delete instance;
   instance = 0;
}

void Game::processInput() {
   SDL_PollEvent(&event);
   switch (event.type) {
      case SDL_QUIT: {
         running = false;
         break;
      }
      case SDL_KEYDOWN: {
         if (event.key.keysym.sym == SDLK_ESCAPE) {
            running = false;
         }
      }
      default: {
         break;
      }
   }
}

bool Game::isRunning() const { return running; }

SDL_Renderer* Game::getRenderer() { return renderer; }

AssetManager* Game::getAssetManger() { return assetManager; }

SDL_Event Game::getEvent() { return event; }