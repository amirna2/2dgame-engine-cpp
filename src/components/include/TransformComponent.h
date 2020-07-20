#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include "../../../lib/glm/glm.hpp"
#include "../include/Component.h"

class TransformComponent : public Component {
private:
   glm::vec2 position;
   glm::vec2 velocity;
   int width;
   int height;
   int scale;

public:
   TransformComponent(int posX, int posY, int velX, int velY, int w, int h,
                      int s);
   ~TransformComponent(){};

   void initialize() override;
   void update(float deltaTime) override;
   void render() override;
};

#endif