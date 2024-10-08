#ifndef TEXTUREDRECTANGLE_HPP
#define TEXTUREDRECTANGLE_HPP

#include <iostream>
#include <string> 

#include <SDL.h> 

#include "ResourceManager.hpp"

class TexturedRectangle {
    public: 
        TexturedRectangle(SDL_Renderer* renderer, std::string filepath);
        TexturedRectangle(SDL_Renderer* renderer, std::string filepath, int r, int g, int b);
        ~TexturedRectangle();
        void Update();
        void Render(SDL_Renderer* renderer);
        void SetPosition(int x, int y);
        int GetX();
        int GetY();
        void SetDimensions(int w, int h);
        int GetWidth();
        int GetHeight();
        void SetColorKey(Uint8 r, Uint8 g, Uint8 b);
        SDL_Surface* GetSurface() { return m_surface; }
        SDL_Texture* GetTexture() { return m_texture; }
        int GetRKey() { 
            return m_rKey; }
        int GetGKey() { 
            return m_gKey; }
        int GetBKey() { 
            return m_bKey; }
    private: 
        SDL_Rect m_rect; 
        SDL_Texture* m_texture; 
        SDL_Surface* m_surface; 
        int m_rKey = 0xFF;
        int m_gKey = 0x00;
        int m_bKey = 0xFF;
};

#endif
