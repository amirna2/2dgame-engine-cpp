#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include "./EntityManager.h"
#include "./TextureManager.h"
#include <map>
#include <string>

using namespace std;

class AssetManager {
private:
   EntityManager* manager;
   map<string, SDL_Texture*> textures;

public:
   AssetManager(EntityManager* manager);
   ~AssetManager();
   void clearData();
   void addTexture(string textureId, const char* fileName);
   SDL_Texture GetTexture(std::string textureId);
};

#endif