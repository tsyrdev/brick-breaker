#include <iostream> 

#include <SDL.h> 

#include "SDLApp.hpp"
#include "GameEntity.hpp"

const int WINDOW_WIDTH = 500; 
const int WINDOW_HEIGHT = 500; 
const int BALL_WIDTH = 25; 
const int BALL_HEIGHT = 25; 
const int START_BALL_X = WINDOW_WIDTH / 2 - BALL_WIDTH / 2;
const int START_BALL_Y = 400;
const int BRICK_WIDTH = 50; 
const int BRICK_HEIGHT = 50; 
const int PLAYER_HEIGHT = 100;
const int PLAYER_WIDTH = 100; 
const int START_PLAYER_X = WINDOW_WIDTH / 2 - PLAYER_WIDTH / 2; 
const int START_PLAYER_Y = START_BALL_Y + BALL_HEIGHT; 
const char* title = "Brick Breaker!"; 

SDLApp* app; 
GameEntity* ball; 
GameEntity* brick; 
GameEntity* player; 

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
    static bool up = true; 
    static bool right = rand() % 2 == 0 ? true : false;
    int ballX = ball->GetX();
    int ballY = ball->GetY();
    if (up) {
        ballY--; 
        if (ballY < 0)
            up = false; 
    } else {
        ballY++;
        if (ballY + BALL_HEIGHT > WINDOW_HEIGHT)
            up = true; 
    }
    if (right) {
        ballX++;
        if (ballX + BALL_WIDTH > WINDOW_WIDTH) 
            right = false;
    } else {
        ballX--;
        if (ballX < 0)
            right = true; 
    }
    ball->SetPosition(ballX, ballY);

    // Draws the background
    SDL_SetRenderDrawColor(app->GetRenderer(), 255, 187, 145, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(app->GetRenderer());

    ball->Render();
    brick->Render();
    player->Render();
}


int main() {
    const char* title = "Brick Breaker!"; 
    app = new SDLApp(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT); 
    ball = new GameEntity(app->GetRenderer(), "./images/ball.bmp"); 
    brick = new GameEntity(app->GetRenderer(), "./images/brick.bmp"); 
    player = new GameEntity(app->GetRenderer(), "./images/player.bmp");

    ball->SetPosition(START_BALL_X, START_BALL_Y);
    ball->SetDimensions(BALL_WIDTH, BALL_HEIGHT);
    brick->SetPosition(0, 0);
    brick->SetDimensions(BRICK_WIDTH, BRICK_HEIGHT);
    player->SetPosition(START_PLAYER_X, START_PLAYER_Y);
    player->SetDimensions(PLAYER_WIDTH, PLAYER_HEIGHT);

    app->SetEventCallback(eventCallback);
    app->SetRenderCallback(renderCallback);
    app->SetFrameRate(200);
    app->RunLoop();

    delete ball; 
    delete app; 
    return 0; 
}
