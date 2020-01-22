#include "../Includes/Map.h"
#include "../Includes/TextureManager.h"




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