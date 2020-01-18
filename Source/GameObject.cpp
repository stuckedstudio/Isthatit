#include "../Includes/GameObject.h"
#include "../Includes/TextureManager.h"
GameObject::GameObject(const char* texturesheet, SDL_Renderer* ren)
{
    renderer = ren;
    objTexture = TextureManager::LoadTexture(texturesheet,ren);
}

void GameObject::Update()
{


}

void GameObject::Render()
{

    
}