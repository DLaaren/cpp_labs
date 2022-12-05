#pragma once

#include <cstdlib>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <memory>
#include "gameObject.h"
#include "textureManager.h"

namespace tamagochi {

class Stat : public game::GameObject {
    using game::GameObject::GameObject;
    private:
        int level_;
    public:
        void SetStat() {
            level_ = 100;
        }
        void SetStat(int value) {
            level_ = value;
        }

        void AddStat() {level_ += 10;}
        void SubStat() {level_ -= 10;}

        int GetStat() const {return level_;}
};

class HealthStat : public Stat {
    using Stat::Stat;
    public:
        void UpdateHealth() {
                if (this->GetStat() <= 100 && this->GetStat() > 80) {
                    this->UpdateTex("health.png");
                }
                if (this->GetStat() <= 80 && this->GetStat() > 50) {
                    this->UpdateTex("health80.png");
                }
                if (this->GetStat() <= 50 && this->GetStat() > 30) {
                    this->UpdateTex("health50.png");
                }
                if (this->GetStat() <= 30 && this->GetStat() > 10) {
                    this->UpdateTex("health30.png");
                }
                if (this->GetStat() == 10) {
                    this->UpdateTex("health0.png");
                }
                this->Update();
            }
};

class HungerStat : public Stat {
    using Stat::Stat;
    public:
        void UpdateHunger() {
            if (this->GetStat() <= 100 && this->GetStat() > 80) {
                this->UpdateTex("food.png");
            }
            if (this->GetStat() <= 80 && this->GetStat() > 50) {
                this->UpdateTex("food80.png");
            }
            if (this->GetStat() <= 50 && this->GetStat() > 30) {
                this->UpdateTex("food50.png");
            }
            if (this->GetStat() <= 30 && this->GetStat() > 10) {
                this->UpdateTex("food30.png");
            }
            if (this->GetStat() == 10) {
                this->UpdateTex("food0.png");
            }
            this->Update();
        }
};

class MoodStat : public Stat {
    using Stat::Stat;
    public:
        void UpdateMood() {
            if (this->GetStat() <= 100 && this->GetStat() > 80) {
                this->UpdateTex("mood.png");
            }
            if (this->GetStat() <= 80 && this->GetStat() > 50) {
                this->UpdateTex("mood80.png");
            }
            if (this->GetStat() <= 50 && this->GetStat() > 30) {
                this->UpdateTex("mood50.png");
            }
            if (this->GetStat() <= 30 && this->GetStat() > 10) {
                this->UpdateTex("mood30.png");
            }
            if (this->GetStat() == 10) {
                this->UpdateTex("mood0.png");
            }
            this->Update();
        }
};

enum Deaths {
    OLD, HUNGER, DISEASE, DISAPPEAR, ALIVE, DIED
};

class Pet : public game::GameObject {

    using game::GameObject::GameObject;

    private:
        Deaths death_;

        int age_;
        bool isAlive_;
        bool isSick_;
        bool hasPooped_;

        std::unique_ptr<HealthStat> health_;
        std::unique_ptr<HungerStat> hunger_;
        std::unique_ptr<MoodStat> mood_;
        std::unique_ptr<GameObject> termometer;
        std::unique_ptr<GameObject> poop;

        Mix_Music *meow;
        std::unique_ptr<GameObject> lovesign;

    public:

        void SetPet() {
            death_ = ALIVE;
            age_ = 0;

            isAlive_ = true;
            isSick_ = false;
            hasPooped_ = false;

            health_ = std::make_unique<HealthStat>("health.png", 20, 20, 100, 85);
            health_->SetStat();
            hunger_ = std::make_unique<HungerStat>("food.png", 120, 20, 100, 85);
            hunger_->SetStat();
            mood_ = std::make_unique<MoodStat>("mood.png", 200, 20, 100, 85);
            mood_->SetStat();

            termometer = std::make_unique<GameObject>("termometer.png", 400, 400, 100, 100);
            poop = std::make_unique<GameObject>("poop.png", 350, 600, 100, 100);

            meow = Mix_LoadMUS("meow.mp3");
            lovesign = std::make_unique<GameObject>("love.png", 400, 400, 100, 100);
        }

        void UpdatePet() {
            this->Update();
            health_->UpdateHealth();
            hunger_->UpdateHunger();
            mood_->UpdateMood();
            if(Mix_PlayingMusic() != 0 && isSick_ == false) {
                lovesign->Update();
            }
            if (isSick_ == true) {
                termometer->Update();
            }
            if (hasPooped_ == true) {
                poop->Update();
            }
        }

        void RenderPet() {
            this->Render();
            health_->Render();
            hunger_->Render();
            mood_->Render();
            if(Mix_PlayingMusic() != 0 && isSick_ == false) {
                lovesign->Render();
            }
            if (isSick_ == true) {
                termometer->Render();
            }
            if (hasPooped_ == true) {
                poop->Render();
            }
        }
        
        void cleanPoop() { hasPooped_ = false; }
        void hasPetPooped() {
            if (hasPooped_ == true) {
                this->SubHealth();
            }
        }
        bool isPetAlive() {return isAlive_;}
        void isPetSick() {
            if (isSick_) {
                this->SubHealth();
            }
        }

        void Grow() { 
            age_ += 1;
            if (age_ >= 80) {
                int randNum = std::rand() % 100;
                if (randNum <= 20) {
                    Die(OLD);
                }
            }
            int rand = std::rand() % 100;
            if (rand <= 20) {
                hasPooped_ = true;
            }
        }

        int GetAge() { return age_;}

        void GetSick() {
            isSick_ = true;
            if (health_->GetStat() >= 30 ) {
                health_->SetStat(50);
            }
            if (mood_->GetStat() >= 30) {
                mood_->SetStat(30);
            }
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "sickness",
            "Your pet has got sick\nYou need to treat him asap\nТвой питомец заболел\nВылечи его как можно скорее ", NULL);
        }

        void GetTreated() {
            isSick_ = false;
            health_->SetStat(100);
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "sickness", "Your pet is no sick anymore!!\nТвой питомец выздоровел!", NULL);
        }

        void Die(Deaths death_) {
            std::string age = std::to_string(age_);
            std::string tmp_message;
            const char *message;
            switch (death_) {
                case OLD:
                    tmp_message = "Your pet has died due to old age\nIt was " + age + " years old\nТвой питомец умер от старости\nЕму было " + age + " лет";
                    message = tmp_message.c_str();
                    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "death", message, NULL);
                    break;
                case HUNGER:
                    tmp_message = "Your pet has died due to hunger\nIt was " + age + " years old\n\nТвой питомец умер из-за голода\nЕму было " + age + " лет";
                    message = tmp_message.c_str();
                    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "death", message, NULL);
                    break;
                case DISEASE:
                    tmp_message = "Your pet has died due to disease\nIt was " + age + " years old\n\nТвой питомец умер из-за болезни\nЕму было " + age + " лет";
                    message = tmp_message.c_str();
                    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "death", message, NULL);
                    break;
                case DISAPPEAR:
                    tmp_message = "Your pet has gone because you did not love it :<\nIt was " + age + 
                    " years old\n\nТвой питомец ушёл от тебя, потому что ты не любил его :<\nЕму было " + age + " лет";
                    message = tmp_message.c_str();
                    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "death", message, NULL);
                    break;
                case DIED:
                    tmp_message = "Your pet has died\nIt was " + age + " years old\n\nТвой питомец умер\nЕму было " + age + " лет";
                    message = tmp_message.c_str();
                    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "death", message, NULL);
                    break;
            }
            isAlive_ = false;
        }

        void AddHunger() {
            if (hunger_->GetStat() >= 100) return;
            hunger_->AddStat();
        }

        void SubHunger() {
            hunger_->SubStat();
            if (hunger_->GetStat() == 0) {
                Die(HUNGER);
            }
        }

        void AddMood() {
            if (mood_->GetStat() >= 100) return;
            mood_->AddStat();
        }

        void SubMood() {
            mood_->SubStat();
            if (mood_->GetStat() == 0) {
                Die(DISAPPEAR);
                return;
            }
            if (mood_->GetStat() <= 50 && isSick_ == false) {
                int randNum = std::rand() % 100;
                if (randNum >= 20) {
                    this->GetSick();
                }
            }
        }

        void AddHealth() {
            if (health_->GetStat() >= 100) return;
            health_->AddStat();
        }

        void SubHealth() {
            health_->SubStat();
            if (health_->GetStat() <= 0) {
                if (isSick_ == true) {
                    Die(DISEASE);
                }
                else {
                    Die(DIED);
                }
            }
        }

        void MakeMeow() {
            if(Mix_PlayingMusic() == 0) {
                Mix_PlayMusic(meow, 0);
            }
        }
};
}