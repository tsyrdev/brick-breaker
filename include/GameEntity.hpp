#ifndef GAMEENTITY_HPP
#define GAMEENTITY_HPP

#include <string>
#include <vector>

#include <SDL.h> 

#include "TexturedRectangle.hpp"
#include "Collider2D.hpp"

class GameEntity {
    public: 
        GameEntity(SDL_Renderer* renderer);
        ~GameEntity();
        void SetPosition(int index, int x, int y);
        void SetPosition(int x, int y);
        void SetDimensions(int w, int h);
        void Update();
        void Render();
        void AddTexturedComponent(std::string spritepath);
        void AddTexturedComponentWithKey(std::string spritepath, int r, int g, int b); 
        void AddCollider(); 
        void AutomateCollider();
        void AutomateCollider(int index); 
        void SetCollider(int x, int y, int w, int h); 
        void SetCollider(int index, int x, int y, int w, int h); 
        SDL_bool* Intersects(GameEntity* other);
        int GetX() { return m_sprites[m_spriteIndex]->GetX(); }
        int GetY() { return m_sprites[m_spriteIndex]->GetY(); }
        int GetWidth() { return m_sprites[m_spriteIndex]->GetWidth(); }
        int GetHeight() { return m_sprites[m_spriteIndex]->GetHeight(); }
        int GetSpriteIndex() { return m_spriteIndex; }
        void SetSpriteIndex(int index) {
            m_spriteIndex = index; 
        }
    private: 
        int m_spriteIndex; 
        int m_inGameScale; 
        std::vector<Collider2D*> m_hitboxes; 
        std::vector<TexturedRectangle*> m_sprites; 
        SDL_Renderer* m_renderer; 
}; 

#endif
