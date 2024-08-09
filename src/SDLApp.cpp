#include <iostream> 
#include "SDLApp.hpp"

SDLApp::SDLApp(const char* windowName, int x, int y, int w, int h) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        std::cout << "Failed to initialize SDL: " << SDL_GetError(); 
    
    m_window = SDL_CreateWindow(windowName, x, y, w, h, SDL_WINDOW_SHOWN); 
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED); 
}

SDLApp::~SDLApp() {
    SDL_DestroyRenderer(m_renderer); 
    SDL_DestroyWindow(m_window); 
    SDL_Quit(); 
}

void SDLApp::SetEventCallback(std::function<void(void)> EventCallback) {
    m_eventCallback = EventCallback;
}

void SDLApp::SetRenderCallback(std::function<void(void)> RenderCallback) {
    m_renderCallback = RenderCallback;
}

void SDLApp::RunLoop() {
    while (m_isRunning) {
        Uint32 buttons; 
        buttons = SDL_GetMouseState(&m_mouseX, &m_mouseY); 

        m_eventCallback(); 
        SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(m_renderer);

        m_renderCallback();

        SDL_RenderPresent(m_renderer);
        SDL_Delay(m_frameRateMilli);
    } 
}

void SDLApp::SetFrameRate(int fps) {
    m_frameRateMilli = 1.0 / fps * 1000;   
    std::cout << m_frameRateMilli;
}
