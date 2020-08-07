#include "./include/SpriteComponent.h"
#include "../include/Game.h"

SpriteComponent::SpriteComponent(const char* filePath) { setTexture(filePath); }

void SpriteComponent::setTexture(std::string assetTextureId) {
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

   destRectangle.x = (int)tPos.x;
   destRectangle.y = (int)tPos.y;
   destRectangle.w = tWidth * tScale;
   destRectangle.h = tHeight * tScale;
}

void SpriteComponent::render() {
   TextureManager::draw(texture, sourceRectangle, destRectangle, spriteFlip);
}