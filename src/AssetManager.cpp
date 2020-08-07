#include "./include/AssetManager.h"

using namespace std;

AssetManager::AssetManager(EntityManager* manager) : manager(manager) {}

void AssetManager::clearData() { textures.clear(); }

void AssetManager::addTexture(string textureId, const char* filePath) {
   textures.emplace(textureId, TextureManager::loadTexture(filePath));
}

SDL_Texture* AssetManager::getTexture(string textureId) {
   return textures[textureId];
}
