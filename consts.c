#include <SDL.h>
#include "consts.h" 



SDL_Window *window;
SDL_Renderer *renderer;
SDL_Event event;
Uint64 fps_limit_start , fps_limit_end;
float dt;


SDL_Color WHITE;
SDL_Color RED;
SDL_Color BLACK;
SDL_Color YELLOW;


int WIDTH = 602;
int HIGHT = 602;
int IsGameRunning; 


int isMouseDown;
int isRightMouseDown;
int isLeftMouseDown;
SDL_Rect mouse_rect;

struct WireManager wire_manager;
struct SelectionMenu selection_menu;
struct RuleManager rule_manager;


SDL_Texture* GlobalTexture;

struct Gate* gates;
int gate_count;
void addGate(int x , int y , int w , int h, int condition) {
    gate_count++;
    gates = realloc(gates,gate_count * sizeof(struct Gate));

    switch (condition)
    {
    case ConditionType_and :
        gates[gate_count - 1] = AndGate.new(x,y,w,h).base;
        break;
    case ConditionType_or :
        gates[gate_count - 1] = OrGate.new(x,y,w,h).base;
        break;
    case ConditionType_not :
        gates[gate_count - 1] = NotGate.new(x,y,w,h).base;
        break;                
    default:
        break;
    }
}
void global_state__init(){
    SDL_CreateWindowAndRenderer(WIDTH, HIGHT, 0, &window, &renderer);
    IsGameRunning = true;


    WHITE.r  = 255;  WHITE.b= 255;  WHITE.g = 255;  WHITE.a = 255;  
    RED.r  = 255;  RED.b= 0;  RED.g = 0;  RED.a = 255;  
    BLACK.r  = 0;  BLACK.b= 0;  BLACK.g = 0;  BLACK.a = 255;  
    YELLOW.r  = 255;  YELLOW.b= 255;  YELLOW.g = 0;  YELLOW.a = 255;  

    gates = malloc(0);
    gate_count = 0;


    isMouseDown = false; 
    isLeftMouseDown = false;
    mouse_rect.w = 2; mouse_rect.h = 2;


    SDL_Surface *surface =  SDL_CreateRGBSurface(0,600,600,32,0,0,0,0);
    SDL_FillRect(surface,NULL,SDL_MapRGB(surface->format,255,255,255));
    GlobalTexture = SDL_CreateTextureFromSurface(renderer,surface);

    SDL_FreeSurface(surface);
}

void resetEvents() {
    isMouseDown = false;
    isRightMouseDown = false;
    isLeftMouseDown = false;
}

