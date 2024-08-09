#ifndef TEXTUREDRECTANGLE_HPP
#define TEXTUREDRECTANGLE_HPP

#include <SDL.h> 

class TexturedRectangle {
    public: 
        TexturedRectangle(SDL_Renderer* renderer, const char* filepath);
        ~TexturedRectangle();
        void Draw(int x, int y, int w, int h);
        void Update();
        void Render(SDL_Renderer* renderer);
    private: 
        SDL_Rect m_rect; 
        SDL_Texture* m_texture; 
};

#endif
