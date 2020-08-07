
#include "./include/TextureManager.h"

SDL_Texture* TextureManager::loadTexture(const char* fileName) {
   SDL_Surface* surface = IMG_Load(fileName);
   SDL_Renderer* renderer = Game::getInstance()->getRenderer();
   SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
   SDL_FreeSurface(surface);
   return texture;
}

void TextureManager::draw(SDL_Texture* texture, SDL_Rect sourceRect,
                          SDL_Rect destRect, SDL_RendererFlip flip) {
   SDL_Renderer* renderer = Game::getInstance()->getRenderer();
   SDL_RenderCopyEx(renderer, texture, &sourceRect, &destRect, 0.0f, NULL,
                    flip);
}