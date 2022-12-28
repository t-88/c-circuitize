#pragma once
#include <SDL.h>


struct Wire {

    SDL_Rect rect;
    SDL_Point p1 , p2;
    SDL_Color currColor;

    int input_id;
    int output_id;

    float angle;
    int isMouseOverit;
    int requestToDelete;

    void (*render) (struct Wire _);
    void (*update) (struct Wire *_);
    void (*event) (struct Wire *_);
};

extern const struct WireClass {
    struct Wire (*new)(SDL_Rect,SDL_Rect,int,int);
} Wire;

