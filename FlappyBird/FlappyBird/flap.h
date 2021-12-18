//
//  flap.h
//  FlappyBird
//
//  Created by Tsznok Wong on 16/9/15.
//  Copyright (c) 2015 Tsznok Wong. All rights reserved.
//
#pragma once
#ifndef FlappyBird_flap_h
#define FlappyBird_flap_h
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <string>

class Bird{
private:
    SDL_Rect cropRect;
    SDL_Texture *texture;
    double moveSpeed;
    double frameCounter;
    int frameWidth, frameHeight;
    int textureWidth;
    bool isActive;
    SDL_Scancode keys[1];
public:
    Bird(SDL_Renderer *renderTarget, std::string filePath, int x,int y, int framesX, int frameY);
    ~Bird();
    
    void Update(float delta, const Uint8 *KeyState);
    void Draw(SDL_Renderer *renderTarget);
    SDL_Rect positionRect;
};

#endif
