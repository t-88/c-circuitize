#pragma once

#include <SDL.h>
#include "wire_manager.h"
#include "selection_menu.h"
#include "gate.h"
#include "rule_manager.h"





#define true 1
#define false 0


#define PortType_none 0
#define PortType_input 1
#define PortType_output 2

#define ConditionType_and 0
#define ConditionType_or 1
#define ConditionType_not 2


extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern SDL_Event event;
extern Uint64 fps_limit_start , fps_limit_end;
extern float dt;


extern SDL_Color WHITE;
extern SDL_Color RED;
extern SDL_Color BLACK;
extern SDL_Color YELLOW;



extern int WIDTH;
extern int HIGHT;
extern int IsGameRunning; 


extern int isMouseDown;
extern int isRightMouseDown;
extern int isLeftMouseDown;
extern SDL_Rect mouse_rect;


extern struct WireManager wire_manager;
extern struct RuleManager rule_manager;
extern struct SelectionMenu selection_menu;


extern SDL_Texture* GlobalTexture;

extern struct Gate* gates;
extern int gate_count;



extern void addGate(int x , int y , int w , int h, int condition);
extern void global_state__init();
extern void resetEvents();
extern int AABB(SDL_Rect r1 , SDL_Rect r2);



#define setRenderDrawColor(color) SDL_SetRenderDrawColor(renderer,color.r,color.g,color.b,color.a)
#define setRenderDrawScale(scale) SDL_RenderSetScale(renderer,scale,scale)