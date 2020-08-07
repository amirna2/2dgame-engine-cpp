#include "./include/Entity.h"
#include "./components/include/Component.h"
#include <iostream>

using namespace std;

Entity::Entity(EntityManager& manager) : manager(manager) {
   this->active = true;
}

Entity::Entity(EntityManager& manager, string name) : manager(manager) {
   this->active = true;
   this->name = name;
}

void Entity::update(float deltaTime) {
   for (auto& component : components) {
      component->update(deltaTime);
   }
}

void Entity::render() {
   for (auto& component : components) {
      component->render();
   }
}

void Entity::destroy() { this->active = false; }

bool Entity::isAcvtive() const { return active; }

void Entity::listAllComponents() const {
   for (auto mapElement : componentTypeMap) {
      cout << "    Component<" << mapElement.first->name() << ">" << endl;
   }
}
