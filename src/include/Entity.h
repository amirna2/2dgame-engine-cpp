#ifndef ENTITY_H
#define ENTITY_H

#include <map>
#include <string>
#include <vector>

class Component;
class EntityManager;

using namespace std;

class Entity {
private:
   EntityManager& manager;
   bool active;
   vector<Component*> components;
   map<const type_info*, Component*> componentTypeMap;

public:
   string name;
   Entity(EntityManager& manager);
   Entity(EntityManager& manager, string name);
   void update(float deltaTime);
   void render();
   void destroy();
   bool isAcvtive() const;

   template <typename T, typename... Targs> T& addComponent(Targs&&... args) {
      T* newComponent(new T(forward<Targs>(args)...));
      newComponent->owner = this;
      components.emplace_back(newComponent);
      componentTypeMap[&typeid(*newComponent)] = newComponent;
      newComponent->initialize();
      return *newComponent;
   }
   template <typename T> T* getComponent() {
      return static_cast<T*>(componentTypeMap[&typeid(T)]);
   }
};

#endif