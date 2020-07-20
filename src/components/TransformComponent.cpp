#include "./include/TransformComponent.h"
#include "../../lib/glm/glm.hpp"
#include "../include/Game.h"
#include <SDL2/SDL.h>

TransformComponent::TransformComponent(int posX, int posY, int velX, int velY,
                                       int w, int h, int s) {
   position = glm::vec2(posX, posY);
   velocity = glm::vec2(velX, velY);
   width = w;
   height = h;
   scale = s;
}

void TransformComponent::update(float deltaTime) {
   position.x += velocity.x * deltaTime;
   position.y += velocity.y * deltaTime;
}

void TransformComponent::initialize() {}

void TransformComponent::render() {
   SDL_Rect transformRectangle = {(int)position.x, (int)position.y, width,
                                  height};
   Game* game = Game::getInstance();
   SDL_SetRenderDrawColor(game->getRenderer(), 255, 255, 255, 255);
   SDL_RenderFillRect(game->getRenderer(), &transformRectangle);
}