#include <iostream> 

#include <SDL.h> 

#include "SDLApp.hpp"
#include "TexturedRectangle.hpp"

const int WINDOW_WIDTH = 500; 
const int WINDOW_HEIGHT = 500; 
const char* title = "Brick Breaker!"; 

SDLApp* app; 
TexturedRectangle* ball; 
TexturedRectangle* brick; 

void eventCallback() {
    SDL_Event event; 

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT)
            app->QuitApp();
        else 
            std::cout << "something was pressed in: " << app->GetMouseX() << ", " << app->GetMouseY() << std::endl;
    }
}

void renderCallback() {
    SDL_SetRenderDrawColor(app->GetRenderer(), 255, 187, 145, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(app->GetRenderer());
    ball->Render(app->GetRenderer());
    brick->Render(app->GetRenderer());
}


int main() {
    const char* title = "Brick Breaker!"; 
    app = new SDLApp(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT); 
    ball = new TexturedRectangle(app->GetRenderer(), "./images/ball.bmp"); 
    brick = new TexturedRectangle(app->GetRenderer(), "./images/brick.bmp"); 
    ball->Draw(200, 200, 25, 25); 
    brick->Draw(0, 0, 50, 50); 
    std::cout << "set" << std::endl;     
    app->SetEventCallback(eventCallback);
    app->SetRenderCallback(renderCallback);
    app->RunLoop();

    delete ball; 
    delete app; 
    return 0; 
}
