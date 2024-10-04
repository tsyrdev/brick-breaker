#ifndef SDLAPP_HPP
#define SDLAPP_HPP

#include <SDL.h> 
#include <functional>

class SDLApp {
    public: 
        SDLApp(Uint32 initFlags, const char* windowName, int x, int y, int w, int h); 
        ~SDLApp(); 
        SDL_Renderer* GetRenderer() const { return m_renderer; }
        void SaveScreenshot(std::string filepath); 
        SDL_Texture* GetScreenshot() {
            SDL_Surface* sshot = SDL_CreateRGBSurface(0, m_width, m_height, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
            SDL_RenderReadPixels(m_renderer, NULL, SDL_PIXELFORMAT_ARGB8888, sshot->pixels, sshot->pitch);
            return SDL_CreateTextureFromSurface(m_renderer, sshot);
        } 
        void SetEventCallback(std::function<void(void)> EventCallback); 
        void SetUpdateCallback(std::function<void(void)> UpdateCallback); 
        void SetRenderCallback(std::function<void(void)> RenderCallback); 
        void RunLoop(); 
        void SetFrameRate(int fps); 
        void QuitApp() { m_isRunning = false; }
        
        int GetMouseX() { return m_mouseX; }
        int GetMouseY() { return m_mouseY; }
        int GetWindowW() { return m_width; }
        int GetWindowH() { return m_height; }
    private: 
        SDL_Window* m_window; 
        SDL_Renderer* m_renderer;
        std::function<void(void)> m_eventCallback; 
        std::function<void(void)> m_updateCallback;
        std::function<void(void)> m_renderCallback; 
        int m_mouseX, m_mouseY; 
        int m_width, m_height; 
        double m_frameRateMilli;
        bool m_isRunning = true; 
}; 

#endif
