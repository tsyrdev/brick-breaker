#ifndef BRICK_HPP
#define BRICK_HPP

#include "GameEntity.hpp"
#include "PowerBall.hpp"

const int BRICK_WIDTH = 50; 
const int BRICK_HEIGHT = 50; 

class Brick : public GameEntity {
    public:
        Brick(SDL_Renderer* renderer, int durability, Power power); 
        ~Brick();
        void SetPosition(int x, int y);
        void SetDimensions(int w, int h);
        void SetCollider(int index, int x, int y, int w, int h);
        int GetHitsLeft();
        PowerBall* GetPowerBall() { return m_powerBall; }
        bool Hit();
        bool HasPower() { return m_powerBall != nullptr; }
    private:
        int m_hitsLeft;
        PowerBall* m_powerBall; 
};

#endif
