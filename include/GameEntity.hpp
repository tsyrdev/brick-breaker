#ifndef GAMEENTITY_HPP
#define GAMEENTITY_HPP

#include "TexturedRectangle.hpp"

class GameEntity {
    public: 
        GameEntity(SDL_Renderer* renderer, const char* filepath) {
            m_renderer = renderer; 
            m_sprite = new TexturedRectangle(m_renderer, filepath);
        }
        ~GameEntity() {
            delete m_sprite; 
        }
        void SetPosition(int x, int y) { m_sprite->SetPosition(x, y); }
        void SetDimensions(int w, int h) { m_sprite->SetDimensions(w, h); }
        void Update() {

        }
        void Render() {
            m_sprite->Render(m_renderer); 
        }
        int GetX() { return m_sprite->GetX(); }
        int GetY() { return m_sprite->GetY(); }
        int GetWidth() { return m_sprite->GetWidth(); }
        int GetHeight() { return m_sprite->GetHeight(); }
    private: 
        TexturedRectangle* m_sprite; 
        SDL_Renderer* m_renderer; 
}; 

#endif
