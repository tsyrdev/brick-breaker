#include "DynamicText.hpp"

#include <iostream>

bool DynamicText::s_ttfInitialized = false; 

DynamicText::DynamicText(std::string fontpath, size_t fontSize) {
    if (!s_ttfInitialized && TTF_Init() == -1) {
        std::cout << "failed to initialize" << std::endl; 
    } else 
        s_ttfInitialized = true; 
    m_ourFont = TTF_OpenFont(fontpath.c_str(), fontSize);
    if (m_ourFont == nullptr) {
        std::cout << "could not load font" << std::endl;
        exit(1); 
    }
}
DynamicText::~DynamicText() {
    if (nullptr != m_ourFont)
        TTF_CloseFont(m_ourFont); 
    if (nullptr != m_texture)
        SDL_DestroyTexture(m_texture);
}

void DynamicText::DrawText(SDL_Renderer* renderer, std::string text, Uint8 r, Uint8 g, Uint8 b) {
    DrawText(renderer, text, m_rect.x, m_rect.y, m_rect.w, m_rect.h, r, g, b);
}

// Defaults the color to white.
void DynamicText::DrawText(SDL_Renderer* renderer, std::string text, int x, int y, int w, int h) {
    DrawText(renderer, text, x, y, w, h, 255, 255, 255); 
}
void DynamicText::DrawText(SDL_Renderer* renderer, std::string text, int x, int y, int w, int h, Uint8 r, Uint8 g, Uint8 b) {
    m_rect.x = x; 
    m_rect.y = y; 
    m_rect.w = w; 
    m_rect.h = h; 
    SDL_Surface* surfaceText = TTF_RenderText_Solid(m_ourFont, text.c_str(), {r, g, b});

    m_texture = SDL_CreateTextureFromSurface(renderer, surfaceText);
    SDL_FreeSurface(surfaceText);
    SDL_RenderCopy(renderer, m_texture, NULL, &m_rect); 
}

void DynamicText::SetPosition(int x, int y) {
    m_rect.x = x;
    m_rect.y = y;
}

void DynamicText::SetDimensions(int w, int h) {
    m_rect.w = w; 
    m_rect.h = h;
}

int DynamicText::GetBestSize(int w, int h, const char* text) {
    int fontSize = 300; 
    int textWidth = 0;
    int textHeight = 0; 

    while (true) {
        TTF_SetFontSize(m_ourFont, fontSize);
        TTF_SizeText(m_ourFont, text, &textWidth, &textHeight);

        if (textWidth <= w && textHeight <= w) {
            break;
        }

        if (textWidth > w || textHeight > h) 
            fontSize--;
        else
            fontSize++;
    }

    return fontSize;
}
