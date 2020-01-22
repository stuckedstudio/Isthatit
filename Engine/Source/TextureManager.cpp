#include <iostream>
#include "../Includes/TextureManager.h"
#include <filesystem>

namespace fs = std::filesystem;
SDL_Texture* TextureManager::LoadTexture(const char* texture)
{
    SDL_Surface* tempSurface = IMG_Load(texture);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer,tempSurface);
    SDL_FreeSurface(tempSurface);
    return tex;
}
std::vector<SDL_Texture*> TextureManager::GetMapableTextures()
{
    const char* dirRoot = "../..";
    std::vector<SDL_Texture*> texList;
    std::string path = std::string(dirRoot) + "/Assets/Tiles";
    std::cout << path << std::endl;
    try{
    for(const auto & entry : fs::directory_iterator(path))
    {
        texList.push_back(TextureManager::LoadTexture(entry.path().generic_string().c_str()));
    }
    }
    catch(fs::filesystem_error::exception)
    {
        SDL_ShowSimpleMessageBox(NULL,"Error Reading Data","Tile assets could not be read - Please reinstall program or contact the developer",Game::window);
        
    }
    return texList;
}
void TextureManager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest)
{
    SDL_RenderCopy(Game::renderer, tex, &src, &dest);
}