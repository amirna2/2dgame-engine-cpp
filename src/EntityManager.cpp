#include "./include/EntityManager.h"
#include "./include/Entity.h"

void EntityManager::clearData() {
   for (auto& entity : entities) {
      entity->destroy();
   }
}

bool EntityManager::hasNoEntities() { return entities.size() == 0; }

void EntityManager::update(float deltaTime) {
   for (auto& entity : entities) {
      entity->update(deltaTime);
   }
}

void EntityManager::render() {
   for (auto& entity : entities) {
      entity->render();
   }
}

Entity& EntityManager::addEntity(string name) {
   Entity* entity = new Entity(*this, name);
   entities.emplace_back(entity);
   return *entity;
}

vector<Entity*> EntityManager::getEntities() const { return entities; }
unsigned int EntityManager::getEntityCount() { return entities.size(); }
