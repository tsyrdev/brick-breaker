#ifndef BALL_HPP
#define BALL_HPP

#include "GameEntity.hpp"

#include <string>
#include <iostream>

#include <SDL.h>

const int POWERBALL_WIDTH = 25.0;
const int POWERBALL_HEIGHT = 25.0;
const std::string ASSET_POWERBALL_FILEPATH = "./assets/images/powerball.bmp"; 

enum Power {
    NOTHING,
    BALL_SPEED_UP,
    BALL_SLOW_DOWN,
    PLAYER_SPEED_UP,
    PLAYER_SLOW_DOWN,
    PLUS_LIFE,
    MINUS_LIFE,
    PlUS_BALL
};

class PowerBall : public GameEntity {
    public:
        PowerBall(SDL_Renderer* renderer, Power power);
        void SetUp();
        void SetCollider();
        Power GetPower();
    private:
        Power m_power;
};

#endif
