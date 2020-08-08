#include "./include/TileComponent.h"

TileComponent::TileComponent(int sourceRectX, int sourceRectY, int x, int y,
                             int tileSize, int tileScale,
                             std::string assetTextureId) {
   texture = Game::getInstance()->getAssetManger()->getTexture(assetTextureId);

   sourceRectangle.x = sourceRectX;
   sourceRectangle.y = sourceRectY;
   sourceRectangle.w = tileSize;
   sourceRectangle.h = tileSize;

   destRectangle.x = x;
   destRectangle.y = y;
   destRectangle.w = tileSize * tileScale;
   destRectangle.h = tileSize * tileScale;

   position.x = x;
   position.y = y;
}

TileComponent::~TileComponent() { SDL_DestroyTexture(texture); }

void TileComponent::update(float deltaTime) {
   // destRectangle.x = position.x - Game::camera.x;
   // destRectangle.y = position.y - Game::camera.y;

   destRectangle.x = position.x;
   destRectangle.y = position.y;
}

void TileComponent::render() {
   TextureManager::draw(texture, sourceRectangle, destRectangle, SDL_FLIP_NONE);
}