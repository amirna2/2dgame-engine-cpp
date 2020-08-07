#ifndef SPRITE_COMPONENT_H
#define SPRITE_COMPONENT_H

#include "../../include/AssetManager.h"
#include "../../include/TextureManager.h"
#include "TransformComponent.h"
#include <SDL2/SDL.h>

class SpriteComponent : public Component {
private:
   TransformComponent* transform;
   SDL_Texture* texture;
   SDL_Rect sourceRectangle;
   SDL_Rect destRectangle;

public:
   SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

   SpriteComponent(const char* filePath);

   void setTexture(std::string assetTextureId);

   void initialize() override;

   void update(float deltaTime) override;

   void render() override;
};

#endif