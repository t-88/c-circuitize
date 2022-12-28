#pragma once
#include "consts.h"

extern int AABB(SDL_Rect r1 , SDL_Rect r2);
extern int LinePointCollistion( SDL_Point p1, SDL_Point p2, SDL_Point p,int offset);

extern void MY_DrawRotatedLine(SDL_Rect dst,SDL_Point* origin , float rotation );

extern SDL_Rect MY_calcRotationAndOffsetOfRect(SDL_Rect dst,SDL_Point* newPointPos,float rotation,SDL_Point* origin,SDL_Point* offset);
extern float MY_CalcDistence(SDL_Point p1,SDL_Point p2);