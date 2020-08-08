#ifndef TILECOMPONENT_H
#define TILECOMPONENT_H

#include "../../include/AssetManager.h"
#include "../../include/EntityManager.h"
#include "../../lib/glm/glm.hpp"
#include "./Component.h"
#include <SDL2/SDL.h>

class TileComponent : public Component {
public:
   SDL_Texture* texture;
   SDL_Rect sourceRectangle;
   SDL_Rect destRectangle;
   glm::vec2 position;

   TileComponent(int sourceRectX, int sourceRectY, int x, int y, int tileSize,
                 int tileScale, std::string assetTextureId);

   ~TileComponent();

   void update(float deltaTime) override;

   void render() override;
};

#endif
