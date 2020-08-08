#ifndef MAP_H
#define MAP_H

#include <string>

using namespace std;

class Map {
private:
   string textureId;
   int scale;
   int tileSize;

public:
   Map(string textureId, int scale, int tileSize);
   ~Map(){};
   void loadMap(string filePath, int mapSizeX, int mapSizeY);
   void addTile(int sourceX, int sourceY, int x, int y);
};

#endif MAP_H
