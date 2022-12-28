#include <SDL.h>
#include "consts.h"
#include "selection_menu.h"





static void selection_menu_render(struct SelectionMenu _) {
    setRenderDrawColor(WHITE);
    SDL_RenderFillRect(renderer,&_.rect);

    for (size_t i = 0; i < _.btn_count; i++){
        _.btns[i].render(_.btns[i]);
    }

    if(_.isItemSelected) {
        
        SDL_SetRenderDrawColor(renderer,0,255,255,255);
        _.curr_item.x = mouse_rect.x - _.curr_item.w / 2;
        _.curr_item.y = mouse_rect.y - _.curr_item.h / 2;

        SDL_RenderFillRect(renderer,&_.curr_item);
    }
}
static void selection_menu_event(struct SelectionMenu *_) {
    for (size_t i = 0; i < _->btn_count; i++){
        _->btns[i].event(&_->btns[i]);
    }

    switch (event.type)
    {
    case SDL_KEYDOWN:
        switch (event.key.keysym.scancode)
        {
        case SDL_SCANCODE_ESCAPE:
            _->isItemSelected = false;
            _->curr_item_id = 1;
            break;
        
        default:
            break;
        }
        break;
    
    default:
        break;
    }

    if(isLeftMouseDown && _->isItemSelected && !_->eventUpdatedThisFrame) {
        _->isItemSelected = false;
        switch (_->curr_item_id)
        {
        case 1:
            wire_manager.addInputPort(&wire_manager,mouse_rect.x,mouse_rect.y,30,30);
        break;
        case 2:
            wire_manager.addOutputPort(&wire_manager,mouse_rect.x,mouse_rect.y,20,20);
        break;
        case 3:
            addGate(mouse_rect.x,mouse_rect.y,50,50,ConditionType_and);
        break;
        case 4:
            addGate(mouse_rect.x,mouse_rect.y,50,50,ConditionType_or);
        break;
        case 5:
            addGate(mouse_rect.x,mouse_rect.y,50,50,ConditionType_not);
        break;        
        default:
            break;
        }
    }
}

static void selection_menu_callback_manager(int id) {
        selection_menu.eventUpdatedThisFrame = true;
        selection_menu.isItemSelected = true;
        selection_menu.curr_item_id = id;

    switch (id)
    {
    case 1:
        selection_menu.isItemSelected = true;
        selection_menu.curr_item_id = 1;
    break;
    case 2:
        selection_menu.curr_item_id = 2;
    break;
    default:
        break;
    }
}
static void selection_menu_add_btn(struct SelectionMenu *_,int id) {
    _->btn_count++;
    _->btns = realloc(_->btns,_->btn_count * sizeof(struct Btn));

    struct Btn btn = Btn.new(_->rect.x + 20 * _->btn_count + ((_->btn_count - 1) * 10),_->rect.y + 10,id);
    btn.callback = &selection_menu_callback_manager;
    _->btns[_->btn_count - 1]= btn;
}


static void selection_menu_update(struct SelectionMenu *_) {
    for (size_t i = 0; i < _->btn_count; i++){
        _->btns[i].update(&_->btns[i]);
    }

    for (size_t i = 0; i < _->btn_count; i++){
        _->btns[i].afterUpdate(&_->btns[i]);
    }
    _->eventUpdatedThisFrame = false;
}





static struct SelectionMenu selection_menu_new() {
    
    struct SelectionMenu _;
    _.rect.x = 0;_.rect.y = HIGHT - 50;_.rect.w = WIDTH;_.rect.h = 100;
    _.render = &selection_menu_render;    
    _.update = &selection_menu_update;    
    _.event =  &selection_menu_event;   
    _.addBtn =  &selection_menu_add_btn;   




    _.isItemSelected= false;
    SDL_Rect r = {0,0,30,30};
    _.curr_item = r;

    _.btn_count = 0;
    _.eventUpdatedThisFrame = false;
    _.btns = malloc(0);

    _.addBtn(&_,1);
    _.addBtn(&_,2);
    _.addBtn(&_,3);
    _.addBtn(&_,4);
    _.addBtn(&_,5);

    return _;
}



const struct SelectionMenuClass SelectionMenu = {.new = &selection_menu_new};