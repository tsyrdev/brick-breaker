#ifndef GAMEENTITY_HPP
#define GAMEENTITY_HPP

#include <SDL.h> 
#include "TexturedRectangle.hpp"
#include "Collider2D.hpp"

class GameEntity {
    public: 
        GameEntity(SDL_Renderer* renderer, const char* filepath);
        ~GameEntity();
        void SetPosition(int x, int y) { m_sprite->SetPosition(x, y); }
        void SetDimensions(int w, int h);
        void Update();
        void Render();
        int GetX() { return m_sprite->GetX(); }
        int GetY() { return m_sprite->GetY(); }
        int GetWidth() { return m_sprite->GetWidth(); }
        int GetHeight() { return m_sprite->GetHeight(); }
        void AddCollider(Collider2D* collider); 
        void AutomateCollider(); 
        void SetCollider(int x, int y, int w, int h); 
        SDL_bool Intersects(GameEntity* other);
    private: 
        int m_inGameScale; 
        Collider2D* m_hitbox; 
        TexturedRectangle* m_sprite; 
        SDL_Renderer* m_renderer; 
}; 

#endif
