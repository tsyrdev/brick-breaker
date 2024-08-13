#include <iostream> 
#include "SDLApp.hpp"

SDLApp::SDLApp(Uint32 initFlags, const char* windowName, int x, int y, int w, int h) {
    if (SDL_Init(initFlags) < 0)
        std::cout << "Failed to initialize SDL: " << SDL_GetError(); 
    m_width = w;    
    m_height = h; 
    m_window = SDL_CreateWindow(windowName, x, y, m_width, m_height, SDL_WINDOW_SHOWN); 
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED); 
}

SDLApp::~SDLApp() {
    SDL_DestroyRenderer(m_renderer); 
    SDL_DestroyWindow(m_window); 
    SDL_Quit(); 
}

void SDLApp::SaveScreenshot(std::string filepath) {
    SDL_Surface* sshot = SDL_CreateRGBSurface(0, m_width, m_height, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000); 
    SDL_RenderReadPixels(m_renderer, NULL, SDL_PIXELFORMAT_ARGB8888, sshot->pixels, sshot->pitch);
    SDL_SaveBMP(sshot, filepath.c_str());
    SDL_FreeSurface(sshot);
}

void SDLApp::SetEventCallback(std::function<void(void)> EventCallback) {
    m_eventCallback = EventCallback;
}

void SDLApp::SetUpdateCallback(std::function<void(void)> UpdateCallback) {
    m_updateCallback = UpdateCallback; 
}

void SDLApp::SetRenderCallback(std::function<void(void)> RenderCallback) {
    m_renderCallback = RenderCallback;
}

void SDLApp::RunLoop() {
    while (m_isRunning) {
        Uint32 startTime = SDL_GetTicks(); 
        Uint32 buttons; 
        buttons = SDL_GetMouseState(&m_mouseX, &m_mouseY); 

        m_eventCallback(); 
        m_updateCallback(); 
        SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(m_renderer);

        m_renderCallback();

        SDL_RenderPresent(m_renderer);

        Uint32 elapsedTime = SDL_GetTicks() - startTime; 
        if (elapsedTime < m_frameRateMilli)
            SDL_Delay(m_frameRateMilli - elapsedTime); 
    } 
}

void SDLApp::SetFrameRate(int fps) {
    m_frameRateMilli = 1.0 / fps * 1000;   
}
