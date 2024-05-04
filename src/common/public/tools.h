#ifndef PVZ_TOOL_H
#define PVZ_TOOL_H
#include <graphics.h>
//¹¤¾ßº¯Êý
void putimagePNG(int  picture_x, int picture_y, IMAGE* picture);
int getDelay();
inline void flipImage(IMAGE*src,IMAGE*dst);
#endif