//
//  main.cpp
//  SDL
//
//  Created by Tsznok Wong on 7/9/15.
//  Copyright (c) 2015 Tsznok Wong. All rights reserved.
//

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
int main(int argc, const char * argv[]) {
    SDL_Window *window = nullptr;
    SDL_Surface *windowSurface = nullptr;
    SDL_Surface *imageSurface = nullptr;
    
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
        std::cout << "Video Initialization Error: " << SDL_GetError() << std::endl;
    else{
        window = SDL_CreateWindow("SDL Coding", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 960, SDL_WINDOW_SHOWN);
        if(window == NULL)
            std::cout << "Window creation error:" << SDL_GetError() << std::endl;
        else{
            //window created
            windowSurface = SDL_GetWindowSurface(window);
            imageSurface = IMG_Load("./Resource/Logo.png");
            if(imageSurface == NULL)
                std::cout << "Image loading Error: " << SDL_GetError() << std::endl;
            else{
                SDL_BlitSurface(imageSurface,NULL,windowSurface,NULL);
                SDL_UpdateWindowSurface(window);
                bool isRunning = true;
                SDL_Event ev;
                while(isRunning){
                    while(SDL_PollEvent(&ev) != 0){
                        if(ev.type == SDL_QUIT)isRunning=false;
                    }
                    SDL_UpdateWindowSurface(window);
                }
            }
            //SDL_Delay(2000);
        }
    }
    SDL_FreeSurface(imageSurface);
    imageSurface=nullptr;
    
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}
