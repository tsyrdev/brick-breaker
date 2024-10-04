#include "GameEntity.hpp"

GameEntity::GameEntity(SDL_Renderer* renderer) {
    m_renderer = renderer; 
    m_spriteIndex = 0;
}
GameEntity::~GameEntity() {
    for (int i = 0; i < m_sprites.size(); ++i)
        delete m_sprites[i]; 
}
void GameEntity::SetPosition(int index, int x, int y) {
    m_sprites[index]->SetPosition(x, y);
}
void GameEntity::SetPosition(int x, int y) { 
    for (int i = 0; i < m_sprites.size(); ++i) {
        m_sprites[i]->SetPosition(x, y);  
    }
}
void GameEntity::SetDimensions(int w, int h) {
    for (int i = 0; i < m_sprites.size(); ++i) 
        m_sprites[i]->SetDimensions(w, h);  
    m_inGameScale = w; 
}
void GameEntity::Update() {

}
void GameEntity::Render() {
    m_sprites[m_spriteIndex]->Render(m_renderer); 
}
void GameEntity::AddTexturedComponent(std::string spritepath) {
    m_sprites.push_back(new TexturedRectangle(m_renderer, spritepath));
}
void GameEntity::AddTexturedComponentWithKey(std::string spritepath, int r, int g, int b) {
    m_sprites.push_back(new TexturedRectangle(m_renderer, spritepath, r, g, b));
}
void GameEntity::AddCollider() {
    m_hitboxes.push_back(new Collider2D());
}
void GameEntity::AutomateCollider() {
    AutomateCollider(0);
}
void GameEntity::AutomateCollider(int index) {
    int x, y, r, g, b; 
    x = m_sprites[m_spriteIndex]->GetX();
    y = m_sprites[m_spriteIndex]->GetY();
    r = m_sprites[m_spriteIndex]->GetRKey(); 
    g = m_sprites[m_spriteIndex]->GetGKey(); 
    b = m_sprites[m_spriteIndex]->GetBKey(); 
    m_hitboxes[index]->SetColliderBoxAutomatically(x, y, m_sprites[m_spriteIndex]->GetSurface(), r, g, b, m_inGameScale);
}
void GameEntity::SetCollider(int x, int y, int w, int h) {
    m_hitboxes[m_spriteIndex]->SetColliderBox(x, y, w, h);
}
void GameEntity::SetCollider(int index, int x, int y, int w, int h) {
    m_hitboxes[index]->SetColliderBox(x, y, w, h);
}
SDL_bool* GameEntity::Intersects(GameEntity* other) {
    SDL_bool* indexes = new SDL_bool[m_hitboxes.size()]; 
    for (int i = 0; i < m_hitboxes.size(); ++i)
        for (int j = 0; j < other->m_hitboxes.size(); ++j) {
            if (m_hitboxes[i]->Intersects(other->m_hitboxes[j])) {
                indexes[i] = SDL_TRUE; 
                break; 
            } else 
                indexes[i] = SDL_FALSE;
        }
    return indexes;
}

