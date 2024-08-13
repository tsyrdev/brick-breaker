#ifndef DYNAMICTEXT_HPP
#define DYNAMICTEXT_HPP

#include <string>

#include <SDL.h>
#include <SDL_ttf.h>

class DynamicText {
    public:
        DynamicText(std::string fontpath, size_t fontSize);
        ~DynamicText();
        // Defaults the color to white.
        void DrawText(SDL_Renderer* renderer, std::string text, Uint8 r, Uint8 g, Uint8 b);
        void DrawText(SDL_Renderer* renderer, std::string text, int x, int y, int w, int h);
        void DrawText(SDL_Renderer* renderer, std::string text, int x, int y, int w, int h, Uint8 r, Uint8 g, Uint8 b);
        void SetPosition(int x, int y);
        void SetDimensions(int w, int h);
        int GetBestSize(int w, int h, const char* text);
        int GetX() { return m_rect.x; }
        int GetY() { return m_rect.y; }
    private: 
        SDL_Rect m_rect; 
        SDL_Texture* m_texture; 
        SDL_Surface* m_surface; 
        TTF_Font* m_ourFont; 
        static bool s_ttfInitialized; 
};

#endif
