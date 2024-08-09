#include <iostream> 

#include <SDL.h> 
#include <sys/syslimits.h>

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
const int BALL_SPEED = 5; 
const int PLAYER_SPEED = 5; 
const char* title = "Brick Breaker!"; 

SDLApp* app; 
GameEntity* ball; 
GameEntity* brick; 
GameEntity* player; 
int playerDir; 

void eventCallback() {
    SDL_Event event; 

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT)
            app->QuitApp();
        else {
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_a)
                    playerDir = -1;                 
                if (event.key.keysym.sym == SDLK_d)
                    playerDir = 1; 
            } if (event.type == SDL_KEYUP) {
                if (event.key.keysym.sym == SDLK_a || event.key.keysym.sym == SDLK_d)
                    playerDir = 0; 
            }
        }
    }
}

void renderCallback() {
    static bool ballUp = true; 
    static bool ballRight = rand() % 2 == 0 ? true : false;
    int ballX = ball->GetX();
    int ballY = ball->GetY();
    int playerX = player->GetX(); 

    if (ballUp) {
        ballY -= BALL_SPEED; 
        if (ballY < 0) {
            ballY += BALL_SPEED;
            ballUp = false; 
        }
    } else {
        ballY += BALL_SPEED;
        if (ballY + BALL_HEIGHT > WINDOW_HEIGHT) {
            ballY -= BALL_SPEED;
            ballUp = true; 
        }
    }
    if (ballRight) {
        ballX += BALL_SPEED;
        if (ballX + BALL_WIDTH > WINDOW_WIDTH) {
            ballX -= BALL_SPEED;
            ballRight = false;
        }
    } else {
        ballX -= BALL_SPEED;
        if (ballX < 0) {
            ballX += BALL_SPEED;
            ballRight = true; 
        }
    }
    ball->SetPosition(ballX, ballY);
    ball->AutomateCollider();

    if (playerDir == 1) {
        playerX += PLAYER_SPEED;
        if (playerX + PLAYER_WIDTH > WINDOW_WIDTH) {
            playerX -= PLAYER_SPEED;
            playerDir = 0; 
        }
    } else if (playerDir == -1) {
        playerX -= PLAYER_SPEED; 
        if (playerX < 0) {
            playerX += PLAYER_SPEED;
            playerDir = 0; 
        }
    }
    player->SetPosition(playerX, START_PLAYER_Y); 
    player->AutomateCollider(); 

    if (player->Intersects(ball) == SDL_TRUE)
        ballUp = true; 

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
    playerDir = 0; 

    ball->SetPosition(START_BALL_X, START_BALL_Y);
    ball->SetDimensions(BALL_WIDTH, BALL_HEIGHT);
    ball->AddCollider(new Collider2D()); 
    ball->AutomateCollider();
    // std::cout << "ball" << std::endl;

    brick->SetPosition(0, 0);
    brick->SetDimensions(BRICK_WIDTH, BRICK_HEIGHT);
    
    player->SetPosition(START_PLAYER_X, START_PLAYER_Y);
    player->SetDimensions(PLAYER_WIDTH, PLAYER_HEIGHT);
    player->AddCollider(new Collider2D()); 
    player->AutomateCollider();
    // std::cout << "player" << std::endl;

    app->SetEventCallback(eventCallback);
    app->SetRenderCallback(renderCallback);
    app->SetFrameRate(90);
    app->RunLoop();

    delete ball; 
    delete app; 
    return 0; 
};

