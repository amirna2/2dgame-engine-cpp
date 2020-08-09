#include "./include/Game.h"
#include "./components/include/KeyboardControlComponent.h"
#include "./components/include/SpriteComponent.h"
#include "./components/include/TransformComponent.h"
#include <iostream>

using namespace std;

Game* Game::instance = 0;

Game* Game::getInstance() {
   if (instance == 0) {
      instance = new Game();
   }
   return instance;
}

Game::Game() { this->running = false; }

Game::~Game() {
   delete assetManager;
   delete entityManager;
   delete map;
}

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
   entityManager = new EntityManager();
   assetManager = new AssetManager(entityManager);

   event = SDL_Event();

   loadLevel(0);

   running = true;
}

void Game::handleCameraMovement() {
   TransformComponent* mainPlayerTransform =
       player->getComponent<TransformComponent>();

   camera.x = mainPlayerTransform->getPosition().x - (WINDOW_WIDTH / 2);
   camera.y = mainPlayerTransform->getPosition().y - (WINDOW_HEIGHT / 2);

   camera.x = camera.x < 0 ? 0 : camera.x;
   camera.y = camera.y < 0 ? 0 : camera.y;
   camera.x = camera.x > camera.w ? camera.w : camera.x;
   camera.y = camera.y > camera.h ? camera.h : camera.y;
}

void Game::loadLevel(int level) {
   EntityManager* manager = getEntityManger();

   assetManager->addTexture(
       "tank-image", string("./assets/images/tank-big-right.png").c_str());

   assetManager->addTexture(
       "chopper-image",
       string("./assets/images/chopper-spritesheet.png").c_str());

   assetManager->addTexture("radar-image",
                            string("./assets/images/radar.png").c_str());

   assetManager->addTexture("jungle-tiletexture",
                            string("./assets/tilemaps/jungle.png").c_str());

   map = new Map("jungle-tiletexture", 2, 32);
   map->loadMap("./assets/tilemaps/jungle.map", 25, 20);

   player = &(manager->addEntity("chopper", PLAYER_LAYER));
   player->addComponent<TransformComponent>(240, 106, 0, 0, 32, 32, 1);
   player->addComponent<SpriteComponent>("chopper-image", 2, 90, true, false);
   player->addComponent<KeyboardControlComponent>("up", "right", "down", "left",
                                                  "space");

   Entity& tankEntity(manager->addEntity("tank", ENEMY_LAYER));

   tankEntity.addComponent<TransformComponent>(0, 0, 20, 20, 32, 32, 1);
   tankEntity.addComponent<SpriteComponent>("tank-image");

   Entity& radarEntity(manager->addEntity("Radar", UI_LAYER));
   radarEntity.addComponent<TransformComponent>(720, 15, 0, 0, 64, 64, 1);
   radarEntity.addComponent<SpriteComponent>("radar-image", 8, 150, false,
                                             true);
   // manager->listAllEntities();
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
   entityManager->update(deltaTime);
   handleCameraMovement();
}

void Game::render() {
   // we draw in the back buffer after clearing it
   SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
   SDL_RenderClear(renderer);

   if (entityManager->hasNoEntities()) {
      return;
   }
   entityManager->render();

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
EntityManager* Game::getEntityManger() { return entityManager; }

SDL_Event Game::getEvent() { return event; }