#pragma once
#include <SDL.h>
#include "port.h"
#include "consts.h"


struct Gate {
    SDL_Rect rect;

    int output_id; 
    int input_port1; 
    int input_port2; 
    int condition;
    SDL_Color mainColor;

    void (*render)(struct Gate _);
    void (*update)(struct Gate *_);
};

extern const struct GateClass {
    struct Gate (*new)(int x , int y,int w , int h, int condition);
} Gate;


struct AndGate { struct Gate base; };
extern const struct AndGateClass { struct AndGate (*new)(int x , int y,int w , int h); } AndGate;

struct OrGate { struct Gate base;};
extern const struct OrGateClass { struct OrGate (*new)(int x , int y,int w , int h); } OrGate;

struct NotGate { struct Gate base;};
extern const struct NotGateClass { struct NotGate (*new)(int x , int y,int w , int h); } NotGate;