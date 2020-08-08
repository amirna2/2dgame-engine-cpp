#include "./include/EntityManager.h"
#include "./include/Entity.h"
#include <iostream>

using namespace std;

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

Entity& EntityManager::addEntity(string entityName, LayerType layer) {
   Entity* entity = new Entity(*this, entityName, layer);
   entities.emplace_back(entity);
   return *entity;
}

vector<Entity*> EntityManager::getEntities() const { return entities; }
unsigned int EntityManager::getEntityCount() { return entities.size(); }

vector<Entity*> EntityManager::getEntitiesByLayer(LayerType layer) const {
   std::vector<Entity*> selectedEntities;
   for (auto& entity : entities) {
      if (entity->getLayerType() == layer) {
         selectedEntities.emplace_back(entity);
      }
   }
   return selectedEntities;
}

void EntityManager::listAllEntities() const {
   unsigned int i = 0;
   for (auto& entity : entities) {
      std::cout << "Entity[" << i << "]: " << entity->name << std::endl;
      entity->listAllComponents();
      i++;
   }
}