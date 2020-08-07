#include "../../include/EntityManager.h"
#include "../../include/Game.h"
#include "SpriteComponent.h"
#include "TransformComponent.h"

using namespace std;

class KeyboardControlComponent : public Component {
public:
   string upKey;
   string downKey;
   string rightKey;
   string leftKey;
   string shootKey;
   TransformComponent* transform;
   SpriteComponent* sprite;

   KeyboardControlComponent();

   KeyboardControlComponent(string upKey, string rightKey, string downKey,
                            string leftKey, string shootKey);

   string getSDLKeyStringCode(string key);

   void initialize() override;

   void update(float deltaTime) override;
};