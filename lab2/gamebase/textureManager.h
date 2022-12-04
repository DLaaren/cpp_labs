#pragma once

#include "game.h"

namespace game {

class TextureManager {
    public:
        static SDL_Texture *LoadTexture(const char *filename);
        static void Draw(SDL_Texture* tex, SDL_Rect destR);
};

}