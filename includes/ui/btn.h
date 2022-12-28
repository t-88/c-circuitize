#pragma once

#include <SDL.h>
#include "selection_menu.h"

struct Btn{

    SDL_Rect rect;
    int isClicked;
    int id;
    

    void (*event)(struct Btn *_);
    void (*update)(struct Btn *_);
    void (*afterUpdate)(struct Btn *_);
    void (*render)(struct Btn _);
    
    void (*callback)(int id);
};


extern const struct BtnClass {
    struct Btn (*new) (int x , int y,int id);
} Btn;