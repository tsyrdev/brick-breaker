#include <iostream>

#include "TexturedRectangle.hpp"

TexturedRectangle::TexturedRectangle(SDL_Renderer* renderer, std::string filepath) {
    m_surface = ResourceManager::GetInstance().GetSurface(filepath);  
    SDL_SetColorKey(m_surface, SDL_TRUE, SDL_MapRGB(m_surface->format, m_rKey, m_gKey, m_bKey));
    m_texture = SDL_CreateTextureFromSurface(renderer, m_surface); 
} 
TexturedRectangle::TexturedRectangle(SDL_Renderer* renderer, std::string filepath, int r, int g, int b) {
    m_rKey = r; 
    m_gKey = g; 
    m_bKey = b; 
    m_surface = ResourceManager::GetInstance().GetSurface(filepath);
    SDL_SetColorKey(m_surface, SDL_TRUE, SDL_MapRGB(m_surface->format, m_rKey, m_gKey, m_bKey));
    m_texture = SDL_CreateTextureFromSurface(renderer, m_surface); 
}
TexturedRectangle::~TexturedRectangle() {
    SDL_DestroyTexture(m_texture); 
    SDL_FreeSurface(m_surface); 
}
void TexturedRectangle::Update() {
    
}
void TexturedRectangle::Render(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, m_texture, NULL, &m_rect); 
}
void TexturedRectangle::SetPosition(int x, int y) {
    m_rect.x = x; 
    m_rect.y = y;
}
int TexturedRectangle::GetX() { return m_rect.x; }
int TexturedRectangle::GetY() { return m_rect.y; }
void TexturedRectangle::SetDimensions(int w, int h) {
    m_rect.w = w;
    m_rect.h = h; 
}
int TexturedRectangle::GetWidth() { return m_rect.w; }
int TexturedRectangle::GetHeight() { return m_rect.h; }
void TexturedRectangle::SetColorKey(Uint8 r, Uint8 g, Uint8 b) {
    m_rKey = r;
    m_gKey = g;
    m_bKey = b;
}
