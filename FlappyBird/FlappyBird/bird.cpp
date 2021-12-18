//
//  bird.cpp
//  FlappyBird
//
//  Created by Tsznok Wong on 17/9/15.
//  Copyright (c) 2015 Tsznok Wong. All rights reserved.
//
#include "flap.h"
#include <SDL2_image/SDL_image.h>
#include <iostream>
#include <cmath>
#define GRAVITY 9.81
Bird::Bird(SDL_Renderer *renderTarget, std::string filePath, int x,int y, int framesX, int framesY){
    SDL_Surface *surface = IMG_Load(filePath.c_str());
    if(surface == NULL)
        std::cout << "Image loading Error: " << SDL_GetError() << std::endl;
    else{
        texture = SDL_CreateTextureFromSurface(renderTarget, surface);
        SDL_SetTextureColorMod(texture, 128, 255, 255);
        if(texture == NULL)
            std::cout << "Error: " << std::endl;
    }
    SDL_FreeSurface(surface);
    
    SDL_QueryTexture(texture, NULL, NULL, &cropRect.w, &cropRect.h);
    
    positionRect.w = x;
    positionRect.h = y;
    
    textureWidth = cropRect.w;
    cropRect.w /= framesX;
    cropRect.h /= framesY;
    
    frameWidth = positionRect.w = cropRect.w;
    frameHeight = positionRect.h = cropRect.h;
    
    isActive = false;
    
    static int playerNumber = 0;
    playerNumber++;
    if(playerNumber == 1){
        keys[0] = SDL_SCANCODE_SPACE;
    }
    else{
        keys[0] = SDL_SCANCODE_ESCAPE;
    }
}
Bird::~Bird(){
    SDL_DestroyTexture(texture);
}
void Bird::Update(float delta, const Uint8 *keyState){
    isActive = true;
    if(keyState[keys[0]]){
        moveSpeed += rand()%10+10;
    }
    else {
        moveSpeed -= GRAVITY * delta;
        positionRect.h += moveSpeed * delta;
    }
    if(isActive){
        frameCounter += delta;
        if(frameCounter >= 0.25f){
            frameCounter = 0;
            cropRect.w += frameWidth;
            if(cropRect.w >= textureWidth)
                cropRect.w = 0;
        }
    }
    else{
        frameCounter = 0;
        cropRect.w = frameWidth;
    }
}
void Bird::Draw(SDL_Renderer *renderTarget){
    SDL_RenderCopy(renderTarget, texture, &cropRect, &positionRect);
}









