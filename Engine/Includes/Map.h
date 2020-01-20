#pragma once

#include <vector>
#include "Game.h"

class Map
{
    public:
        Map();
        ~Map();

        void LoadMap(int mapArr[20][25]);

        void DrawMap();
    
    private:
        SDL_Rect src,dest;
        std::vector<SDL_Texture*> Textures;

        int map[20][25];

};
