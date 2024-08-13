#include "PowerBall.hpp"

PowerBall::PowerBall(SDL_Renderer* renderer, Power power) : GameEntity(renderer) {
    m_power = power;
}
void PowerBall::SetUp() {
    AddTexturedComponent(ASSET_POWERBALL_FILEPATH.c_str());
    AddCollider();
}
void PowerBall::SetCollider() {
    GameEntity::SetCollider(GetX(), GetY(), GetWidth(), GetHeight());
}
Power PowerBall::GetPower() {
    return m_power; 
}

