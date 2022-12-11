#include "gamebase/game.h"
#include <iostream>

int main() {
    std::unique_ptr<game::Game> game = std::make_unique<game::Game>();

    game->Init("Meow");
    int count;
    while (game->Running()) {
        count++;
        
        game->HandleEvents();
        game->Update(count);
        game->Render();
    }
    game->Clean();
    return 0;
} 
