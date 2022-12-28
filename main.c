#include <SDL.h>
#include <math.h>
#include "consts.h"
#include "utility.h"
#include "wire_manager.h"
#include "port.h"
#include "selection_menu.h"
#include "gate.h"






void init() {
    SDL_Init(SDL_INIT_VIDEO);
    global_state__init();

    wire_manager = WireManager.new();
    selection_menu = SelectionMenu.new(); 
    rule_manager = RuleManager.new();
}

void events() {
    while (SDL_PollEvent(&event))
    {   
        SDL_GetMouseState(&mouse_rect.x,&mouse_rect.y);

        switch (event.type)
        {
            case SDL_QUIT:
                IsGameRunning = 0;
            break;
    
            case SDL_MOUSEBUTTONDOWN:
                switch (event.button.button)
                {
                    case SDL_BUTTON_LEFT: isLeftMouseDown = true; break;
                    case SDL_BUTTON_RIGHT: isRightMouseDown  = true; break;
                }
            break;

        }

        wire_manager.event(&wire_manager);
        selection_menu.event(&selection_menu);

    }


}
void render() {
    setRenderDrawColor(BLACK);
    SDL_RenderClear(renderer);


    wire_manager.render(&wire_manager);

    for (size_t i = 0; i < gate_count; i++){
        gates[i].render(gates[i]);
    }



    selection_menu.render(selection_menu);


    SDL_RenderPresent(renderer);
}
void update() {
    fps_limit_start = SDL_GetPerformanceCounter();

    rule_manager.update(&rule_manager);

    wire_manager.update(&wire_manager);
    selection_menu.update(&selection_menu);

}
void afterUpdate() {




    fps_limit_end = SDL_GetPerformanceCounter();
    dt = (fps_limit_end - fps_limit_start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;
    SDL_Delay(16.666f - dt);
}
void cleanUp() {
    wire_manager.cleanUp(&wire_manager);

    SDL_DestroyTexture(GlobalTexture);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


int main()
{
    init();
    while (IsGameRunning)
    {
        events();
        render();
        update();
        afterUpdate();
        resetEvents();
    }
    cleanUp();
    return 0;
}
