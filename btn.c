#include <SDL.h>
#include "consts.h"
#include "utility.h"
#include "btn.h"





static void btn__render(struct Btn _) {
    setRenderDrawColor(RED);
    SDL_RenderFillRect(renderer,&_.rect);
}
static void btn__event(struct Btn *_) {
    if(isLeftMouseDown && AABB(mouse_rect,_->rect)) {
        _->isClicked =  true;
        _->callback(_->id);
    }
}
static void btn__update(struct Btn *_) {
       
}
static void btn__after_update(struct Btn *_) {
    _->isClicked = false;
}



static struct Btn btn__new(int x , int y,int id) {
    
    struct Btn _;
    
    _.rect.x = x;_.rect.y = y;_.rect.w = 20;_.rect.h = 20;
    
    _.render = &btn__render;    
    _.update = &btn__update;    
    _.event =  &btn__event;   
    _.afterUpdate = &btn__after_update;

    _.isClicked = false;
    _.id = id;
    return _;
}



const struct BtnClass Btn = {.new = &btn__new};