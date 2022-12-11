#include "gameObject.h"
#include "textureManager.h"
#include <iostream>

namespace game{

GameObject::GameObject(const char *texturesheet, int x, int y, int w, int h) {
    objTexture = TextureManager::LoadTexture(texturesheet);
    xpos = x;
    ypos = y;
    width = w;
    height = h;
} 

void GameObject::Update() {
    destRect.x = xpos;
    destRect.y = ypos;
    destRect.w = width;
    destRect.h = height;
}

void GameObject::Render() {
    SDL_RenderCopy(Game::renderer_, objTexture, NULL, &destRect);
}

void GameObject::UpdateTex(const char *texture) {
    SDL_DestroyTexture(objTexture);
    objTexture = TextureManager::LoadTexture(texture);
}
void GameObject::UpdatePlace(int x, int y) {
    xpos = x;
    ypos = y;
}
}