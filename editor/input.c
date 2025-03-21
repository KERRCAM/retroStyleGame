// LIBRARY IMPORTS
#include <stdio.h>
#include <SDL2/SDL.h>
#include <math.h>
#include <stdbool.h>

// LOCAL IMPORTS

//-----------------------------------------------------------------------------------------------//

bool wDown = false;
bool aDown = false;
bool sDown = false;
bool dDown = false;

//-----------------------------------------------------------------------------------------------//

void editorInput(SDL_Event event){

    if (event.type == SDL_MOUSEMOTION){
        int x, y;
        SDL_GetMouseState(&x, &y);
        printf("Mouse movement: %i %i\n", x, y);
    }

    if (event.type == SDL_KEYDOWN){
        switch (event.key.keysym.sym){
            case SDLK_w:
                wDown = true;
            break;
            case SDLK_s:
                sDown = true;
            break;
            case SDLK_a:
                aDown = true;
            break;
            case SDLK_d:
                dDown = true;
            break;
        }
    }

    if (event.type == SDL_KEYUP){
        switch (event.key.keysym.sym){
            case SDLK_w:
                wDown = false;
            case SDLK_s:
                sDown = false;
            case SDLK_a:
                aDown = false;
            case SDLK_d:
                dDown = false;
        }
    }

}

//-----------------------------------------------------------------------------------------------//



//-----------------------------------------------------------------------------------------------//
