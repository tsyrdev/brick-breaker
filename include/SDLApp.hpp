#ifndef SDLAPP_HPP
#define SDLAPP_HPP

#include <SDL.h> 
#include <functional>

class SDLApp {
    public: 
        SDLApp(const char* windowName, int x, int y, int w, int h); 
        ~SDLApp(); 
        SDL_Renderer* GetRenderer() const { return m_renderer; }
        void SetEventCallback(std::function<void(void)> EventCallback); 
        void SetRenderCallback(std::function<void(void)> RenderCallback); 
        void RunLoop(); 
        void QuitApp() { m_isRunning = false; }
        
        int GetMouseX() { return m_mouseX; }
        int GetMouseY() { return m_mouseY; }
    private: 
        SDL_Window* m_window; 
        SDL_Renderer* m_renderer;
        std::function<void(void)> m_eventCallback; 
        std::function<void(void)> m_renderCallback; 
        int m_mouseX, m_mouseY; 
        bool m_isRunning = true; 
}; 

#endif
