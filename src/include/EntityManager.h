#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "Constants.h"
#include "Entity.h"
#include <vector>

using namespace std;

class Component;

class EntityManager {
private:
   vector<Entity*> entities;

public:
   void clearData();
   void update(float deltaTime);
   void render();

   bool hasNoEntities();
   vector<Entity*> getEntities() const;
   unsigned int getEntityCount();
   void listAllEntities() const;

   Entity& addEntity(string name);
   Entity& addEntity(string entityName, LayerType layer);
   vector<Entity*> getEntitiesByLayer(LayerType layer) const;
};

#endif