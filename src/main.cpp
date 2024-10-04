#include <iostream> 

#include <SDL.h> 
#include <string>
#include <list>

#include "SDLApp.hpp"
#include "GameEntity.hpp"
#include "ResourceManager.hpp"
#include "DynamicText.hpp"
#include "Sound.hpp"
#include "LevelReader.hpp"
#include "Brick.hpp"

// WINDOW DIMENSIONS
const int WINDOW_WIDTH = 500; 
const int WINDOW_HEIGHT = 500; 

// FILEPATHS
// fonts
const std::string ASSET_FONT1_FILEPATH = "./assets/fonts/ka1.ttf";
// images
const std::string ASSET_BALL_FILEPATH = "./assets/images/ball.bmp";
const std::string ASSET_BRICK1_FILEPATH = "./assets/images/brick1.bmp";
const std::string ASSET_BRICK2_FILEPATH = "./assets/images/brick2.bmp";
const std::string ASSET_BRICK3_FILEPATH = "./assets/images/brick3.bmp";
const std::string ASSET_PLAYER_FILEPATH = "./assets/images/player.bmp";
const std::string ASSET_HEART_FILEPATH = "./assets/images/heart.bmp";
const std::string ASSET_CROSS_FILEPATH = "./assets/images/cross.bmp";
const std::string ASSET_POWER_BALLSPEEDUP_FILEPATH = "./assets/images/ballSpeedUp.bmp";
const std::string ASSET_POWER_BALLSLOWDOWN_FILEPATH = "./assets/images/ballSlowDown.bmp";
const std::string ASSET_POWER_PLAYERSPEEDUP_FILEPATH = "./assets/images/playerSpeedUp.bmp";
const std::string ASSET_POWER_PLAYERSLOWDOWN_FILEPATH = "./assets/images/playerSlowDown.bmp";
const std::string ASSET_POWER_PLUSLIFE_FILEPATH = "./assets/images/heartPlus.bmp";
const std::string ASSET_POWER_MINUSLIFE_FILEPATH = "./assets/images/heartMinus.bmp";
const std::string ASSET_POWER_PLUSBALL_FILEPATH = "./assets/images/ballMinus.bmp";
const std::string ASSET_LOSTWRAPPER_FILEPATH = "./assets/images/lost.bmp";
const std::string ASSET_SKEY_FILEPATH = "./assets/images/sKey.bmp";
const std::string ASSET_PKEY_FILEPATH = "./assets/images/pKey.bmp";
const std::string ASSET_MKEY_FILEPATH = "./assets/images/mKey.bmp";
const std::string ASSET_LKEY_FILEPATH = "./assets/images/lKey.bmp";
const std::string ASSET_LOGO_FILEPATH = "./assets/images/logoWBG.bmp";
// const std::string ASSET_POWERBALL_FILEPATH = "./assets/images/powerball.bmp"; // Defined in PowerBall.hpp
// files
const std::string ASSET_SCORES_FILEPATH = "./assets/levels/scores.txt";
const std::string ASSET_DEFAULT_LEVEL_FILEPATH = "./assets/levels/level1.txt";
// sounds
const std::string ASSET_SOUND_DEATH_FILEPATH = "./assets/sounds/Smash_Death_Sound.wav";

// related to the BALL
const int BALL_WIDTH = 25; 
const int BALL_HEIGHT = 25; 
const int START_BALL_X = WINDOW_WIDTH / 2 - BALL_WIDTH / 2;
const int START_BALL_Y = 350;
const float START_BALL_SPEED = 4.0; 

// related to the BRICKS
// const int BRICK_WIDTH = 50; // Defined in Brick.hpp
// const int BRICK_HEIGHT = 50; // Defined in Brick.hpp
const int BRICK_SPRITE_HEIGHT = 20; 

// related to the POWERBALLS
// const int POWERBALL_WIDTH = 25.0; // Defined in PowerBall.hpp
// const int POWERBALL_HEIGHT = 25.0; // Defined in PowerBall.hpp
const float POWERBALL_INIT_SPEED = 1.0;

// related to the POWERBARS
const int POWERLOGO_SIZE = 40; // its a square so 50x50 

// related to the PLAYER
const int PLAYER_HEIGHT = 100;
const int PLAYER_SPRITE_HEIGHT = 20;
const int PLAYER_WIDTH = 100; 
const int START_PLAYER_X = WINDOW_WIDTH / 2 - PLAYER_WIDTH / 2; 
const int START_PLAYER_Y = 400;
const float START_PLAYER_SPEED = 5.0; 
const int PLAYER_MOVE_RIGHT = 1;
const int PLAYER_MOVE_LEFT = -1;
const int PLAYER_STOPPED = 0;

// related to the LOSS SCREEN
const int START_LOST_X = 0;
const int START_LOST_Y = 150;
const float LOST_WRAPPER_SPEED = 5.0;
const int LOST_MESSAGE_W = 300;
const int LOST_MESSAGE_H = 50;
const int LOST_MESSAGE_X = WINDOW_WIDTH / 2 - LOST_MESSAGE_W / 2; 
const int LOST_MESSAGE_Y = -50; 
const float LOST_MESSAGE_SPEED = 4.0;
const int HIGHSCORE_MESSAGE_W = 200;
const int HIGHSCORE_MESSAGE_H = 35;
const int HIGHSCORE_MESSAGE_X = (WINDOW_WIDTH - HIGHSCORE_MESSAGE_W) / 2;
const int HIGHSCORE_MESSAGE_Y_OFFSET = 145;
const int SCORE_MESSAGE_W = 100;
const int SCORE_MESSAGE_H = 35;
const int SCORE_MESSAGE_X = (WINDOW_WIDTH - SCORE_MESSAGE_W) / 2;
const int SCORE_MESSAGE_Y_OFFSET = 270;
const int HIGHSCORE_W = 160;
const int HIGHSCORE_H = 100;
const int HIGHSCORE_X = (WINDOW_WIDTH - HIGHSCORE_W) / 2;
const int HIGHSCORE_Y_OFFSET = 170;
const int SCORE_W = 150;
const int SCORE_H = 100;
const int SCORE_X = (WINDOW_WIDTH - SCORE_W) / 2;
const int SCORE_Y_OFFSET = 300;
const int AGAIN_W = 350;
const int AGAIN_H = 35;
const int AGAIN_X = (WINDOW_WIDTH - AGAIN_W) / 2;
const int AGAIN_Y_OFFSET = 400;
const int CROSS_X = 0;
const int CROSS_Y = 470;
const int CROSS_Y_OFFSET = -30;

const int START_KEY_WIDTH = 150;
const int START_KEY_HEIGHT = 150;
const int START_KEY_X = 60;
const int START_KEY_Y = 300;

// COLLIDER INDEXES
const int COLL_LEFT = 0;
const int COLL_TOP = 1;
const int COLL_RIGHT = 2;
const int COLL_BOT = 3;

// GAME TITLE
const std::string TITLE = "Brick Breaker 2"; 

SDLApp* app; 
GameEntity* ball; 
std::list<Brick*> bricks; 
std::vector<PowerBall*> powers;
GameEntity* player; 
TexturedRectangle* heart;
TexturedRectangle* lostWrapper;
TexturedRectangle* cross;
TexturedRectangle* gameLogo;
DynamicText* lostMessage;
DynamicText* againMessage;
DynamicText* scoreMessage;
DynamicText* highscoreMessage;
DynamicText* highscore;
DynamicText* score;
GameEntity* sCollider; 
TexturedRectangle* pKey;
TexturedRectangle* mKey;
TexturedRectangle* lKey;

Sound* deathSound;

enum State {
    START,
    PAUSED,
    PLAYING,
    WON,
    MENU,
    LEVEL,
    LOST
};

struct MenuText { // to be used in the menu 
    DynamicText text; 
    bool isSelected; 
};

struct ActivePower { // consider making this a class 
    Power power;
    int activeTime; 
    TexturedRectangle* textRect; 
};

struct GameState {
    Level level; 
    int playerDir; 
    int ballYDir;
    int ballXDir;
    int score;
    float playerSpeed; 
    float ballSpeed; 
    int lives; 
    State state;
    bool isHighscore;
    SDL_Texture* snapshot;
    std::vector<ActivePower> activePowers; 
};

GameState* gameState; 

void initGame() {
    gameState->playerDir = 0;
    gameState->ballXDir = -1; 
    gameState->ballYDir = rand() % 2 == 0 ? -1 : 1;
    gameState->playerSpeed = START_PLAYER_SPEED;
    gameState->ballSpeed = START_BALL_SPEED;
    gameState->score = 0; 
    gameState->state = State::PLAYING;
    gameState->lives = 3; 
    gameState->isHighscore = false;
    cross->SetPosition(CROSS_X, CROSS_Y);
    lostWrapper->SetPosition(START_LOST_X, START_LOST_Y);
    highscoreMessage->SetPosition(HIGHSCORE_MESSAGE_X, START_LOST_Y + HIGHSCORE_MESSAGE_Y_OFFSET);
    scoreMessage->SetPosition(SCORE_MESSAGE_X, START_LOST_Y + SCORE_MESSAGE_Y_OFFSET);
    highscore->SetPosition(HIGHSCORE_X, START_LOST_Y + HIGHSCORE_Y_OFFSET);
    score->SetPosition(SCORE_X, START_LOST_Y + SCORE_MESSAGE_Y_OFFSET);
    againMessage->SetPosition(AGAIN_X, START_LOST_Y + AGAIN_Y_OFFSET);
    lostMessage->SetPosition(LOST_MESSAGE_X, LOST_MESSAGE_Y);

    ball->SetPosition((app->GetWindowW() - BALL_WIDTH) / 2, START_BALL_Y);

    player->SetPosition((app->GetWindowW() - PLAYER_WIDTH) / 2, START_PLAYER_Y);  
    
    gameState->activePowers.clear();
    powers.clear();
    bricks.clear();
    for (int x = 0; x < sizeof(gameState->level.shape) / sizeof(gameState->level.shape[0]); ++x) 
        for (int y = 0; y < sizeof(gameState->level.shape[0]) / sizeof(gameState->level.shape[0][0]); ++y)
            if (gameState->level.shape[x][y] != 0) {
                                Brick* brick = new Brick(app->GetRenderer(), gameState->level.shape[x][y], gameState->level.powers[x][y]);
                if (gameState->level.shape[x][y] == 3) {
                    brick->AddTexturedComponent(ASSET_BRICK3_FILEPATH);
                    brick->AddTexturedComponent(ASSET_BRICK2_FILEPATH);
                    brick->AddTexturedComponent(ASSET_BRICK1_FILEPATH);
                } else if (gameState->level.shape[x][y] == 2) {
                    brick->AddTexturedComponent(ASSET_BRICK2_FILEPATH);
                    brick->AddTexturedComponent(ASSET_BRICK1_FILEPATH);
                } else {
                    brick->AddTexturedComponent(ASSET_BRICK1_FILEPATH);
                }

                brick->AddCollider();
                brick->AddCollider();
                brick->AddCollider();
                brick->AddCollider();
                int bx = y * BRICK_WIDTH; 
                int by = x * BRICK_SPRITE_HEIGHT;
                int bw = BRICK_WIDTH;
                int bh = BRICK_HEIGHT;
                int ch = BRICK_SPRITE_HEIGHT;
                brick->SetPosition(bx, by);
                brick->SetDimensions(bw, bh);
                brick->SetCollider(COLL_LEFT, bx, by, 1, ch);
                brick->SetCollider(COLL_RIGHT, bx + BRICK_WIDTH, by, 1, ch);
                brick->SetCollider(COLL_TOP, bx, by, bw, 1);
                brick->SetCollider(COLL_BOT, bx, by + BRICK_SPRITE_HEIGHT, bw, 1);
                bricks.push_back(brick);
            }
}

void pauseGame() {
    gameState->snapshot = app->GetScreenshot(); 
    SDL_SetTextureColorMod(gameState->snapshot, 160, 160, 160);
}

void activatePower(Power power) {
    ActivePower activePower;
    activePower.power = power;

    switch(power) {
        case Power::BALL_SPEED_UP: 
            activePower.textRect = new TexturedRectangle(app->GetRenderer(), ASSET_POWER_BALLSPEEDUP_FILEPATH.c_str());
            gameState->ballSpeed += 0.5;
            // std::cout << "ball speedup" << std::endl;
            break;
        case Power::BALL_SLOW_DOWN:
            if (gameState->ballSpeed - 0.5 > 0) {
                gameState->ballSpeed -= 0.5;
                activePower.textRect = new TexturedRectangle(app->GetRenderer(), ASSET_POWER_BALLSLOWDOWN_FILEPATH.c_str());
                // std::cout << "ball slowdown" << std::endl;
            }
            break;
        case Power::PLAYER_SPEED_UP:
            activePower.textRect = new TexturedRectangle(app->GetRenderer(), ASSET_POWER_PLAYERSPEEDUP_FILEPATH.c_str());
            gameState->playerSpeed += 1;
            // std::cout << "player speedup" << std::endl;
            break;
        case Power::PLAYER_SLOW_DOWN:
            activePower.textRect = new TexturedRectangle(app->GetRenderer(), ASSET_POWER_PLAYERSLOWDOWN_FILEPATH.c_str());
            if (gameState->playerSpeed - 0.5 > 0) 
                gameState->playerSpeed -= 0.5;
                // std::cout << "player slowdown" << std::endl;
            break;
        case Power::MINUS_LIFE:
            activePower.textRect = new TexturedRectangle(app->GetRenderer(), ASSET_POWER_MINUSLIFE_FILEPATH.c_str());
            if (gameState->lives - 1 > 0)
                gameState->lives--;
                // std::cout << "lives -1" << std::endl;
            break;
        case Power::PLUS_LIFE:
            activePower.textRect = new TexturedRectangle(app->GetRenderer(), ASSET_POWER_PLUSLIFE_FILEPATH.c_str());
            gameState->lives++;
            // std::cout << "lives +1" << std::endl;
            break;
        default: 
             std::cout << "nothing powerball" << std::endl;
    }
    
    gameState->activePowers.push_back(activePower); 
}

// event handlers 

void startEventHandler(SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_s) {
            ball->SetPosition(START_BALL_X, START_BALL_Y);
            gameState->state = State::PLAYING;
            delete sCollider; 
            delete gameLogo;
        }
    }
}

void playingEventHandler(SDL_Event& event, const Uint8* keyState) {
    if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_a)
            gameState->playerDir = PLAYER_MOVE_LEFT; 
        else if (event.key.keysym.sym == SDLK_d)
            gameState->playerDir = PLAYER_MOVE_RIGHT;
        else if (event.key.keysym.sym == SDLK_p) {
            pauseGame();
            gameState->state = State::PAUSED;
            std::cout << "pause" << std::endl;
        }
    } else if (event.type == SDL_KEYUP) {
        if (event.key.keysym.sym == SDLK_a || 
            event.key.keysym.sym == SDLK_d) {
            if (keyState[SDL_SCANCODE_A] == 1) {
                gameState->playerDir = PLAYER_MOVE_LEFT;
            }
            else if (keyState[SDL_SCANCODE_D] == 1) {
                gameState->playerDir = PLAYER_MOVE_RIGHT;
            } else
                gameState->playerDir = PLAYER_STOPPED;
        } else if (event.key.keysym.sym == SDLK_r) {
            initGame();
            std::cout << "reset" << std::endl;
        } 
    }
}

void wonEventHandler(SDL_Event& event, const Uint8* keyState) {
    if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_a)
            gameState->playerDir = PLAYER_MOVE_LEFT; 
        if (event.key.keysym.sym == SDLK_d)
            gameState->playerDir = PLAYER_MOVE_RIGHT;
    } else if (event.type == SDL_KEYUP) {
        if (event.key.keysym.sym == SDLK_a || 
            event.key.keysym.sym == SDLK_d) {
            if (keyState[SDL_SCANCODE_A] == 1) {
                gameState->playerDir = PLAYER_MOVE_LEFT;
            }
            else if (keyState[SDL_SCANCODE_D] == 1) {
                gameState->playerDir = PLAYER_MOVE_RIGHT;
            } else
                gameState->playerDir = PLAYER_STOPPED;
        } else if (event.key.keysym.sym == SDLK_r) {
            initGame();
            std::cout << "reset" << std::endl;
        }
    }
}

void pausedEventHandler(SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_p) 
            gameState->state = State::PLAYING;
        else if (event.key.keysym.sym == SDLK_m) 
            gameState->state = State::MENU;
        else if (event.key.keysym.sym == SDLK_l) 
            gameState->state = State::LEVEL;
    }
}

void menuEventHandler(SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_ESCAPE) 
            gameState->state = State::PAUSED; 
        else if (event.key.keysym.sym) {
            // TODO: Handle filepath input 
            // Essentially build the string
            // with the user's keypresses.
        }
    }
}

void lostEventHandler(SDL_Event& event) {
    if (event.type == SDL_KEYDOWN || event.type == SDL_MOUSEBUTTONDOWN) {
        gameState->state = State::PLAYING;
        if (gameState->isHighscore)
            gameState->level.bestScore = gameState->score;
        initGame();
    }
}

void HandleEvents() {
    //std::cout << "start event" << std::endl;
    SDL_Event event; 
    const Uint8* keyState = SDL_GetKeyboardState(NULL);

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT)
            app->QuitApp();
        switch (gameState->state) {
            case State::START:
                startEventHandler(event);
                break;
            case State::PLAYING:
                playingEventHandler(event, keyState);
                break;
            case State::WON:
                wonEventHandler(event, keyState);
                break;
            case State::PAUSED:
                pausedEventHandler(event);
                break;
            case State::LEVEL:
                break;
            case State::MENU: 
                menuEventHandler(event);
                break;
            case State::LOST:
                lostEventHandler(event);
                break;
       }
        
    }
    //std::cout << "end event" << std::endl;
}

// update handlers
void startUpdateHandler() {
    int ballX = ball->GetX();
    int ballY = ball->GetY();

    if (ballX < 0 || ballX + ball->GetWidth() > app->GetWindowW()) {
        gameState->ballXDir *= -1;
        ballX += gameState->ballSpeed * gameState->ballXDir;
    }
    if (ballY < 0 || ballY > app->GetWindowH()) {
        gameState->ballYDir *= -1;
        ballY += gameState->ballSpeed * gameState->ballYDir;
    }

    ballX += gameState->ballSpeed * gameState->ballXDir;
    ballY += gameState->ballSpeed * gameState->ballYDir;

    ball->SetPosition(ballX, ballY);
    ball->SetCollider(ballX, ballY, BALL_WIDTH, BALL_HEIGHT);

    SDL_bool* intersections = sCollider->Intersects(ball); 
    if (intersections[COLL_TOP] || intersections[COLL_BOT]) {
        gameState->ballYDir *= -1;
    }
    if (intersections[COLL_LEFT] || intersections[COLL_RIGHT]) {
        gameState->ballXDir *= -1;
    }
    delete intersections;
}

void playingUpdateHandler() {
    if (gameState->lives == 0) {
        gameState->state = State::LOST;
        if (gameState->score > gameState->level.bestScore)
            gameState->isHighscore = true; 
    }
    if (bricks.size() == 0) {
        gameState->state = State::WON;
    }

    int ballX = ball->GetX();
    int ballY = ball->GetY();

    if (ballX < 0 || ballX + ball->GetWidth() > app->GetWindowW()) {
        gameState->ballXDir *= -1;
        ballX += gameState->ballSpeed * gameState->ballXDir;
    }
    if (ballY < 0) {
        gameState->ballYDir *= -1;
        ballY += gameState->ballSpeed * gameState->ballYDir;
    }
    if (ballY > app->GetWindowH()) {
        gameState->lives--;
        if (gameState->lives > 0) {
            gameState->ballYDir *= -1; 
            gameState->ballXDir = rand() % 2 == 0 ? -1 : 1;
            ballX = START_BALL_X;
            ballY = START_BALL_Y;
        }
        //deathSound->PlaySound();
    }

    ballX += gameState->ballSpeed * gameState->ballXDir;
    ballY += gameState->ballSpeed * gameState->ballYDir;

    ball->SetPosition(ballX, ballY);
    ball->SetCollider(ballX, ballY, BALL_WIDTH, BALL_HEIGHT);

    int playerX = player->GetX(); 

    playerX += gameState->playerSpeed * gameState->playerDir;

    if (playerX + player->GetWidth() > app->GetWindowW()) {
        playerX = app->GetWindowH() - player->GetWidth(); 
        gameState->playerDir = 0; 
    } else if (playerX < 0) {
        playerX = 0;
        gameState->playerDir = 0; 
    }

    player->SetPosition(playerX, START_PLAYER_Y); 
    player->SetCollider(COLL_LEFT, playerX, START_PLAYER_Y, 1, 20);
    player->SetCollider(COLL_RIGHT, playerX + PLAYER_WIDTH, START_PLAYER_Y, 1, 20);
    player->SetCollider(COLL_TOP, playerX, START_PLAYER_Y, 100, 1);

    SDL_bool* playerInter = player->Intersects(ball);
    if (playerInter[COLL_LEFT] == SDL_TRUE) {
        if (gameState->ballXDir == 1)
            gameState->ballXDir *= -1;
        gameState->ballYDir = -1; 
    } else if (playerInter[COLL_RIGHT] == SDL_TRUE) {
        if (gameState->ballXDir == -1)
            gameState->ballXDir *= -1;
        gameState->ballYDir = -1; 
    } else if (playerInter[COLL_TOP] == SDL_TRUE)
        gameState->ballYDir = -1;

    for (auto it = bricks.begin(); it != bricks.end(); ) {
        SDL_bool* brickInter = (*it)->Intersects(ball);
        bool collided = false; 
        if (brickInter[COLL_LEFT] == SDL_TRUE) {
            if (gameState->ballXDir == 1)
                gameState->ballXDir = -1; 
            collided = true; 
        } else if (brickInter[COLL_RIGHT] == SDL_TRUE) {
            if (gameState->ballXDir == -1)
                gameState->ballXDir = 1;
            collided = true; 
        }
        
        if (brickInter[COLL_BOT] == SDL_TRUE) {
            if (gameState->ballYDir == -1)
                gameState->ballYDir = 1;
            collided = true; 
        } else if (brickInter[COLL_TOP] == SDL_TRUE) {
            if (gameState->ballYDir == 1)
                gameState->ballYDir = -1;
            collided = true; 
        }
        if (collided) {
            (*it)->Hit();
            if ((*it)->GetHitsLeft() <= 0) {
                // TODO: Change the color of the brick once
                gameState->score++;  
                if ((*it)->HasPower()) {
                    PowerBall* powerball = (*it)->GetPowerBall();
                    powers.push_back(powerball);
                }

                it = bricks.erase(it);
            }
            else {
                int newInd = (*it)->GetSpriteIndex() + 1;
                (*it)->SetSpriteIndex(newInd);
                ++it;
            }
        } else 
            ++it;
    }

    for (int i = 0; i < powers.size(); ++i) {
        int powerX = powers[i]->GetX();
        int powerY = powers[i]->GetY();

        if (powerY + POWERBALL_HEIGHT > app->GetWindowH()) {
            powers.erase(powers.begin() + i);
        } else {
            powerY += POWERBALL_INIT_SPEED + (rand() % 3);

            powers[i]->SetPosition(powerX, powerY);
            powers[i]->SetCollider();

            SDL_bool* inters = powers[i]->Intersects(player);
            if (inters[0] == SDL_TRUE) {
                activatePower(powers[i]->GetPower()); 
                powers.erase(powers.begin() + i);
            }
        }
    }
}

void wonUpdateHandler() {
    int ballX = ball->GetX();
    int ballY = ball->GetY();

    if (ballX < 0 || ballX + ball->GetWidth() > app->GetWindowW()) {
        gameState->ballXDir *= -1;
        ballX += gameState->ballSpeed * gameState->ballXDir;
    }
    if (ballY < 0) {
        gameState->ballYDir *= -1;
        ballY += gameState->ballSpeed * gameState->ballYDir;
    }
    if (ballY > app->GetWindowH()) {
        gameState->lives--;
        if (gameState->lives > 0) {
            gameState->ballYDir *= -1; 
            gameState->ballXDir = rand() % 2 == 0 ? -1 : 1;
            ballX = START_BALL_X;
            ballY = START_BALL_Y;
        }
        //deathSound->PlaySound();
    }

    ballX += gameState->ballSpeed * gameState->ballXDir;
    ballY += gameState->ballSpeed * gameState->ballYDir;

    ball->SetPosition(ballX, ballY);
    ball->SetCollider(ballX, ballY, BALL_WIDTH, BALL_HEIGHT);

    int playerX = player->GetX(); 

    playerX += gameState->playerSpeed * gameState->playerDir;

    if (playerX + player->GetWidth() > app->GetWindowW()) {
        playerX = app->GetWindowH() - player->GetWidth(); 
        gameState->playerDir = 0; 
    } else if (playerX < 0) {
        playerX = 0;
        gameState->playerDir = 0; 
    }

    player->SetPosition(playerX, START_PLAYER_Y); 
    player->SetCollider(COLL_LEFT, playerX, START_PLAYER_Y, 1, 20);
    player->SetCollider(COLL_RIGHT, playerX + PLAYER_WIDTH, START_PLAYER_Y, 1, 20);
    player->SetCollider(COLL_TOP, playerX, START_PLAYER_Y, 100, 1);

    SDL_bool* playerInter = player->Intersects(ball);
    if (playerInter[COLL_LEFT] == SDL_TRUE) {
        if (gameState->ballXDir == 1)
            gameState->ballXDir *= -1;
        gameState->ballYDir = -1; 
    } else if (playerInter[COLL_RIGHT] == SDL_TRUE) {
        if (gameState->ballXDir == -1)
            gameState->ballXDir *= -1;
        gameState->ballYDir = -1; 
    } else if (playerInter[COLL_TOP] == SDL_TRUE)
        gameState->ballYDir = -1;
}

void pausedUpdateHandler() {

}

void menuUpdateHandler() {

}

void lostUpdateHandler() {
    int lostMessageY = lostMessage->GetY();
    int lostWrapperY = lostWrapper->GetY();

    int newWrapperY = lostWrapperY - LOST_WRAPPER_SPEED;
    if (lostWrapperY - LOST_WRAPPER_SPEED > 0) {
        lostWrapper->SetPosition(START_LOST_X, newWrapperY);
        highscoreMessage->SetPosition(HIGHSCORE_MESSAGE_X, newWrapperY + HIGHSCORE_MESSAGE_Y_OFFSET);
        scoreMessage->SetPosition(SCORE_MESSAGE_X, newWrapperY + SCORE_MESSAGE_Y_OFFSET);
        highscore->SetPosition(HIGHSCORE_X, newWrapperY + HIGHSCORE_Y_OFFSET);
        score->SetPosition(SCORE_X, newWrapperY + SCORE_Y_OFFSET);
        againMessage->SetPosition(AGAIN_X, newWrapperY + AGAIN_Y_OFFSET);
        cross->SetPosition(CROSS_X, newWrapperY + CROSS_Y_OFFSET);
    }
    if (lostMessageY + LOST_MESSAGE_SPEED < 90)
        lostMessage->SetPosition(LOST_MESSAGE_X, lostMessageY + LOST_MESSAGE_SPEED);
}

void HandleUpdate() {
    //std::cout << "start update" << std::endl;
    switch (gameState->state) {
        case State::START:
            startUpdateHandler();
            break;
        case State::PLAYING:
            playingUpdateHandler();
            break;
        case State::WON:
            wonUpdateHandler(); 
            break;
        case State::PAUSED:
            pausedUpdateHandler();
            break;
        case State::LEVEL:
            break;
        case State::MENU: 
            menuUpdateHandler();
            break;
        case State::LOST:
            lostUpdateHandler();
            break;
    }
    //std::cout << "end update" << std::endl;
}

// render handlers
void startRenderHandler() {
    SDL_SetRenderDrawColor(app->GetRenderer(), 0xFF, 0xAB, 0xC7, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(app->GetRenderer());

    gameLogo->Render(app->GetRenderer());
    sCollider->Render();

    DynamicText start(ASSET_FONT1_FILEPATH, 100); 
    start.DrawText(app->GetRenderer(), "to start", sCollider->GetX() + sCollider->GetWidth() + 20, sCollider->GetY() + sCollider->GetHeight() / 2 - 20, 200, 40, 0xFF, 0x2C, 0x89);

    ball->Render(); 
}

void playingRenderHandler() {
    SDL_SetRenderDrawColor(app->GetRenderer(), 0xFF, 0xAB, 0xC7, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(app->GetRenderer());

    std::string scoreStr = std::to_string(gameState->score);
    DynamicText score(ASSET_FONT1_FILEPATH, 250); 
    score.DrawText(app->GetRenderer(), scoreStr.c_str(), app->GetWindowW() / 2 - 100, app->GetWindowH() / 2 - 20, 200, 100, 0xFF, 0x2C, 0x89);
    DynamicText levelName(ASSET_FONT1_FILEPATH, 200); 
    levelName.DrawText(app->GetRenderer(), gameState->level.name.c_str(), app->GetWindowW() / 2 - 100, app->GetWindowH() / 2 + 80, 200, 50, 255, 203, 221);
    DynamicText lives(ASSET_FONT1_FILEPATH, 100); 
    lives.DrawText(app->GetRenderer(), "Lives: ", 5, app->GetWindowH() - 30, 100, 30, 255, 203, 221);
    DynamicText reset(ASSET_FONT1_FILEPATH, 100); 
    reset.DrawText(app->GetRenderer(), "R - reset", app->GetWindowW() - 120, app->GetWindowH() - 30, 120, 30, 255, 203, 221);
    DynamicText pause(ASSET_FONT1_FILEPATH, 100); 
    pause.DrawText(app->GetRenderer(), "P - pause", app->GetWindowW() - 260, app->GetWindowH() - 30, 120, 30, 255, 203, 221);

    for (int i = 0; i < gameState->lives; ++i) {
        heart->SetPosition(105 + i * 30, app->GetWindowH() - 30);
        heart->SetDimensions(25, 25);
        heart->Render(app->GetRenderer());
    }
    int powerBarW = gameState->activePowers.size() * POWERLOGO_SIZE + (5 * (gameState->activePowers.size() - 1)); // 5 is the margin 
    int powerBarH = POWERLOGO_SIZE; 

    for (int i = 0; i < gameState->activePowers.size(); ++i) {
        gameState->activePowers[i].textRect->SetDimensions(POWERLOGO_SIZE, POWERLOGO_SIZE); 
        gameState->activePowers[i].textRect->SetPosition(((app->GetWindowW() - powerBarW) / 2) + i * (POWERLOGO_SIZE + 5), START_PLAYER_Y + PLAYER_SPRITE_HEIGHT + 5); 
        gameState->activePowers[i].textRect->Render(app->GetRenderer());
    }
    for (int i = 0; i < powers.size(); ++i) {
        powers[i]->Render();
    }
    for (auto it = bricks.begin(); it != bricks.end(); ++it)
        (*it)->Render();

    player->Render();
    ball->Render();

    if (gameState->lives == 0) {
        SDL_Surface* sshot = SDL_CreateRGBSurface(0, app->GetWindowW(), app->GetWindowH(), 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
        SDL_RenderReadPixels(app->GetRenderer(), NULL, SDL_PIXELFORMAT_ARGB8888, sshot->pixels, sshot->pitch);
        gameState->snapshot = SDL_CreateTextureFromSurface(app->GetRenderer(), sshot);
        SDL_SetTextureColorMod(gameState->snapshot, 160, 160, 160);
    }
}

void wonRenderHandler() {
    SDL_SetRenderDrawColor(app->GetRenderer(), 0xFF, 0xAB, 0xC7, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(app->GetRenderer());

    std::string scoreStr = std::to_string(gameState->score);
    DynamicText score(ASSET_FONT1_FILEPATH, 250); 
    score.DrawText(app->GetRenderer(), scoreStr.c_str(), app->GetWindowW() / 2 - 100, app->GetWindowH() / 2, 200, 100, 255, 203, 221);
    DynamicText levelName(ASSET_FONT1_FILEPATH, 200); 
    levelName.DrawText(app->GetRenderer(), gameState->level.name.c_str(), app->GetWindowW() / 2 - 100, app->GetWindowH() / 2 + 80, 200, 50, 255, 203, 221);
    DynamicText lives(ASSET_FONT1_FILEPATH, 100); 
    lives.DrawText(app->GetRenderer(), "Lives: ", 5, app->GetWindowH() - 30, 100, 30, 255, 203, 221);

    for (int i = 0; i < gameState->lives; ++i) {
        heart->SetPosition(105 + i * 30, app->GetWindowH() - 30);
        heart->SetDimensions(25, 25);
        heart->Render(app->GetRenderer());
    }
    if (gameState->lives <= 0) {
        DynamicText smile(ASSET_FONT1_FILEPATH, 100); 
        smile.DrawText(app->GetRenderer(), ": )", 110, app->GetWindowH() - 30, 15, 30, 255, 203, 221);
    }

    int powerBarW = gameState->activePowers.size() * POWERLOGO_SIZE + (5 * (gameState->activePowers.size() - 1)); // 5 is the margin 
    int powerBarH = POWERLOGO_SIZE; 

    for (int i = 0; i < gameState->activePowers.size(); ++i) {
        gameState->activePowers[i].textRect->SetDimensions(POWERLOGO_SIZE, POWERLOGO_SIZE); 
        gameState->activePowers[i].textRect->SetPosition(((app->GetWindowW() - powerBarW) / 2) + i * (POWERLOGO_SIZE + 5), START_PLAYER_Y + PLAYER_SPRITE_HEIGHT + 5); 
        gameState->activePowers[i].textRect->Render(app->GetRenderer());
    }
    DynamicText you(ASSET_FONT1_FILEPATH, 250);
    you.DrawText(app->GetRenderer(), "YOU", (app->GetWindowW() - 400) / 2, 0, 400, 150, 255, 203, 221);
    DynamicText won(ASSET_FONT1_FILEPATH, 250);
    won.DrawText(app->GetRenderer(), "WON", (app->GetWindowW() - 400) / 2, 110, 400, 150, 255, 203, 221);
    DynamicText reset(ASSET_FONT1_FILEPATH, 100);
    reset.DrawText(app->GetRenderer(), "press R to reset", (app->GetWindowW() - 300) / 2, 233, 300, 30, 0xF5, 0x70, 0x9E);

    player->Render();
    ball->Render();
}

void pausedRenderHandler() {
    SDL_RenderCopy(app->GetRenderer(), gameState->snapshot, NULL, NULL);
    mKey->Render(app->GetRenderer());

    DynamicText menu(ASSET_FONT1_FILEPATH, 100); 
    menu.DrawText(app->GetRenderer(), "to go to menu", mKey->GetX() + mKey->GetWidth() + 20, mKey->GetY() + mKey->GetHeight() / 2 - 10, 265, 30, 0xFF, 0x2C, 0x89);
    lKey->Render(app->GetRenderer());
    DynamicText level(ASSET_FONT1_FILEPATH, 100); 
    level.DrawText(app->GetRenderer(), "to choose level", lKey->GetX() + lKey->GetWidth() + 20, lKey->GetY() + lKey->GetHeight() / 2 - 10, 260, 30, 0xFF, 0x2C, 0x89);
    pKey->Render(app->GetRenderer());
    DynamicText pause(ASSET_FONT1_FILEPATH, 100); 
    pause.DrawText(app->GetRenderer(), "to resume", pKey->GetX() + pKey->GetWidth() + 20, pKey->GetY() + pKey->GetHeight() / 2 - 10, 200, 30, 0xFF, 0x2C, 0x89);
}

void levelRenderHandler() {

}

void menuRenderHandler() {

}

void lostRenderHandler() {
    // background dimmed down image
    SDL_RenderCopy(app->GetRenderer(), gameState->snapshot, NULL, NULL); 
    
    lostWrapper->Render(app->GetRenderer());
    lostMessage->DrawText(app->GetRenderer(), "YOU LOST", 0xFE, 0x4E, 0x9C);
    highscoreMessage->DrawText(app->GetRenderer(), "HIGHSCORE", 0xFF, 0x91, 0xB7);
    scoreMessage->DrawText(app->GetRenderer(), "SCORE", 0xFF, 0x91, 0xB7);
    highscore->DrawText(app->GetRenderer(), std::to_string(gameState->level.bestScore), 0xFF, 0x6C, 0xAD);
    score->DrawText(app->GetRenderer(), std::to_string(gameState->score), 0xFF, 0x6C, 0xAD);
    againMessage->DrawText(app->GetRenderer(), "PRESS TO PLAY AGAIN", 255, 255, 255);

    if (gameState->isHighscore) {
        cross->Render(app->GetRenderer());
    }
}

void HandleRendering() {
    //std::cout << "start render" << std::endl;
    // Draws the background
    switch (gameState->state) {
        case State::START:
            startRenderHandler();
            break;
        case State::PLAYING:
            playingRenderHandler();
            break;
        case State::WON:
            wonRenderHandler();
            break;
        case State::PAUSED:
            pausedRenderHandler();
            break;
        case State::LEVEL: 
            levelRenderHandler();
        case State::MENU: 
            menuRenderHandler(); 
            break;
        case State::LOST:
            lostRenderHandler();
            break;
    }
}



int main() {
    srand((unsigned) time(NULL));

    // app config
    app = new SDLApp(SDL_INIT_VIDEO | SDL_INIT_AUDIO, TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT); 
    app->SetFrameRate(90);

    // game config
    LevelReader::GetInstance().LoadScores(ASSET_SCORES_FILEPATH);
    gameState = new GameState; 
    gameState->playerDir = 0;
    gameState->ballXDir = -1; 
    gameState->ballYDir = rand() % 2 == 0 ? -1 : 1;
    gameState->playerSpeed = START_PLAYER_SPEED;
    gameState->ballSpeed = START_BALL_SPEED;
    gameState->score = 0; 
    gameState->level = LevelReader::GetInstance().LoadLevel(ASSET_DEFAULT_LEVEL_FILEPATH);
    gameState->state = State::START;
    gameState->lives = 3; 
    gameState->isHighscore = false;
    heart = new TexturedRectangle(app->GetRenderer(), ASSET_HEART_FILEPATH);
    cross = new TexturedRectangle(app->GetRenderer(), ASSET_CROSS_FILEPATH);
    cross->SetPosition(CROSS_X, CROSS_Y);
    cross->SetDimensions(app->GetWindowW(), app->GetWindowH());

    // start screen config
    gameLogo = new TexturedRectangle(app->GetRenderer(), ASSET_LOGO_FILEPATH);
    gameLogo->SetDimensions(450, 150);
    gameLogo->SetPosition(25, 100);

    sCollider = new GameEntity(app->GetRenderer());
    sCollider->AddTexturedComponent(ASSET_SKEY_FILEPATH);
    sCollider->SetPosition(START_KEY_X, START_KEY_Y);
    sCollider->SetDimensions(START_KEY_WIDTH, START_KEY_HEIGHT);
    sCollider->AddCollider();
    sCollider->SetCollider(COLL_LEFT, START_KEY_X, START_KEY_Y, 1, START_KEY_HEIGHT); 
    sCollider->AddCollider();
    sCollider->SetCollider(COLL_TOP, START_KEY_X, START_KEY_Y, START_KEY_WIDTH, 1); 
    sCollider->AddCollider();
    sCollider->SetCollider(COLL_RIGHT, START_KEY_X + START_KEY_WIDTH, START_KEY_Y, 1, START_KEY_HEIGHT); 
    sCollider->AddCollider();
    sCollider->SetCollider(COLL_BOT, START_KEY_X, START_KEY_Y + START_KEY_HEIGHT, START_KEY_WIDTH, 1); 

    // paused screen config
    pKey = new TexturedRectangle(app->GetRenderer(), ASSET_PKEY_FILEPATH);
    pKey->SetDimensions(100, 100);
    pKey->SetPosition(60, 300);
    mKey = new TexturedRectangle(app->GetRenderer(), ASSET_MKEY_FILEPATH);
    mKey->SetDimensions(100, 100);
    mKey->SetPosition(60, 75);
    lKey = new TexturedRectangle(app->GetRenderer(), ASSET_LKEY_FILEPATH);
    lKey->SetDimensions(100, 100);
    lKey->SetPosition(60, 187);

    // lost screen config
    lostWrapper = new TexturedRectangle(app->GetRenderer(), ASSET_LOSTWRAPPER_FILEPATH);
    lostWrapper->SetPosition(START_LOST_X, START_LOST_Y);
    lostWrapper->SetDimensions(app->GetWindowW(), app->GetWindowH());
    highscoreMessage = new DynamicText(ASSET_FONT1_FILEPATH, 200);
    highscoreMessage->SetPosition(HIGHSCORE_MESSAGE_X, START_LOST_Y + HIGHSCORE_MESSAGE_Y_OFFSET);
    highscoreMessage->SetDimensions(HIGHSCORE_MESSAGE_W, HIGHSCORE_MESSAGE_H);
    scoreMessage = new DynamicText(ASSET_FONT1_FILEPATH, 200);
    scoreMessage->SetPosition(SCORE_MESSAGE_X, START_LOST_Y + SCORE_MESSAGE_Y_OFFSET);
    scoreMessage->SetDimensions(SCORE_MESSAGE_W, SCORE_MESSAGE_H);
    highscore = new DynamicText(ASSET_FONT1_FILEPATH, 200);
    highscore->SetPosition(HIGHSCORE_X, START_LOST_Y + HIGHSCORE_Y_OFFSET);
    highscore->SetDimensions(HIGHSCORE_W, HIGHSCORE_H);
    score = new DynamicText(ASSET_FONT1_FILEPATH, 200);
    score->SetPosition(SCORE_X, START_LOST_Y + SCORE_MESSAGE_Y_OFFSET);
    score->SetDimensions(SCORE_W, SCORE_H);
    againMessage = new DynamicText(ASSET_FONT1_FILEPATH, 200);
    againMessage->SetPosition(AGAIN_X, START_LOST_Y + AGAIN_Y_OFFSET);
    againMessage->SetDimensions(AGAIN_W, AGAIN_H);
    lostMessage = new DynamicText(ASSET_FONT1_FILEPATH, 100);
    lostMessage->SetPosition(LOST_MESSAGE_X, LOST_MESSAGE_Y);
    lostMessage->SetDimensions(LOST_MESSAGE_W, LOST_MESSAGE_H);

    // entities
    ball = new GameEntity(app->GetRenderer());
    ball->AddTexturedComponent(ASSET_BALL_FILEPATH);
    ball->AddCollider();
    ball->SetPosition((app->GetWindowW() - BALL_WIDTH) / 2, START_BALL_Y);
    ball->SetDimensions(BALL_WIDTH, BALL_HEIGHT);

    player = new GameEntity(app->GetRenderer());
    player->AddTexturedComponent(ASSET_PLAYER_FILEPATH);
    player->AddCollider();
    player->AddCollider();
    player->AddCollider();
    player->SetPosition((app->GetWindowW() - PLAYER_WIDTH) / 2, START_PLAYER_Y);  
    player->SetDimensions(PLAYER_WIDTH, PLAYER_HEIGHT);

    for (int x = 0; x < sizeof(gameState->level.shape) / sizeof(gameState->level.shape[0]); ++x) 
        for (int y = 0; y < sizeof(gameState->level.shape[0]) / sizeof(gameState->level.shape[0][0]); ++y)
            if (gameState->level.shape[x][y] > 0) {
                Brick* brick = new Brick(app->GetRenderer(), gameState->level.shape[x][y], gameState->level.powers[x][y]);
                if (gameState->level.shape[x][y] == 3) {
                    brick->AddTexturedComponent(ASSET_BRICK3_FILEPATH);
                    brick->AddTexturedComponent(ASSET_BRICK2_FILEPATH);
                    brick->AddTexturedComponent(ASSET_BRICK1_FILEPATH);
                } else if (gameState->level.shape[x][y] == 2) {
                    brick->AddTexturedComponent(ASSET_BRICK2_FILEPATH);
                    brick->AddTexturedComponent(ASSET_BRICK1_FILEPATH);
                } else {
                    brick->AddTexturedComponent(ASSET_BRICK1_FILEPATH);
                }

                brick->AddCollider();
                brick->AddCollider();
                brick->AddCollider();
                brick->AddCollider();
                int bx = y * BRICK_WIDTH; 
                int by = x * BRICK_SPRITE_HEIGHT;
                int bw = BRICK_WIDTH;
                int bh = BRICK_HEIGHT;
                int ch = BRICK_SPRITE_HEIGHT;
                brick->SetPosition(bx, by);
                brick->SetDimensions(bw, bh);
                brick->SetCollider(COLL_LEFT, bx, by, 1, ch);
                brick->SetCollider(COLL_RIGHT, bx + BRICK_WIDTH, by, 1, ch);
                brick->SetCollider(COLL_TOP, bx, by, bw, 1);
                brick->SetCollider(COLL_BOT, bx, by + BRICK_SPRITE_HEIGHT, bw, 1);
                bricks.push_back(brick);
            }

    // sounds
    deathSound = new Sound(ASSET_SOUND_DEATH_FILEPATH);
    deathSound->SetUpDevice(); 

    // loop callbacks
    app->SetEventCallback(HandleEvents);
    app->SetUpdateCallback(HandleUpdate);
    app->SetRenderCallback(HandleRendering);

    //SDL_Delay(1000);
    app->RunLoop();

    delete ball; 
    delete player; 
    for (auto it = bricks.begin(); it != bricks.end(); ++it) 
        delete *it;
    delete deathSound;
    delete app; 
    return 0; 
};

