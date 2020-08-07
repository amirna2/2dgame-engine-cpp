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

void TransformComponent::setVelocity(float x, float y) {
   velocity.x = x;
   velocity.y = y;
}

void TransformComponent::update(float deltaTime) {
   position.x += velocity.x * deltaTime;
   position.y += velocity.y * deltaTime;
}

void TransformComponent::initialize() {}

void TransformComponent::render() {}