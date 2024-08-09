#ifndef TEXTUREDRECTANGLE_HPP
#define TEXTUREDRECTANGLE_HPP

#include <SDL.h> 

class TexturedRectangle {
    public: 
        TexturedRectangle(SDL_Renderer* renderer, const char* filepath);
        ~TexturedRectangle();
        void Update();
        void Render(SDL_Renderer* renderer);
        void SetPosition(int x, int y) {m_rect.x = x; m_rect.y = y;}
        int GetX() { return m_rect.x; }
        int GetY() { return m_rect.y; }
        void SetDimensions(int w, int h) {m_rect.w = w; m_rect.h = h;}
        int GetWidth() { return m_rect.w; }
        int GetHeight() { return m_rect.h; }
    private: 
        SDL_Rect m_rect; 
        SDL_Texture* m_texture; 
};

#endif
