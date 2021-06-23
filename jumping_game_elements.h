#ifndef JUMPINGGAMEELEMENTS_H
#define JUMPINGGAMEELEMENTS_H

#include <platform.h>
#include <movingplatform.h>
#include <timedplatform.h>
#include <timedmovingplatform.h>
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <animatedsprite.h>
#include <Shop.h>
#include <read_textures.h>
#include <smallelementcoin.h>
#include <memory>

class JumpingGameElements
{
private:
    const int count;
    std::vector<std::unique_ptr<Platform>> platformpointers;
    sf::IntRect current_long_platform_texture_rect;
    sf::IntRect current_small_platform_texture_rect;
    sf::IntRect current_long_timed_platform_texture_rect;
    sf::IntRect current_small_timed_platform_texture_rect;
    AnimatedSprite ludek;
public:
    JumpingGameElements(const int &platform_count):count(platform_count),
        current_long_platform_texture_rect(sf::IntRect(0,288,380,94)),
        current_small_platform_texture_rect(sf::IntRect(214,1662,200,100)),
        current_long_timed_platform_texture_rect(sf::IntRect(0,384,380,94)),
        current_small_timed_platform_texture_rect(sf::IntRect(382,204,200,100)), ludek(10){

        for(int i=0;i<count;i++){
            platformpointers.emplace_back(nullptr);
        }

        create_ludek();
    }

    void HeroSetVerticalSpeed(const float &ver_speed){
        ludek.SetVerticalSpeed(ver_speed);
    }

    float HeroGetVerticalSpeed(){
        return ludek.GetVerticalSpeed();
    }

    float HeroGetAcceleration(){
        return ludek.GetAcceleration();
    }

    void HeroSetRecVec(const std::string &vec_name){
        ludek.setrecvec(vec_name);
    }

    sf::FloatRect HeroGetGlobalBounds(){
        return ludek.getGlobalBounds();
    }

    void HeroMove(const float &move_x, const float &move_y){
        ludek.move(move_x,move_y);
    }

    void HeroStartJumpAnimation(){
        ludek.start_jump_animation();
    }

    void HeroSetAcceleration(const float &acceleration){
        ludek.SetAcceleration(acceleration);
    }

    void HeroStep(const sf::Time &elapsed, const sf::RenderWindow &window){
        ludek.step(elapsed,window);
    }

    void PlatformFullStep(const int &i, const sf::Time &elapsed, const float &speed_y){
        platformpointers[i]->full_step(elapsed,speed_y);
    }

    bool PlatformGetWotkingState(const int &i){
        return platformpointers[i]->Is_working();
    }

    sf::FloatRect PlatformGetGlobalBounds(const int &i){
        return platformpointers[i]->getGlobalBounds();
    }

    void PlatformActivate(const int &i){
        platformpointers[i]->activate();
    }

    SmallElementCoin* PlatformGetCoin(const int &i){
        return platformpointers[i]->GetCoin();
    }

    std::pair<int,int> PlatformPick(const int &i, sftools::Chronometer &chrono){
        return platformpointers[i]->pick(&chrono);
    }

    void PlatformChangeWorkingState(const int &i, const bool &change_to){
        platformpointers[i]->ChangeWorkingState(change_to);
    }

    void create_ludek(){
        ludek.setTexture(hero_texture);

        ludek.setScale(0.2,0.2);
        ludek.setTextureRect(sf::IntRect(0,482,328,433));//first frame

        ludek.setPosition(600,505);
        ludek.setMainrecvec("walk");
    }

    int GetPlatformCount(){
        return count;
    }

    void draw(sf::RenderWindow* window){

        for(auto &el : platformpointers){
            el->draw(window);
        }
        window->draw(ludek);
    }

    void set_new_platform_texture_rects(const sf::IntRect &long_plat,const sf::IntRect &short_plat,
                                        const sf::IntRect &long_timed_plat,const sf::IntRect &short_timed_plat){
        this->current_long_platform_texture_rect = long_plat;
        this->current_small_platform_texture_rect = short_plat;
        this->current_long_timed_platform_texture_rect = long_timed_plat;
        this->current_small_timed_platform_texture_rect = short_timed_plat;
    }

    void Platform_generate_new(const int &long_or_short, const int &i, const int &difficulty){ //podmienia starą platformę na nową random generation
        this->platformpointers[i] = std::make_unique<Platform>();//std::move(platform);
        this->platformpointers[i]->SetDifficulty(difficulty);
        this->platformpointers[i]->setTexture(jumping_elements_textures);
        if(long_or_short==0){
            this->platformpointers[i]->setScale(0.3,0.3);
            this->platformpointers[i]->setTextureRect(current_long_platform_texture_rect);
        }
        else{
            this->platformpointers[i]->setScale(0.4,0.4);
            this->platformpointers[i]->setTextureRect(current_small_platform_texture_rect);
        }
    }

    void PlatformSetNewPosition(const int &i, const sf::Vector2f &position){
        this->platformpointers[i]->setPosition(position);
        this->platformpointers[i]->SetMiddle();
        this->platformpointers[i]->random_coin(current_long_platform_texture_rect);
    }



};

#endif // JUMPINGGAMEELEMENTS_H
