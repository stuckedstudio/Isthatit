
#pragma once

#include "Game.h"
#include <vector>

class TextureManager
{
    public:
        static SDL_Texture* LoadTexture(const char* fileName);
        static std::vector<SDL_Texture*> GetMapableTextures();
        static void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest);
    private:
       
};