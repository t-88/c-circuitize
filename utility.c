#include <SDL.h>
#include "utility.h"
#include "consts.h"

float MY_CalcDistence(SDL_Point p1 , SDL_Point p2) {
    return SDL_sqrtf(SDL_fabs(SDL_powf(p1.x - p2.x , 2) + SDL_powf(p1.y - p2.y , 2)));
}


int AABB(SDL_Rect r1 , SDL_Rect r2) {
    return(r1.x + r1.w > r2.x) && (r1.y + r1.h > r2.y) && (r2.y + r2.h > r1.y) && (r2.x + r2.w > r1.x); 
}
int LinePointCollistion(SDL_Point p1 , SDL_Point p2, SDL_Point p,int offset){
    return SDL_fabs((MY_CalcDistence(p,p1) + MY_CalcDistence(p,p2)) - MY_CalcDistence(p1,p2)) <= offset;
}


float multByRotationMatrix(float x , float y, float rotation , int option) {
    // rotation matrix:
    // [ cos(a) -sin(a) ]
    // [ sin(a)  cos(a) ]
    float cosA = SDL_cosf(3.14 * rotation / 180);
    float sinA = SDL_sinf(3.14 * rotation / 180);
    if(option == 1) {
        return x * cosA - y * sinA; 
    } else {
        return x * sinA + y * cosA;
    }
}

SDL_Rect MY_calcRotationAndOffsetOfRect(SDL_Rect dst,SDL_Point* newPointPos,float rotation,SDL_Point* origin,SDL_Point* offset) {

    SDL_Point origin_;
    origin_.x = dst.x; origin_.y = dst.y;
    SDL_Point offset_;
    offset_.x = 0; offset_.y = 0;

    if(origin != NULL) { origin_  = *origin ; } 
    if(offset != NULL) { offset_  = *offset ; }
    
    dst.x = multByRotationMatrix(origin_.x,origin_.y,rotation,1) + multByRotationMatrix(offset_.x,offset_.y,rotation,1); 
    dst.y = multByRotationMatrix(origin_.x,origin_.y,rotation,2) + multByRotationMatrix(offset_.x,offset_.y,rotation,2);

    if(newPointPos != NULL) {
        newPointPos->x = multByRotationMatrix(dst.w,1,rotation,1) + origin_.x;
        newPointPos->y = multByRotationMatrix(dst.w,1,rotation,2) + origin_.y; 
    }

    return dst;
}
void MY_DrawRotatedLine(SDL_Rect dst,SDL_Point* origin , float rotation ) {
    SDL_Point origin_;
    origin_.x = dst.x; origin_.y = dst.y;
    if(origin != NULL) { origin_  = *origin ; }

    SDL_RenderCopyEx(renderer,GlobalTexture,NULL,&dst,rotation,origin,SDL_FLIP_NONE);
}



