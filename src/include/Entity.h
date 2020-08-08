#ifndef ENTITY_H
#define ENTITY_H

#include <map>
#include <string>
#include <vector>

#include "../components/include/Component.h"
#include "./Constants.h"
#include "./EntityManager.h"

class Component;
class EntityManager;

using namespace std;

class Entity {
private:
   EntityManager& manager;
   bool active;
   vector<Component*> components;
   map<const type_info*, Component*> componentTypeMap;
   LayerType layer;

public:
   string name;
   Entity(EntityManager& manager);
   Entity(EntityManager& manager, string name);
   Entity(EntityManager& manager, string name, LayerType layer);
   void update(float deltaTime);
   void render();
   void destroy();
   bool isAcvtive() const;
   void listAllComponents() const;
   LayerType getLayerType() { return layer; }

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