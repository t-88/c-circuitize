#include <SDL.h>
#include "port.h"
#include "consts.h"



static void output__render(struct OutputPort _) {
    _.base.render(_.base);
}
static void output__event(struct OutputPort *_) {
    _->base.event(&(_->base));

}
static void output__update(struct OutputPort *_) {
    _->base.update(&(_->base));

}


static struct OutputPort output__new(int x , int y , int w , int h) {
    struct OutputPort _;
    _.base = Port.new(x,y,w,h);
    _.base.currColor = RED;
    _.base.type = PortType_output;


    _.event = &output__event; 
    _.render = &output__render; 
    _.update = &output__update; 

    return _;
}
const struct OutputPortClass OutputPort = {.new = output__new};
