#include "TexturedRectangle.hpp"


TexturedRectangle::TexturedRectangle(SDL_Renderer* renderer, const char* filepath) {
    SDL_Surface* surface = SDL_LoadBMP(filepath);           
    SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 255, 0, 215));
    m_texture = SDL_CreateTextureFromSurface(renderer, surface); 
    SDL_FreeSurface(surface); 
} 

TexturedRectangle::~TexturedRectangle() {
    SDL_DestroyTexture(m_texture); 
}

void TexturedRectangle::Draw(int x, int y, int w, int h) {
    m_rect.x = x;
    m_rect.y = y;
    m_rect.w = w;
    m_rect.h = h;
}

void TexturedRectangle::Update() {
    
}

void TexturedRectangle::Render(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, m_texture, NULL, &m_rect); 
}

