#ifndef TEXTUREMANAHGER_H
#define TEXTUREMANAHGER_H

#include "Game.h"

class TextureManager {
public:
   static SDL_Texture* loadTexture(const char* fileName);
   static void draw(SDL_Texture* texture, SDL_Rect sourceRect,
                    SDL_Rect destRect, SDL_RendererFlip flip);
};

#endif
