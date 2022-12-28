#pragma once

#include <SDL.h>
#include "consts.h"

struct Port {
    SDL_Rect rect;
    SDL_Point p1 , p2;
    SDL_Color currColor;
    SDL_Color notActiveColor;
    SDL_Color activeColor;




    int id;
    int type;
    int drawWire;
    int isActive;

    void (*render) (struct Port _);
    void (*update) (struct Port *_);
    void (*event) (struct Port *_);
};



struct InputPort {
    struct Port base;
    void (*render) (struct InputPort _);
    void (*event) (struct InputPort *_);
    void (*update) (struct InputPort *_);
};
struct OutputPort {
    struct Port base;
    void (*render) (struct OutputPort _);
    void (*event) (struct OutputPort *_);
    void (*update) (struct OutputPort *_);
};



extern const struct PortClass {
    struct Port (*new) (int x ,int y,int w ,int h);
} Port;
extern const struct InputPortClass {
    struct InputPort (*new) (int x ,int y,int w ,int h);
} InputPort;
extern const struct OutputPortClass {
    struct OutputPort (*new) (int x ,int y,int w ,int h);
} OutputPort;