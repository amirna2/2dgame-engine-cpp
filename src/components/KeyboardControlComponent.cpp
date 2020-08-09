#include "./include/KeyboardControlComponent.h"

using namespace std;

KeyboardControlComponent::KeyboardControlComponent() {}

KeyboardControlComponent::KeyboardControlComponent(string upKey,
                                                   string rightKey,
                                                   string downKey,
                                                   string leftKey,
                                                   string shootKey) {
   this->upKey = getSDLKeyStringCode(upKey);
   this->rightKey = getSDLKeyStringCode(rightKey);
   this->downKey = getSDLKeyStringCode(downKey);
   this->leftKey = getSDLKeyStringCode(leftKey);
   this->shootKey = getSDLKeyStringCode(shootKey);
}

string KeyboardControlComponent::getSDLKeyStringCode(string key) {
   if (key.compare("up") == 0)
      return "1073741906";
   if (key.compare("down") == 0)
      return "1073741905";
   if (key.compare("left") == 0)
      return "1073741904";
   if (key.compare("right") == 0)
      return "1073741903";
   if (key.compare("space") == 0)
      return "32";
   return to_string(static_cast<int>(key[0]));
}

void KeyboardControlComponent::initialize() {
   transform = owner->getComponent<TransformComponent>();
   sprite = owner->getComponent<SpriteComponent>();
}

void KeyboardControlComponent::update(float deltaTime) {
   if (Game::getInstance()->getEvent().type == SDL_KEYDOWN) {
      string keyCode =
          to_string(Game::getInstance()->getEvent().key.keysym.sym);
      if (keyCode.compare(upKey) == 0) {
         transform->setVelocity(0, -10);

         sprite->play("UpAnimation");
      }
      if (keyCode.compare(rightKey) == 0) {
         transform->setVelocity(10, 0);
         sprite->play("RightAnimation");
      }
      if (keyCode.compare(downKey) == 0) {
         transform->setVelocity(0, 10);
         sprite->play("DownAnimation");
      }
      if (keyCode.compare(leftKey) == 0) {
         transform->setVelocity(-10, 0);
         sprite->play("LeftAnimation");
      }
      if (keyCode.compare(shootKey) == 0) {
         // TODO:
         // Shoot projectiles when 'shoot' key is pressed
      }
   }

   if (Game::getInstance()->getEvent().type == SDL_KEYUP) {
      std::string keyCode =
          std::to_string(Game::getInstance()->getEvent().key.keysym.sym);
      if (keyCode.compare(upKey) == 0) {
         transform->setVelocityY(0);
      }
      if (keyCode.compare(rightKey) == 0) {
         transform->setVelocityX(0);
      }
      if (keyCode.compare(downKey) == 0) {
         transform->setVelocityY(0);
      }
      if (keyCode.compare(leftKey) == 0) {
         transform->setVelocityX(0);
      }
   }
}