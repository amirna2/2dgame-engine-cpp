#include "./include/Map.h"
#include "./components/include/TileComponent.h"
#include "./include/Constants.h"
#include "./include/EntityManager.h"
#include "./include/Game.h"
#include <fstream>

using namespace std;

Map::Map(string textureId, int scale, int tileSize) {
   this->textureId = textureId;
   this->scale = scale;
   this->tileSize = tileSize;
}

void Map::loadMap(std::string filePath, int mapSizeX, int mapSizeY) {
   fstream mapFile;
   mapFile.open(filePath);

   for (int y = 0; y < mapSizeY; y++) {
      for (int x = 0; x < mapSizeX; x++) {
         char ch;
         mapFile.get(ch);
         int sourceRectY = atoi(&ch) * tileSize;
         mapFile.get(ch);
         int sourceRectX = atoi(&ch) * tileSize;
         addTile(sourceRectX, sourceRectY, x * (scale * tileSize),
                 y * (scale * tileSize));
         mapFile.ignore();
      }
   }
   mapFile.close();
}

void Map::addTile(int sourceRectX, int sourceRectY, int x, int y) {
   EntityManager* manager = Game::getInstance()->getEntityManger();
   Entity& newTile(manager->addEntity("Tile", TILEMAP_LAYER));
   newTile.addComponent<TileComponent>(sourceRectX, sourceRectY, x, y, tileSize,
                                       scale, textureId);
}