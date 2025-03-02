// LIBRARY IMPORTS
#include <stdio.h>
#include <SDL2/SDL.h>
#include <math.h>

// LOCAL IMPORTS
#include "include/main.h"
#include "include/player.h"

//-----------------------------------------------------------------------------------------------//

const double FPS = 60.0;
const double FRAME_TIME = 1000.0 / FPS; // In MS
const int WINDOW_WIDTH = 1200;
const int WINDOW_HEIGHT = 900;
const double PI = 3.14159265358979323846;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

int gameRunning = 0;
int lastFrame = 0;

//-----------------------------------------------------------------------------------------------//

int initialize_window(void){

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
        fprintf(stderr, "Error initialising SDL\n");
        return 0;
    }

    window = SDL_CreateWindow(
        NULL,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_BORDERLESS
    );

    if (!window){
        fprintf(stderr, "Error creating SDL window\n");
        return 0;
    }

    // -1 for default driver, 0 for no flags
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer){
        fprintf(stderr, "Error creating SDL renderer\n");
        return 0;
    }

    return 1;
}

//-----------------------------------------------------------------------------------------------//

void processInput(){

    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type){
        case SDL_QUIT:
            gameRunning = 0;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE){
                gameRunning = 0;
            }
            break;
    }

    playerInput(event);

}

//-----------------------------------------------------------------------------------------------//

void setup(){

    for (int i = 0; i < 360; i++){
        M.cos[i] = cos(i / 180.0 * M_PI);
        M.sin[i] = sin(i / 180.0 * M_PI);
    }

    playerSetup();

}

//-----------------------------------------------------------------------------------------------//

void update(){

    /* ONLY NEEDED FOR A CAPPED FRAME RATE
    int waitTime = FRAME_TIME - (SDL_GetTicks() / lastFrame);
    if (waitTime > 0 && waitTime < FRAME_TIME){ SDL_Delay(waitTime); }
    */

    float deltaTime = (SDL_GetTicks() - lastFrame) / 1000.0f;

    lastFrame = SDL_GetTicks();

    playerUpdate(deltaTime);

}

//-----------------------------------------------------------------------------------------------//

void render(){

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Calls to draw objects to the screen
    //playerRender(renderer);

    int wx[4], wy[4], wz[4]; float CS = M.cos[player.angleH], SN = M.sin[player.angleH];

    int x1 = 40 - player.x; int y1 = 10 - player.y;
    int x2 = 40 - player.x; int y2 = 290 - player.y;

    wx[0] = x1 * CS - y1 * SN;
    wx[1] = x2 * CS - y2 * SN;

    wy[0] = y1 * CS + x1 * SN;
    wy[1] = y2 * CS + x2 * SN;

    wz[0] = 0 - player.z + ((player.angleV * wy[0]) / 32.0);
    wz[1] = 0 - player.z + ((player.angleV * wy[1]) / 32.0);

    wx[0] = wx[0] * 200 / wy[0] + (WINDOW_WIDTH / 2);
    wy[0] = wz[0] * 200 / wy[0] + (WINDOW_HEIGHT / 2);
    wx[1] = wx[1] * 200 / wy[1] + (WINDOW_WIDTH / 2);
    wy[1] = wz[1] * 200 / wy[1] + (WINDOW_HEIGHT / 2);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    if (wx[0] > 0 && wx[0] < WINDOW_WIDTH && wy[0] > 0 && wy[0] < WINDOW_HEIGHT){
        SDL_RenderDrawPoint(renderer, wx[0], wy[0]);
    }
    if (wx[1] > 0 && wx[1] < WINDOW_WIDTH && wy[1] > 0 && wy[1] < WINDOW_HEIGHT){
        SDL_RenderDrawPoint(renderer, wx[1], wy[1]);
    }

    SDL_RenderPresent(renderer);

}

//-----------------------------------------------------------------------------------------------//

void destroyWindow(){

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

}

//-----------------------------------------------------------------------------------------------//

int main(){

    gameRunning = initialize_window();

    setup();

    while (gameRunning){
        processInput();
        update();
        render();
    }

    destroyWindow();

    return 0;

}

//-----------------------------------------------------------------------------------------------//
