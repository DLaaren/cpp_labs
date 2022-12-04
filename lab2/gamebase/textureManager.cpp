#include "textureManager.h"
namespace game {

SDL_Texture* TextureManager::LoadTexture(const char* texture) {
    SDL_Surface* tempSurface = IMG_Load(texture);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer_, tempSurface);
    SDL_FreeSurface(tempSurface);
    return tex;
}

void TextureManager::Draw(SDL_Texture* tex, SDL_Rect destR) {
    SDL_RenderCopy(Game::renderer_, tex, NULL, &destR);
}

}