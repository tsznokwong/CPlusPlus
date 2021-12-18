//
//  main.cpp
//  FlappyBird
//
//  Created by Tsznok Wong on 16/9/15.
//  Copyright (c) 2015 Tsznok Wong. All rights reserved.
//
#include "flap.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <OpenGL/OpenGL.h>

SDL_Texture *LoadTexture(std::string filePath, SDL_Renderer *renderTarget){
    SDL_Texture *texture = nullptr;
    return texture;
}

int main(int argc, const char * argv[]) {
    SDL_Window *window = nullptr;
    SDL_Renderer *renderTarget = nullptr;
    int currentTime = 0;
    int prevTime = 0;
    float delta = 0.0f;
    const Uint8 *keyState;
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
        std::cout << "Video Initialization Error: " << SDL_GetError() << std::endl;
    else{
        window = SDL_CreateWindow("Flappy Bird", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 512, 960, SDL_WINDOW_SHOWN);
        renderTarget = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        Bird bird1(renderTarget, "flappyBird.png", 256, 256, 128, 90);
        if(window == NULL)
            std::cout << "Window creation error:" << SDL_GetError() << std::endl;
        else{
            SDL_UpdateWindowSurface(window);
            bool isRunning = true;
            SDL_Event ev;
            while(isRunning){
                prevTime = currentTime;
                currentTime = SDL_GetTicks();
                delta = (currentTime - prevTime)/1000.0f;
                while(SDL_PollEvent(&ev) != 0){
                    if(ev.type == SDL_QUIT)isRunning=false;
                    /*
                    else if(ev.type == SDL_MOUSEBUTTONUP){
                        if(ev.button.button == SDL_BUTTON_LEFT)
                            ;
                    }*/
                }
                keyState = SDL_GetKeyboardState(NULL);
                bird1.Update(delta, keyState);
                SDL_RenderClear(renderTarget);
                bird1.Draw(renderTarget);
                SDL_RenderPresent(renderTarget);
            }
        }
    }
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderTarget);
    window = nullptr;
    renderTarget = nullptr;
    IMG_Quit();
    SDL_Quit();
    
    return 0;
}
