#include <SDL.h>
#include "port.h"
#include "consts.h"



static void input_port__render(struct InputPort _) {
    _.base.render(_.base);
}
static void input_port__event(struct InputPort *_) {
    _->base.event(&(_->base));
    if(AABB(mouse_rect,_->base.rect) && isRightMouseDown) {
        _->base.isActive = (_->base.isActive + 1) % 2; 
    }
}
static void input_port__update(struct InputPort *_) {
    _->base.update(&(_->base));

}


static struct InputPort input_port__new(int x , int y , int w , int h) {
    struct InputPort _;
    _.base = Port.new(x,y,w,h);
    _.base.type = PortType_input;
    _.base.activeColor = YELLOW;

    
    _.event = &input_port__event; 
    _.render = &input_port__render; 
    _.update = &input_port__update; 

    return _;
}
const struct InputPortClass InputPort = {.new = input_port__new};
