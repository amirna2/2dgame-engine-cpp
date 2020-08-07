#ifndef GAME_H
#define GAME_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

class AssetManager;

class Game {
private:
   static Game* instance;
   Game();
   ~Game();

   bool running;
   SDL_Window* window;
   int ticksLastFrame;
   SDL_Renderer* renderer;
   AssetManager* assetManager;

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
   AssetManager* getAssetManger();
};

#endif
