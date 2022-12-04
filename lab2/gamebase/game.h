#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <gameObject.h>
#include <tamagochi.h>

namespace game {
class Game {
    public:
        Game();
        ~Game();

        void Init(const char *title);
        void HandleEvents();
        void Update(int count);
        void Render();
        void Clean();

        struct WindowSize {
            int x = SDL_WINDOWPOS_CENTERED;
            int y = SDL_WINDOWPOS_CENTERED;
            int width = 800;
            int height = 800;
        } windowSize;        

        struct MouseState {
            int x;
            int y;
            Uint32 buttons;
        };
        void ProcessInput(const MouseState &mouse);

        bool clickButton();

        bool Running() { return isRunning_; }

        void UpdateCoins();

        static SDL_Renderer *renderer_;

    private: 
        bool isRunning_;
        bool isShopOpened_;
        bool isToysBought_;
        bool isLitterBoxBought_;
        SDL_Window *window_;

        int coins_;
        GameObject *coin1;
        GameObject *coin2;

        tamagochi::Pet *kitten; 
        GameObject *background;
        GameObject *shop;
        GameObject *shopBackground;
        GameObject *exitButton;
        GameObject *coins;
        GameObject *toys;
        GameObject *litterBox;
        GameObject *pills;
        GameObject *soldSign1;
        GameObject *soldSign2;
        GameObject *pricePills;
        GameObject *priceToys;
        GameObject *priceLitterBox;
        };
}