#include <SDL.h>
#include "wire.h"
#include "utility.h"

static void wire__render(struct Wire _) {
    if(_.isMouseOverit) {
        SDL_SetTextureColorMod(GlobalTexture,255,255,0);
        float border = 2;
        SDL_Rect temp_r = {_.p1.x ,_.p1.y ,_.rect.w + border,_.rect.h + border};
        SDL_Point offset = {-border/2 , -border/2};
        temp_r = MY_calcRotationAndOffsetOfRect(temp_r,NULL,_.angle,&_.p1,&offset);

        MY_DrawRotatedLine(temp_r,&_.p1,_.angle);
    }
    SDL_SetTextureColorMod(GlobalTexture,255,255,255);
    MY_DrawRotatedLine(_.rect,&_.p1,_.angle);

}

static void wire__update(struct Wire* _) {
    SDL_Point mouse_pos = {mouse_rect.x , mouse_rect.y};
    _->isMouseOverit = LinePointCollistion(_->p1,_->p2,mouse_pos,1);

    if(_->isMouseOverit && isRightMouseDown) {
        _->requestToDelete = true;
    }
}

static void wire__event(struct Wire* _) {

}

static struct Wire wire__new(SDL_Rect r1,SDL_Rect r2,int input_id,int output_id) {
    struct Wire _;
    SDL_Point p1 = {.x = r1.x + r1.w / 2  , .y = r1.y + r1.h / 2};
    SDL_Point p2 = {.x = r2.x + r2.w / 2 , .y = r2.y + r2.h / 2  };

    _.p1 = p1; _.p2 = p2; 
    _.angle = SDL_atan2f(p2.y - p1.y ,p2.x - p1.x  ) * 180 /  3.14;
    
    SDL_Rect r = {.x = p1.x,.y = p1.y,.w = MY_CalcDistence(p1,p2),.h = 4};
    r = MY_calcRotationAndOffsetOfRect(r,NULL,_.angle,&p1,NULL);
    _.rect = r;

    _.isMouseOverit = false;
    _.requestToDelete = false;
    _.input_id = input_id;
    _.output_id = output_id;
    

    _.event =  &wire__event;
    _.update = &wire__update;
    _.render = &wire__render;

    return _;
}


const struct  WireClass Wire = {.new = &wire__new};