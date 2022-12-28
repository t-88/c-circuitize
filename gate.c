#include "gate.h"


static void gate__render(struct Gate _) {
    setRenderDrawColor(_.mainColor);
    SDL_RenderFillRect(renderer,&_.rect);
}

static struct Gate gate__new(int x , int y,int w , int h ,int condition) {
    struct Gate _;
    SDL_Rect rect = {.x = x , .y = y, .w = w , .h = h};
    _.rect = rect;

    _.condition = condition;
    _.render = &gate__render;
    _.mainColor  = WHITE;
    return _;
} 
const struct GateClass Gate = {.new = &gate__new};



static struct AndGate and_gate__new(int x , int y,int w , int h )
{
    struct AndGate _;
    _.base = Gate.new(x , y,w , h,ConditionType_and);
    struct InputPort* ip1 =  wire_manager.addInputPort(&wire_manager,x + w,y + (h - 20) / 2 ,20,20);
    struct OutputPort* op1 =  wire_manager.addOutputPort(&wire_manager,x - 20,y,20,20);
    struct OutputPort* op2 = wire_manager.addOutputPort(&wire_manager,x - 20,y + h - 20 ,20,20);

    SDL_Color gray = {125,125,125};
    _.base.mainColor = gray;

    rule_manager.addRule(&rule_manager,op1->base.id,op2->base.id,ip1->base.id,ConditionType_and);

    return _;
}
const struct AndGateClass AndGate = {.new = &and_gate__new};


static struct OrGate or_gate__new(int x , int y,int w , int h )
{
    struct OrGate _;
    _.base = Gate.new(x , y,w , h,ConditionType_or);
    struct InputPort* ip1 =  wire_manager.addInputPort(&wire_manager,x + w,y + (h  - 20) / 2 ,20,20);
    struct OutputPort* op1 =  wire_manager.addOutputPort(&wire_manager,x - 20,y,20,20);
    struct OutputPort* op2 = wire_manager.addOutputPort(&wire_manager,x - 20,y + h - 20 ,20,20);

    SDL_Color c = {200,150,125};
    _.base.mainColor = c;
 
 
    rule_manager.addRule(&rule_manager,op1->base.id,op2->base.id,ip1->base.id,ConditionType_or);

    return _;
}
const struct OrGateClass OrGate = {.new = &or_gate__new};





static struct NotGate not_gate__new(int x , int y,int w , int h )
{
    struct NotGate _;
    _.base = Gate.new(x , y,w , h,ConditionType_not);
    struct InputPort* ip1 =  wire_manager.addInputPort(&wire_manager,x + w,y + (h  - 20) / 2 ,20,20);
    struct OutputPort* op1 = wire_manager.addOutputPort(&wire_manager,x - 20,y + (h - 20) / 2 ,20,20);

    SDL_Color c = {150,200,125};
    _.base.mainColor = c;


    rule_manager.addRule(&rule_manager,op1->base.id,-1,ip1->base.id,ConditionType_not);



    return _;
}

const struct NotGateClass NotGate = {.new = &not_gate__new};