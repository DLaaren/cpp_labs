#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
namespace game {

class GameObject {
    public:
        GameObject(const char* texturesheet, int x, int y, int w, int h);
        ~GameObject() = default;

        void Update();        
        void Render();

        void UpdateTex(const char* texture);
        void UpdatePlace(int x, int y);

    private:
        int xpos, ypos;
        int width, height;

        SDL_Texture *objTexture;
        SDL_Rect srcRect, destRect;
};

}


