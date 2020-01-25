#include "../Includes/Map.h"
#include "../Includes/TextureManager.h"
#include <iostream>
#include <fstream>



Map::Map()
{
    Textures = TextureManager::GetMapableTextures();
    src.x = src.y = 0;
    src.w = dest.w = 32;
    src.h = dest.h = 32;

    dest.x = dest.y = 0;
}
Map::~Map()
{

}
void Map::LoadMap(int mapArr[20][25])
{
    for(int row = 0; row < 20; row++)
    {
        for(int column = 0; column < 25; column++)
        {
            map[row][column] = mapArr[row][column];
        }
    }

}
int Map::LoadMapFromFile(const char* file)
{
    std::ifstream mapfile (file,std::ios::in);
    if(mapfile.is_open())
    {
        std::string message = std::string("Not implmented error - trying to read map: ") + file;  
        SDL_ShowSimpleMessageBox(NULL,"Map read error",message.c_str(),Game::window);
        return 1;
    }
    else
    {
        std::string message = std::string("Could not read map at file: ") + file;  
        SDL_ShowSimpleMessageBox(NULL,"Map read error",message.c_str(),Game::window);
        return 1;
    }
    
}
void Map::DrawMap()
{
    //This is generating textures in the way they were loaded... Not that smart
    int type = 0;
    for(int row = 0; row < 20; row++)
    {
        for(int column = 0; column < 25; column++)
        {
            type = map[row][column];
            dest.x = column*32;
            dest.y = row*32;
            TextureManager::Draw(Textures.at(type),src,dest);
        }
    }
}