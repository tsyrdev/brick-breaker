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

void TexturedRectangle::Update() {
    
}

void TexturedRectangle::Render(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, m_texture, NULL, &m_rect); 
}

