#pragma once

#include <SDL.h>
#include "btn.h"

struct SelectionMenu{
    SDL_Rect rect;

    int btn_count;
    struct Btn *btns;
    
    SDL_Rect curr_item;
    int curr_item_id;
    int isItemSelected;


    int eventUpdatedThisFrame;

    void (*event)(struct SelectionMenu *_);
    void (*update)(struct SelectionMenu *_);
    void (*callbackManager)(struct SelectionMenu *_,int id);
    void (*addBtn)(struct SelectionMenu *_,int id);
    void (*render)(struct SelectionMenu _);
};

extern const struct SelectionMenuClass {
    struct SelectionMenu (*new)();
} SelectionMenu;
