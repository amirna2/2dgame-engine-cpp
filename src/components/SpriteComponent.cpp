#include "./include/SpriteComponent.h"
#include "../include/Animation.h"
#include "../include/Game.h"

using namespace std;

SpriteComponent::SpriteComponent(string assetTextureId) {
   this->isAnimated = false;
   this->isFixed = false;
   setTexture(assetTextureId);
}

SpriteComponent::SpriteComponent(string assetTextureId, bool isFixed) {
   this->isAnimated = false;
   this->isFixed = isFixed;
   setTexture(assetTextureId);
}

SpriteComponent::SpriteComponent(string id, int numFrames, int animationSpeed,
                                 bool hasDirections, bool isFixed) {
   this->isAnimated = true;
   this->numFrames = numFrames;
   this->animationSpeed = animationSpeed;
   this->isFixed = isFixed;

   if (hasDirections) {
      Animation downAnimation = Animation(0, numFrames, animationSpeed);
      Animation rightAnimation = Animation(1, numFrames, animationSpeed);
      Animation leftAnimation = Animation(2, numFrames, animationSpeed);
      Animation upAnimation = Animation(3, numFrames, animationSpeed);
      animations.emplace("DownAnimation", downAnimation);
      animations.emplace("RightAnimation", rightAnimation);
      animations.emplace("LeftAnimation", leftAnimation);
      animations.emplace("UpAnimation", upAnimation);
      this->animationIndex = 0;
      this->currentAnimationName = "DownAnimation";
   } else {
      Animation singleAnimation = Animation(0, numFrames, animationSpeed);
      animations.emplace("SingleAnimation", singleAnimation);
      this->animationIndex = 0;
      this->currentAnimationName = "SingleAnimation";
   }

   play(this->currentAnimationName);

   setTexture(id);
}

void SpriteComponent::play(std::string animationName) {
   numFrames = animations[animationName].numFrames;
   animationIndex = animations[animationName].index;
   animationSpeed = animations[animationName].animationSpeed;
   currentAnimationName = animationName;
}

void SpriteComponent::setTexture(string assetTextureId) {
   texture = Game::getInstance()->getAssetManger()->getTexture(assetTextureId);
}

void SpriteComponent::initialize() {
   transform = owner->getComponent<TransformComponent>();
   sourceRectangle.x = 0;
   sourceRectangle.y = 0;
   sourceRectangle.w = transform->getWidth();
   sourceRectangle.h = transform->getHeight();
}

void SpriteComponent::update(float deltaTime) {
   glm::vec2 tPos = transform->getPosition();
   int tScale = transform->getScale();
   int tWidth = transform->getWidth();
   int tHeight = transform->getHeight();

   if (isAnimated) {
      // we go through each frame of the animation when we update
      sourceRectangle.x =
          sourceRectangle.w *
          static_cast<int>((SDL_GetTicks() / animationSpeed) % numFrames);
   }
   sourceRectangle.y = animationIndex * tHeight;

   destRectangle.x = static_cast<int>(tPos.x);
   destRectangle.y = static_cast<int>(tPos.y);
   destRectangle.w = tWidth * tScale;
   destRectangle.h = tHeight * tScale;
}

void SpriteComponent::render() {
   TextureManager::draw(texture, sourceRectangle, destRectangle, spriteFlip);
}