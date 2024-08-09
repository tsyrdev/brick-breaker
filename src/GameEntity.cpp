#include "GameEntity.hpp"

GameEntity::GameEntity(SDL_Renderer* renderer, const char* filepath) {
    m_renderer = renderer; 
    m_sprite = new TexturedRectangle(m_renderer, filepath);
}
GameEntity::~GameEntity() {
    delete m_sprite; 
}
void GameEntity::SetDimensions(int w, int h) {
    m_sprite->SetDimensions(w, h); 
    m_inGameScale = w; 
}
void GameEntity::Update() {

}
void GameEntity::Render() {
    m_sprite->Render(m_renderer); 
}
void GameEntity::AddCollider(Collider2D* collider) {
    m_hitbox = collider; 
}
void GameEntity::AutomateCollider() {
    int x, y, r, g, b; 
    x = m_sprite->GetX();
    y = m_sprite->GetY();
    r = m_sprite->GetRKey(); 
    g = m_sprite->GetGKey(); 
    b = m_sprite->GetBKey(); 
    m_hitbox->SetColliderBoxAutomatically(x, y, m_sprite->GetSurface(), r, g, b, m_inGameScale);
}
void GameEntity::SetCollider(int x, int y, int w, int h) {
    m_hitbox->SetColliderBox(x, y, w, h);
}
SDL_bool GameEntity::Intersects(GameEntity* other) {
    return m_hitbox->Intersects(other->m_hitbox); 
}

