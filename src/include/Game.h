#ifndef GAME_H
#define GAME_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "../../lib/glm/glm.hpp"

#include "AssetManager.h"
#include "Constants.h"
#include "EntityManager.h"
#include "Map.h"

class AssetManager;
class EntityManager;

class Map;

class Game {
private:
   static Game* instance;
   Game();
   ~Game();

   bool running;
   SDL_Window* window;
   int ticksLastFrame;
   SDL_Renderer* renderer;
   SDL_Event event;
   AssetManager* assetManager;
   EntityManager* entityManager;
   Map* map;
   SDL_Rect camera = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
   void handleCameraMovement();
   Entity* player;

public:
   static Game* getInstance();
   bool isRunning() const;
   void initialize(int width, int height);
   void loadLevel(int level);
   void processInput();
   void update();
   void render();
   void destroy();
   SDL_Renderer* getRenderer();
   SDL_Event getEvent();
   AssetManager* getAssetManger();
   EntityManager* getEntityManger();
   SDL_Rect getCamera() { return camera; }
};

#endif
