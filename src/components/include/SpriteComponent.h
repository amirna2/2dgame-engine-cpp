#ifndef SPRITE_COMPONENT_H
#define SPRITE_COMPONENT_H

#include "../../include/Animation.h"
#include "../../include/AssetManager.h"
#include "../../include/TextureManager.h"
#include "TransformComponent.h"
#include <SDL2/SDL.h>

using namespace std;

class SpriteComponent : public Component {
private:
   TransformComponent* transform;
   SDL_Texture* texture;
   SDL_Rect sourceRectangle;
   SDL_Rect destRectangle;

   bool isAnimated;
   int numFrames;
   int animationSpeed;
   bool isFixed;
   std::map<std::string, Animation> animations;
   std::string currentAnimationName;
   unsigned int animationIndex = 0;

public:
   SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

   SpriteComponent(string assetTextureId);
   SpriteComponent(string assetTextureId, bool isFixed);

   SpriteComponent(string id, int numFrames, int animationSpeed,
                   bool hasDirections, bool isFixed);

   void play(string animationName);

   void setTexture(string assetTextureId);

   void initialize() override;

   void update(float deltaTime) override;

   void render() override;
};

#endif