#pragma once

#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <gameObject.h>
#include <tamagochi.h>

namespace game {
class Game {
    public:
        Game() = default;
        ~Game() = default;

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
        std::unique_ptr<GameObject> coin1;
        std::unique_ptr<GameObject> coin2;

        std::unique_ptr<tamagochi::Pet> kitten; 
        std::unique_ptr<GameObject> background;
        std::unique_ptr<GameObject> shop;
        std::unique_ptr<GameObject> shopBackground;
        std::unique_ptr<GameObject> exitButton;
        std::unique_ptr<GameObject> coins;
        std::unique_ptr<GameObject> toys;
        std::unique_ptr<GameObject> litterBox;
        std::unique_ptr<GameObject> pills;
        std::unique_ptr<GameObject> soldSign1;
        std::unique_ptr<GameObject> soldSign2;
        std::unique_ptr<GameObject> pricePills;
        std::unique_ptr<GameObject> priceToys;
        std::unique_ptr<GameObject> priceLitterBox;
        };
}