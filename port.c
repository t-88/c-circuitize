#include <SDL.h>
#include "port.h"
#include "utility.h"
#include "wire_manager.h"

static void port__render(struct Port _) {
    if((AABB(_.rect,mouse_rect) && _.type != wire_manager.curr_port_type) || wire_manager.curr_port_id == _.id)  {
        SDL_SetRenderDrawColor(renderer,200,120,50,255);
        SDL_Rect hieghligh_rect = {.x = _.rect.x - 5,.y = _.rect.y - 5,.w = _.rect.w + 10,.h = _.rect.h + 10};
        SDL_RenderFillRect(renderer,&hieghligh_rect);
    }


    setRenderDrawColor(_.currColor);
    if(_.drawWire) {
        SDL_RenderDrawLine(renderer,_.p1.x,_.p1.y,_.p2.x,_.p2.y);
    }
    SDL_RenderFillRect(renderer,&_.rect);
}

static void port__update(struct Port* _) {
    if(AABB(_->rect,mouse_rect)) {
        if(isLeftMouseDown ) {
            if(!wire_manager.didUpdateOnePort && wire_manager.ableToSelectPort) {
                
                wire_manager.ableToSelectPort = false;
                wire_manager.didUpdateOnePort = true;
                wire_manager.curr_port_id = _->id;
                wire_manager.curr_port_type = _->type;
                wire_manager.curr_port = _;
            }
            if(!wire_manager.didUpdateOnePort && _->type != wire_manager.curr_port_type) {
                wire_manager.ableToSelectPort = true;
                wire_manager.didUpdateOnePort = true;
                wire_manager.curr_port_type = PortType_none;
                wire_manager.curr_port_id = -1;


                SDL_Point p2 = {.x = mouse_rect.x,.y = mouse_rect.y};
                if(wire_manager.curr_port->type == PortType_input) {
                    wire_manager.addConnection(&wire_manager,wire_manager.curr_port->id,_->id);
                } else {
                    wire_manager.addConnection(&wire_manager,_->id,wire_manager.curr_port->id);
                }

            }
        }
    }

    if(_->isActive) {
        _->currColor = _->activeColor;
    } else {
        _->currColor = _->notActiveColor;
    }
}

static void port__event(struct Port* _) {

}

static struct Port port__new(int x ,int y,int w ,int h) {
    struct Port _;
    SDL_Rect rect = { .x = x , .y = y , .w = w, .h = h};
    SDL_Point p = { .x = -1, .y = -1 };

    _.rect = rect;
    _.p1 = p; _.p2 = p;
    _.id = random();
    _.render = &port__render;
    _.update = &port__update;
    _.event = &port__event;
    
    _.notActiveColor = WHITE;
    _.activeColor = RED;
    _.currColor = WHITE;

    _.drawWire = false;
    _.isActive = false;

    return _;
} 

const struct PortClass Port = { .new = &port__new };
