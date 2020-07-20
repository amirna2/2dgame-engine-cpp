#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <vector>

using namespace std;

class Entity;
class Component;

class EntityManager {
private:
   vector<Entity*> entities;

public:
   void clearData();
   void update(float deltaTime);
   void render();
   bool hasNoEntities();
   Entity& addEntity(string name);
   vector<Entity*> getEntities() const;
   unsigned int getEntityCount();
};

#endif