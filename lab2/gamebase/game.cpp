#include "game.h"
#include "tamagochi.h"
#include <iostream>

namespace game {

SDL_Renderer *Game::renderer_ = nullptr;

Game::Game() {}   

Game::~Game() {}

void Game::Init(const char *title) {
    if ( SDL_Init(SDL_INIT_EVERYTHING) == 0 ) {
        
        window_ = SDL_CreateWindow(title, Game::windowSize.x, Game::windowSize.y, Game::windowSize.width, Game::windowSize.height, 0);
        if ( !window_ ) {
            printf( "SDL could not create a window! SDL Error: %s\n", SDL_GetError() );
            isRunning_ = false;
            return;
        }

        renderer_ = SDL_CreateRenderer(window_, -1, 0);
        if ( !renderer_ ) {
            printf( "SDL_mixer could not create a renderer! SDL Error: %s\n", SDL_GetError() );
            isRunning_ = false;
            return;
        }

        if ( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) {
            printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
            isRunning_ = false;
            return;
        }

        isRunning_ = true;
    } else {
        printf( "SDL could not be opened! SDL Error: %s\n", SDL_GetError() );
        isRunning_ = false;
        return;
    }
    
    background = new GameObject("background.png", 0, 0, Game::windowSize.width, Game::windowSize.height);
    shop = new GameObject("shopsign.png", 680, 20, 100, 100);
    kitten = new tamagochi::Pet("kitten.png", 450, 450, 400, 400);

    shopBackground = new GameObject("shop_background.png", 0, 0, Game::windowSize.width, Game::windowSize.height);
    exitButton = new GameObject ("exit.png", 600, 20, 180, 100);
    coins = new GameObject("coin.png", 700, 120, 100, 100);
    toys = new GameObject("toys.png", 110, 500, 150, 150);
    litterBox = new GameObject("litter_box.png", 80, 300, 150, 150);
    pills = new GameObject("pills.png", 50, 100, 200, 200);
    soldSign1 = new GameObject("sold.png", 100, 550, 200, 100);
    soldSign2 = new GameObject("sold.png", 100, 350, 200, 100);
    coin1 = new GameObject("zero.png", 620, 120, 100, 100);
    coin2 = new GameObject("zero.png", 550, 120, 100, 100);

    pricePills = new GameObject("price1.png", 250, 150, 200, 100);
    priceToys = new GameObject("price2.png", 250, 550, 200, 100);
    priceLitterBox = new GameObject("price2.png", 250, 350, 200, 100);
    

    isShopOpened_ = false;
    isLitterBoxBought_ = false;
    isToysBought_ = false;
    coins_ = 0;
    kitten->SetPet();
}

void Game::UpdateCoins() {
            int tmpCoin1 = coins_ % 10;
            int tmpCoin2 = coins_ / 10;
            switch (tmpCoin1) {
                case 0:
                    coin1->UpdateTex("zero.png");
                    break;
                case 1:
                    coin1->UpdateTex("one.png");
                    break;
                case 2:
                    coin1->UpdateTex("two.png");
                    break;
                case 3:
                    coin1->UpdateTex("three.png");
                    break;
                case 4:
                    coin1->UpdateTex("four.png");
                    break;
                case 5:
                    coin1->UpdateTex("five.png");
                    break;
                case 6:
                    coin1->UpdateTex("six.png");
                    break;
                case 7:
                    coin1->UpdateTex("seven.png");
                    break;
                case 8:
                    coin1->UpdateTex("eight.png");
                    break;
                case 9: 
                    coin1->UpdateTex("nine.png");
                    break;
            } 
            switch (tmpCoin2) {
                case 0:
                    coin2->UpdateTex("zero.png");
                    break;
                case 1:
                    coin2->UpdateTex("one.png");
                    break;
                case 2:
                    coin2->UpdateTex("two.png");
                    break;
                case 3:
                    coin2->UpdateTex("three.png");
                    break;
                case 4:
                    coin2->UpdateTex("four.png");
                    break;
                case 5:
                    coin2->UpdateTex("five.png");
                    break;
                case 6:
                    coin2->UpdateTex("six.png");
                    break;
                case 7:
                    coin2->UpdateTex("seven.png");
                    break;
                case 8:
                    coin2->UpdateTex("eight.png");
                    break;
                case 9: 
                    coin2->UpdateTex("nine.png");
                    break;
            }
}

void Game::HandleEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT:
            isRunning_ = false;
            break;
        case SDL_MOUSEBUTTONDOWN:
            MouseState mouse;
            mouse.buttons = SDL_GetMouseState(&mouse.x, &mouse.y);
            ProcessInput(mouse);
    }
}

void Game::ProcessInput(const MouseState& mouse) {
    if (mouse.buttons == 1 && isShopOpened_ == false) {
        if (mouse.x >= 120 && mouse.x <= 220 && mouse.y >= 20 && mouse.y <= 105) {
            kitten->AddHunger();
        }
        if (mouse.x >= 200 && mouse.x <= 300 && mouse.y >= 20 && mouse.y <= 105) {
            kitten->AddMood();
        }
        if (mouse.x >= 450 && mouse.x <= 850 && mouse.y >= 450 && mouse.y <= 850) {
            kitten->MakeMeow();
        }
        if (mouse.x >= 680 && mouse.x <= 780 && mouse.y >= 20 && mouse.y <= 120) {
            isShopOpened_ = true;
            return;
        }
        if (mouse.x >= 350 && mouse.x <= 450 && mouse.y >= 600 && mouse.y <= 700) {
            kitten->cleanPoop();
        }
    } 
    if (mouse.buttons == 1 && isShopOpened_ == true) {
        if (mouse.x >= 600 && mouse.x <= 780 && mouse.y >= 20 && mouse.y <= 120) {
            isShopOpened_ = false;
        }
        if (mouse.x >= 110 && mouse.x <= 260 && mouse.y >= 500 && mouse.y <= 650 && isToysBought_ == false && coins_ >= 30) {
            coins_ -= 30;
            UpdateCoins();
            toys->UpdatePlace(100, 450);
            isToysBought_ = true;
            toys->Update();
            soldSign1->Update();
        }
        if (mouse.x >= 80 && mouse.x <= 230 && mouse.y >= 300 && mouse.y <= 450 && isLitterBoxBought_ == false && coins_ >= 30 ) {
            coins_ -= 30;
            UpdateCoins();
            litterBox->UpdatePlace(300, 350);
            isLitterBoxBought_ = true;
            litterBox->Update();
            soldSign2->Update();
        }
        if (mouse.x >= 50 && mouse.x <= 250 && mouse.y >= 100 && mouse.y <= 300 && coins_ >= 10) {
            coins_ -= 10;
            UpdateCoins();
            kitten->GetTreated();
        }
    }
}

void Game::Update(int count) {
    if (isShopOpened_ == false) {
        background->Update();
        shop->Update();
        if (count % 10000 == 0) {
            kitten->Grow();
            if (coins_ < 99) coins_ += 1;
            UpdateCoins();
            kitten->isPetSick();
            kitten->SubHunger();
            if (isLitterBoxBought_ == false) {
                kitten->hasPetPooped();
            } else {
                litterBox->Update();
            }
            if (isToysBought_ == true) {
                toys->Update();
            } else {
                kitten->SubMood();
            }
            if (kitten->isPetAlive() == false) {
                SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "death", "The game is over\nИгра окончена", NULL);
                isRunning_ = false;
            }
        }
            kitten->UpdatePet();
    }
    else if (isShopOpened_ == true) {
        shopBackground->Update();
        exitButton->Update();
        coins->Update();
        pills->Update();
        if (isToysBought_ == false) {
            toys->Update();
            priceToys->Update();
        } else {
            soldSign1->Update();
        }
        if (isLitterBoxBought_ == false) {
            litterBox->Update();
            priceLitterBox->Update();
        } else {
            soldSign2->Update();
        }
        coin1->Update();
        coin2->Update();
        pricePills->Update();
    }
}

void Game::Render() {
    SDL_RenderClear(renderer_);
    if (isShopOpened_ == false) {
        background->Render();
        shop->Render();
        kitten->RenderPet();
        if (isToysBought_ == true) {
            toys->Render();
        }
        if (isLitterBoxBought_ == true) {
            litterBox->Render();
        }
    }
    else if (isShopOpened_ == true) {
        shopBackground->Render();
        exitButton->Render();
        coins->Render();
        pills->Render();
        if (isToysBought_ == false) {
            toys->Render();
            priceToys->Render();
        } else {
            soldSign1->Render();
        }
        if (isLitterBoxBought_ == false) {
            litterBox->Render();
            priceLitterBox->Render();
        } else {
            soldSign2->Render();
        }
        coin1->Render();
        coin2->Render();
        pricePills->Render();
    }
    SDL_RenderPresent(renderer_);
}

void Game::Clean() {
    SDL_DestroyWindow(window_);
    SDL_DestroyRenderer(renderer_);
    Mix_Quit();
    SDL_Quit();
}
}