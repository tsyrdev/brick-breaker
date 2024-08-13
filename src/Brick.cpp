#include "Brick.hpp"

Brick::Brick(SDL_Renderer* renderer, int durability, Power power) : GameEntity(renderer) {
    m_hitsLeft = durability;
    if (power != Power::NOTHING) {
        m_powerBall = new PowerBall(renderer, power);
        m_powerBall->SetUp();
    }
}
Brick::~Brick() {
}
void Brick::SetPosition(int x, int y) {
    GameEntity::SetPosition(x, y);
    if (m_powerBall != nullptr)
        m_powerBall->SetPosition(x + BRICK_WIDTH / 2, y);
}
void Brick::SetDimensions(int w, int h) {
    GameEntity::SetDimensions(w, h);
    if (m_powerBall != nullptr)
        m_powerBall->SetDimensions(POWERBALL_WIDTH, POWERBALL_HEIGHT);
}
void Brick::SetCollider(int index, int x, int y, int w, int h) {
    GameEntity::SetCollider(index, x, y, w, h);
    if (m_powerBall != nullptr)
        m_powerBall->SetCollider();
}
int Brick::GetHitsLeft() {
    return m_hitsLeft;
}
bool Brick::Hit() { 
    return --m_hitsLeft; 
}

